/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues -  2022233032
*/

#include "symbols.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

int semantic_errors = 0;            // Number of semantic errors found during the analysis.

// Pointer to the global symbol table.
// Next table in the list is the first local symbol table.
// First local symbol table has a pointer to the next local symbol table and so on.
struct table* global_table = NULL; 

int check_program(struct node* program){
    // Create the global symbol table.
    global_table = new_table("", "Global", program->child);

    // Fill the global symbol table.
    struct node* aux = program->child; // 1st FuncDecl || VarDecl
    while(aux != NULL){
        if(aux->token->category == FuncDecl){
            fill_global_table(aux);
        }

        if(aux->token->category == VarDecl){
            check_declaration(global_table, aux);
        }

        aux = aux->brother; // next FuncDecl || VarDecl
    }
    
    // Fill local symbol tables.
    struct symbol_list* global_symbols = global_table->first_symbol;
    while(global_symbols != NULL){
        if(global_symbols->is_func){
            check_function(global_symbols->node);
        }
        global_symbols = global_symbols->next;
    }

    // Anotate the ast
    aux = program->child; // 1st FuncDecl || VarDecl
    while(aux != NULL){
        anotate_ast(aux);
        aux = aux->brother; // next FuncDecl || VarDecl
    }

    // Verify if symbols are declared but not used
    check_unused_symbols();

    return semantic_errors;
}

void fill_global_table(struct node* function){
    // function == FuncDecl
    struct node* id = get_child(function->child, 0);  // id = Identifier

    if(search_symbol(global_table, id->token->value) == NULL){
        // Insert the function symbol in the global symbol table.
        insert_symbol(global_table, id->token->value, None, function);
    } else {
        printf("Line %d, column %d: Symbol %s already defined\n", id->token->line, id->token->column, id->token->value);
        semantic_errors++;
    }
}

void check_function(struct node* function){
    // function == FuncDecl
    struct node* id = get_child(function->child, 0);  // id = Identifier

    // Create a new local symbol table for the function.
    struct table* local_table = new_table(id->token->value, "Function", function);

    // Obtain function return type.
    type func_type = check_func_type(local_table, function);

    // Search for the function symbol in the global symbol table.
    struct symbol_list* symbol = search_symbol(global_table, id->token->value);
    symbol->type = func_type;

    // Check parameters of the function. (first find FuncParams)
    int index = 0;
    struct node* parameters = get_child(function->child, index);  // parameters = FuncParams
    while(parameters->token->category != FuncParams){
        index++;
        parameters = get_child(function->child, index);
    }
    check_parameters(local_table, parameters);

    // Check body of the function.
    struct node* body = get_child(function, 1);
    check_body(local_table, body);
}

type check_func_type(struct table* table, struct node* node){
    // node == FuncDecl
    type type = get_child(node->child, 1)->token->type; // type = Type (return type)
    category category = get_child(node->child, 1)->token->category; // category = must be != FuncParams
    if(category == FuncParams){
        type = None;    // function has no return type
    }

    insert_symbol(table, "return", type, node);

    return type;
}

void check_parameters(struct table* table, struct node* parameters){
    // parameters = FuncParams 
    struct node* param_list = parameters->child; // param_list = ParamDecl

    while(param_list != NULL){
        struct node* id = get_child(param_list, 1);
        type type = get_child(param_list, 0)->token->type;
        
        if(search_symbol(table, id->token->value) == NULL){
            struct symbol_list* symbol = insert_symbol(table, id->token->value, type, param_list);
            symbol->is_param = 1;
        } else {
            printf("Line %d, column %d: Symbol %s already defined\n", id->token->line, id->token->column,id->token->value);
            semantic_errors++;
        }

        param_list = param_list->brother;   // next ParamDecl
    }
}

void check_body(struct table* table, struct node* body){
    // body == FuncBody

    struct node* statement = body->child; // 1st Statement
    while(statement != NULL){
        category current_category = statement->token->category;
        switch(current_category){
        case VarDecl:
            check_declaration(table, statement);
            break;
        default:
            break;
        }

        statement = statement->brother; // next Statement
    }
}

void check_declaration(struct table* table, struct node* node){
    // node == VarDecl
    if(node == NULL){
        return;
    }
    
    struct node* id = get_child(node, 1);
    type type = get_child(node, 0)->token->type;
    
    if(search_symbol(table, id->token->value) == NULL){
        insert_symbol(table, id->token->value, type, node);
    } else {
        printf("Line %d, column %d: Symbol %s already defined\n", id->token->line, id->token->column, id->token->value);
        semantic_errors++;
    }
}

void check_expression(struct table* table, struct node* expression){
    // expression == Statement
    if(expression == NULL){
        return;
    }

    struct node* aux = NULL;
    struct symbol_list* symbol = NULL;
    char* called_params = (char*) malloc(100 * sizeof(char));

    switch(expression->token->category){
    case Identifier:
        // expression == Identifier
        symbol = search_symbol(table, expression->token->value);
        if(symbol == NULL){
            // Identifier not declared at local table
            // We must search at global table
            symbol = search_symbol(global_table, expression->token->value);
            if(symbol == NULL){
                printf("Line %d, column %d: Cannot find symbol %s\n", expression->token->line, expression->token->column, expression->token->value);
                semantic_errors++;
                expression->token->annotation = "undef";
                expression->token->type = None;
                break;
            }

            // check if identifier is a function
            if(symbol->is_func){
                printf("Line %d, column %d: Cannot find symbol %s\n", expression->token->line, expression->token->column, expression->token->value);
                expression->token->annotation = "undef";
                expression->token->type = None;
            } else {
                expression->token->annotation = type_to_str(symbol->type);
                expression->token->type = symbol->type;
            }
            symbol->is_used = 1;
        } else {
            // Identifier found at local table
            
            // Check if identifier is declared
            if(symbol->is_declared == 0 && symbol->is_func == 0 && symbol->is_param == 0){
                // Identifier is global and not declared
                // Symbol = Global Symbol
                symbol = search_symbol(global_table, expression->token->value);
            }
            expression->token->annotation = type_to_str(symbol->type);
            expression->token->type = symbol->type;
            symbol->is_used = 1;
        }
        break;
    case Natural:
        // expression == Int
        expression->token->annotation = "int";
        expression->token->type = integer;
        break;
    case Decimal:
        // expression == Decimal
        expression->token->annotation = "float32";
        expression->token->type = float32;
        break;
    case StrLit:
        // expression == String
        expression->token->annotation = "string";
        expression->token->type = string;
        break;
    case Or:
    case And:
    case Eq:
    case Ne:
    case Le:
    case Lt:
    case Ge:
    case Gt:
    case Not:
        // expression == Or || And || Eq || Ne || Le || Lt || Ge || Gt || Not
        check_expression(table, expression->child);
        check_expression(table, expression->child->brother);

        expression->token->annotation = "bool";
        expression->token->type = boolean;

        check_operators(expression->child, expression->child->brother, expression);
        break;
    case Assign:
        // expression == Assign
        check_expression(table, expression->child);

        aux = expression->child->brother;
        while(aux != NULL){
            check_expression(table, aux);
            aux = aux->brother;
        }
        
        char* left_anotation = expression->child->token->annotation;
        char* right_anotation = expression->child->brother->token->annotation;

        if(strcmp(left_anotation, right_anotation) != 0){
            printf("Line %d, column %d: Operator = cannot be applied to types %s, %s\n", expression->token->line, expression->token->column, left_anotation, right_anotation);
            expression->token->annotation = left_anotation;
            expression->token->type = expression->child->token->type;
            semantic_errors++;
            break;
        } else if(strcmp(left_anotation, "undef") == 0 && strcmp(right_anotation, "undef") == 0){
            printf("Line %d, column %d: Operator = cannot be applied to types undef, undef\n", expression->token->line, expression->token->column);
            expression->token->annotation = left_anotation;
            expression->token->type = expression->child->token->type;
            semantic_errors++;
            break;
        }
        expression->token->annotation = left_anotation;
        break;
    case Add:
    case Sub:
    case Mul:
    case Div:
    case Mod:
        // expression == Add || Div || Mul || Div ||| Mod
        check_expression(table, expression->child);
        aux = expression->child->brother;
        while(aux != NULL){
            check_expression(table, aux);
            aux = aux->brother;
        }
        
        check_operators(expression->child, expression->child->brother, expression);
        break;
    case Plus:
    case Minus:
        // expression == Plus || Minus
        check_expression(table, expression->child);

        expression->token->annotation = expression->child->token->annotation;
        expression->token->type = expression->child->token->type;

        check_operators(expression->child, NULL, expression);
        break;
    case If:
    case For:
        // expression == If || For
        check_expression(table, expression->child);
        aux = expression->child->brother; // Statement inside If or For
        while(aux != NULL){
            check_expression(table, aux);
            aux = aux->brother;
        }

        char op[4];
        if(expression->token->category == If){
            strcpy(op, "if");
        } else {
            strcpy(op, "for");
        }

        if(expression->child->token->type != boolean && expression->child->token->type != None){
            printf("Line %d, column %d: Incompatible type %s in %s statement\n", expression->child->token->line, expression->child->token->column, expression->child->token->annotation, op);
            semantic_errors++;
        }
        break;
    case Call:
        // expression == Call
        //check_expression(table, expression->child);
        
        strcpy(called_params, "(");

        aux = expression->child->brother;
        while(aux != NULL){
            check_expression(table, aux);
            if(aux->token->annotation != NULL){
                strcat(called_params, aux->token->annotation);
                strcat(called_params, ",");
            } else if(aux->token->type == None){
                // Func Call that returns void
                strcat(called_params, "none,");
            }

            aux = aux->brother;
        }

        if(strlen(called_params) > 1)
            called_params[strlen(called_params) - 1] = '\0'; // remove last comma

        strcat(called_params, ")");

        struct table* func = find_table(expression->child->token->value, NULL);
        if(func == NULL){
            expression->child->token->annotation = "undef";
            expression->child->token->type = None;
            expression->token->annotation = "undef";
            expression->token->type = None;
            printf("Line %d, column %d: Cannot find symbol %s%s\n", expression->child->token->line, expression->child->token->column, expression->child->token->value, called_params);
            break;
        }
        

        char* func_params = func->params;
        expression->child->token->annotation = func_params;
        if(strcmp(func_params, called_params) != 0){
            printf("Line %d, column %d: Cannot find symbol %s%s\n", expression->child->token->line, expression->child->token->column, expression->child->token->value, called_params);
            semantic_errors++;
            expression->token->annotation = "undef";
            expression->child->token->annotation = "undef";
            expression->token->type = None;
            expression->child->token->type = None;
            break;
        }
        
        // Call anotation is the return type of the function
        symbol = search_symbol(global_table, expression->child->token->value);
        type return_type = find_table(symbol->identifier, NULL)->first_symbol->type;
        if(return_type != None){
            expression->token->annotation = type_to_str(return_type);
            expression->token->type = return_type;
        } else {
            expression->token->type = None;
            expression->token->annotation = NULL;
        }
        break;
    case ParseArgs:
        // expression == ParseArgs
        check_expression(table, expression->child);
        check_expression(table, expression->child->brother);

        char* left_annotation = expression->child->token->annotation;
        char* right_annotation = expression->child->brother->token->annotation;

        if(strcmp(left_annotation, "int") != 0 || strcmp(right_annotation, "int") != 0){
            printf("Line %d, column %d: Operator strconv.Atoi cannot be applied to types %s, %s\n", expression->token->line, expression->token->column, expression->child->token->annotation, expression->child->brother->token->annotation);
            semantic_errors++;
            expression->token->annotation = "undef";
            expression->token->type = None;
            break;
        }
        expression->token->annotation = expression->child->token->annotation;
        break;
    case Print:
        // expression == Print
        check_expression(table, expression->child);

        if(expression->child->token->annotation != NULL && strcmp(expression->child->token->annotation, "undef") == 0){
            struct node* line = expression->child;
            struct node* column = expression->child;
            while(line->token->line == 0 && column->token->column == 0){
                line = line->child;
                column = column->child;
            }
            printf("Line %d, column %d: Incompatible type undef in fmt.Println statement\n", line->token->line, column->token->column);
            semantic_errors++;
            break;
        }
        break;
    case Return:
        // expression == Return
        check_expression(table, expression->child);

        // check if return type is the same as the function return type
        type type;
        int line, column;
        char* return_char = NULL;
        if(expression->child != NULL){
            line = expression->child->token->line;
            column = expression->child->token->column;
            type = expression->child->token->type;
            return_char = type_to_str(type);
        } else {
            line = expression->token->line;
            column = expression->token->column;
            type = None;
            return_char = "void";
        }

        if(type != table->first_symbol->type){
            printf("Line %d, column %d: Incompatible type %s in return statement\n", line, column, return_char);
            semantic_errors++;
            break;
        }

        break;
    case Block:
        // expression == Block
        if(expression->child == NULL){
            // Last Block of the Block pair
            break;
        }

        check_expression(table, expression->child);
        aux = expression->child->brother; // next Statement inside Block
        while(aux != NULL){
            check_expression(table, aux);
            aux = aux->brother;
        }
        break;
    default:
        break;
    }
}

void check_operators(struct node* left, struct node* right, struct node* operation){
    if(left->token->annotation == NULL && right->token->annotation == NULL){
        return;
    }
    
    switch(operation->token->category){
    case Or:
    case And:
        // Or || And Operator
        if(left->token->type != boolean || right->token->type != boolean){
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", operation->token->line, operation->token->column, operator_to_str(operation->token->category), left->token->annotation, right->token->annotation);
            semantic_errors++;
        }
        break;
    case Eq:
    case Ne:
        // Eq || Ne Operator
        if(left->token->type != right->token->type || left->token->type == None || right->token->type == None){
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", operation->token->line, operation->token->column, operator_to_str(operation->token->category), left->token->annotation, right->token->annotation);
            semantic_errors++;
        }
        break;
    case Le:
    case Lt:
    case Ge:
    case Gt:
        // Le || Lt || Ge || Gt Operator
        if(
            left->token->type != right->token->type ||
            left->token->type == string || right->token->type == string ||
            left->token->type == boolean || right->token->type == boolean    
        ){
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", operation->token->line, operation->token->column, operator_to_str(operation->token->category), left->token->annotation, right->token->annotation);
            semantic_errors++;
        }
        break;
    case Not:
        // Not Operator
        if(left->token->type != boolean){
            printf("Line %d, column %d: Operator %s cannot be applied to type %s\n", operation->token->line, operation->token->column, operator_to_str(operation->token->category), left->token->annotation);
            semantic_errors++;
        }
        break;
    case Add:
    case Sub:
    case Mul:
    case Div:
    case Mod:
        // Add || Sub || Mul || Div || Mod Operator
        if(
            left->token->type != right->token->type ||
            left->token->type == string || right->token->type == string ||
            left->token->type == boolean || right->token->type == boolean ||
            left->token->type == None || right->token->type == None
        ){
            printf("Line %d, column %d: Operator %s cannot be applied to types %s, %s\n", operation->token->line, operation->token->column, operator_to_str(operation->token->category), left->token->annotation, right->token->annotation);
            operation->token->annotation = "undef";
            semantic_errors++;
            break;
        }
        operation->token->annotation = left->token->annotation;
        operation->token->type = left->token->type;
        break;
    case Plus:
    case Minus:
        // Plus || Minus Operator
        if(left->token->type == string || left->token->type == None || left->token->type == boolean){
            printf("Line %d, column %d: Operator %s cannot be applied to type %s\n", operation->token->line, operation->token->column, operator_to_str(operation->token->category), left->token->annotation);
            operation->token->annotation = "undef";
            semantic_errors++;
            break;
        }
        operation->token->annotation = left->token->annotation;
        operation->token->type = left->token->type;
        break;
    default:
        break;
    }
}

void check_unused_symbols(){
    struct table* aux = global_table->next;
    
    while(aux != NULL){
        struct symbol_list* symbols = aux->first_symbol;
        while(symbols != NULL){ 
            if(symbols->is_used == 0 && symbols->is_func == 0 && symbols->is_param == 0){
                struct node* node = get_child(symbols->node, 1);
                printf("Line %d, column %d: Symbol %s declared but never used\n", node->token->line, node->token->column, symbols->identifier);
                semantic_errors++;
            }
            symbols = symbols->next;
        }
        aux = aux->next;
    }
}

struct symbol_list* insert_symbol(struct table* table, char* identifier, type type, struct node* node){
    struct symbol_list* new = (struct symbol_list*) malloc(sizeof(struct symbol_list));
    *new = (struct symbol_list) {
        .identifier = strdup(identifier),
        .type = type,
        .node = node,
        .is_param = 0,
        .is_func = node->token->category == FuncDecl ? 1 : 0,   // 1 if symbol is a function, 0 otherwise
        .is_used = 0,
        .is_declared = 0,
        .is_declared_codegen = 0,
        .is_global = strcmp(table->name, "Global") == 0 ? 1 : 0, // 1 if symbol is global, 0 otherwise
        .next = NULL
    };

    struct symbol_list* symbols = table->first_symbol;
    if(symbols == NULL){
        table->first_symbol = new;  /* insert new symbol at the begining of the list */
    } else {
        while(symbols->next != NULL){
            if(strcmp(symbols->identifier, identifier) == 0){
                free(new);
                return NULL;    /* return NULL if symbol is already inserted */
            }
            symbols = symbols->next;    /* insert new symbol at the tail of the list */
        }
        symbols->next = new;
    }
    return new;
}

struct symbol_list* search_symbol(struct table* table, char* identifier){
    struct symbol_list* symbols;
    for(symbols = table->first_symbol; symbols != NULL; symbols = symbols->next){
        if(strcmp(symbols->identifier, identifier) == 0){
            return symbols;
        }
    }
    return NULL;
}

struct table* new_table(char* name, char* type, struct node* node){
    struct table* new = (struct table*) malloc(sizeof(struct table));
    *new = (struct table) {
        .name = strdup(name),
        .type = strdup(type),
        .params = NULL,
        .first_symbol = NULL,
        .next = NULL
    };

    if(strcmp(type, "Global") == 0){
        new->params = strdup("");
        return new;
    }

    new->params = (char*) malloc(100 * sizeof(char));
    strcpy(new->params, "(");

    insert_table(new);

    // Add parameter symbols to the table.
    // node = FuncDecl, node->first_child = FuncHeader, node->first_child->child = FuncParams

    struct node* aux = node->child->child->brother; // aux = FuncParams
    while(aux->token->category != FuncParams){
        aux = aux->brother;
    }
    struct node* parameter = aux->child;   // 1st ParamDecl

    if(parameter == NULL){
        strcat(new->params, ")");
        return new;
    }

    while(parameter != NULL){
        struct token* token = get_child(parameter, 0)->token; 
        strcat(new->params, type_to_str(cat_to_type(token->category)));
        strcat(new->params, ",");

        parameter = parameter->brother;
    }
    new->params[strlen(new->params) - 1] = '\0'; // remove last comma
    strcat(new->params, ")");

    return new;
}

void insert_table(struct table* new_table){
    struct table* aux = global_table;
    while(aux->next != NULL){
        aux = aux->next;
    }
    aux->next = new_table;
}

struct table* find_table(char* name, char* params){
    struct table* aux = global_table;
    while(aux != NULL){
        if(strcmp(aux->name, name) == 0){
            if(params == NULL)
                return aux;

            if(strcmp(aux->params, params) == 0)
                return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void free_tables(){
    if(global_table == NULL){
        return;
    }
    
    struct table* aux = global_table;
    struct table* next = NULL;
    while(aux != NULL){
        next = aux->next;
        free(aux);
        aux = next;
    }
}

void anotate_ast(struct node* node){
    // node = FuncDecl || VarDecl

    if(node == NULL || node->token->category == VarDecl){
        return;
    }


    struct node* body = node->child->brother; // aux = FuncBody
    if(body->child == NULL){
        // FuncBody is empty
        return;
    }

    struct table* local_table = find_table(node->child->child->token->value, get_params(node)); // get local table
    if(local_table == NULL){
        // table not found
        return;
    }

    struct node* statement = body->child; // 1st Statement (can be VarDecl)
                                          // Inside of while, VarDecl is skipped

    while(statement != NULL){
        if(statement->token->category != VarDecl){
            // skip VarDecl
            check_expression(local_table, statement);
        } else {
            // VarDecl -> Indicar que a variavel foi declarada
            // Isto resolve o problema de redeclarar variaveis que eram globais
            struct node* id = get_child(statement, 1);
            struct symbol_list* symbol = search_symbol(local_table, id->token->value);
            if(symbol != NULL) symbol->is_declared = 1;
        }
        statement = statement->brother; // next Statement
    }
}

char* get_params(struct node* function){
    // function == FuncDecl
    struct node* aux = function->child->child; // aux = FuncParams
    while(aux->token->category != FuncParams){
        aux = aux->brother;
    }

    char* params = (char*) malloc(100 * sizeof(char));
    strcpy(params, "(");
    if(aux->child == NULL){
        strcat(params, ")");
        return params;
    }

    struct node* param = aux->child; // 1st ParamDecl
    while(param != NULL){
        struct token* token = get_child(param, 0)->token;
        strcat(params, type_to_str(cat_to_type(token->category)));
        strcat(params, ",");
        param = param->brother;
    }

    params[strlen(params) - 1] = '\0'; // remove last comma

    strcat(params, ")");
    return params;
}

void print_symbol_table(){
    struct table* aux = global_table;

    // Print global symbol table.
    printf("===== Global Symbol Table =====\n");
    struct symbol_list* symbols = aux->first_symbol;
    while(symbols != NULL){
        printf("%s\t", symbols->identifier);        // print identifier
        // print params if symbol is a function
        if(symbols->node->token->category == FuncDecl)
            printf("%s", find_table(symbols->identifier, NULL)->params);
        
        printf("\t%s\n", type_to_str(symbols->type)); // print type
        
        symbols = symbols->next;
    }
    printf("\n");

    // Print local symbol tables.

    aux = aux->next;
    while(aux != NULL){
        printf("===== %s", aux->type);
        if(strcmp(aux->name, "") != 0) printf(" %s", aux->name);    // print function name
        if(aux->params != NULL) printf("%s", aux->params);          // print function parameters
        printf(" Symbol Table =====\n");
    
        struct symbol_list* symbols = aux->first_symbol;
        while(symbols != NULL){
            printf("%s\t\t%s", symbols->identifier, type_to_str(symbols->type));
            if(symbols->is_param) printf("\tparam");
            printf("\n");

            symbols = symbols->next;
        }
        printf("\n");
        aux = aux->next;
    }
}

char* operator_to_str(category cat){
    switch(cat){
    case Or:    return "||";
    case And:   return "&&";
    case Eq:    return "==";
    case Ne:    return "!=";
    case Le:    return "<=";
    case Lt:    return "<";
    case Ge:    return ">=";
    case Gt:    return ">";
    case Add:   return "+";
    case Sub:   return "-";
    case Mul:   return "*";
    case Div:   return "/";
    case Not:   return "!";
    case Minus: return "-";
    case Plus:  return "+";
    default:    return NULL;
    }
}

// end of symbols.c