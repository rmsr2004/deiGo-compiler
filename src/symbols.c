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

    struct node* aux = program->child; // 1st FuncDecl
    while(aux != NULL){
        if(aux->token->category == FuncDecl){
            check_function(aux);
        }

        if(aux->token->category == VarDecl){
            check_declaration(global_table, aux);
        }

        aux = aux->brother; // next FuncDecl || VarDecl
    }
    return semantic_errors;
}

void check_function(struct node* function){
    // function == FuncDecl
    struct node* id = get_child(function->child, 0);  // id = Identifier

    if(search_symbol(global_table, id->token->value) == NULL){
        //insert_symbol(global_table, id->token->value, None, function->child);

        // Create a new local symbol table for the function.
        struct table* local_table = new_table(id->token->value, "Function", function);

        // Obtain function return type.
        type func_type = check_func_type(local_table, function);

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

        // Insert the function symbol in the global symbol table.
        insert_symbol(global_table, id->token->value, func_type, function);
    } else {
        printf("Identifier %s already declared\n", id->token->value);
        semantic_errors++;
    }
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
            printf("Identifier %s already declared\n", id->token->value);
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
        printf("Identifier %s already declared\n", id->token->value);
        semantic_errors++;
    }
}

void check_expression(struct table* table, struct node* expression){
    // expression == Statement
    if(expression == NULL){
        return;
    }
}

struct symbol_list* insert_symbol(struct table* table, char* identifier, type type, struct node* node){
    struct symbol_list* new = (struct symbol_list*) malloc(sizeof(struct symbol_list));
    *new = (struct symbol_list) {
        .identifier = strdup(identifier),
        .type = type,
        .node = node,
        .is_param = 0,
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
    for(symbols = table->first_symbol; symbols!= NULL; symbols = symbols->next)
        if(strcmp(symbols->identifier, identifier) == 0)
            return symbols;
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

struct table* find_table(char* name){
    struct table* aux = global_table;
    while(aux != NULL){
        if(strcmp(aux->name, name) == 0){
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void print_symbol_table(){
    struct table* aux = global_table;

    // Print global symbol table.
    printf("==== Global Symbol Table ====\n");
    struct symbol_list* symbols = aux->first_symbol;
    while(symbols != NULL){
        printf("%s\t", symbols->identifier);        // print identifier
        // print params if symbol is a function
        if(symbols->node->token->category == FuncDecl)
            printf("%s", find_table(symbols->identifier)->params);
        
        printf("\t%s\n", type_to_str(symbols->type)); // print type
        
        symbols = symbols->next;
    }
    printf("\n");

    // Print local symbol tables.

    aux = aux->next;
    while(aux != NULL){
        printf("==== %s", aux->type);
        if(strcmp(aux->name, "") != 0) printf(" %s", aux->name);    // print function name
        if(aux->params != NULL) printf("%s", aux->params);          // print function parameters
        printf(" Symbol Table ====\n");
    
        struct symbol_list* symbols = aux->first_symbol;
        while(symbols != NULL){
            printf("%s\t\t%s", symbols->identifier, type_to_str(symbols->type));
            if(symbols->is_param) printf(" param");
            printf("\n");

            symbols = symbols->next;
        }
        printf("\n");
        aux = aux->next;
    }
}

// end of symbols.c