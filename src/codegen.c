/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues -  2022233032
*/

#include "codegen.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symbols.h"

extern struct table* global_table;

int temporary;              // sequence of temporary registers in a function
int string_count = 0;       // sequence of string literals
char* func_name;            // name of the current function

/**
* @struct registers
* @brief A structure to represent a register with its associated symbol.
* 
* This structure contains a symbol and its corresponding register number.
*/
struct registers {
    char* symbol;       // The symbol associated with the register.
    int reg;            // The register number.
} registers;

struct registers regs[32];   // array of registers 
int reg_index = 0;           // index of the array of registers

void codegen_program(struct node* program){
    if(program == NULL){
        return;
    }

    if(program->child == NULL){
        printf("define i32 @main(){\n\tret i32 0\n}");
        return;
    } 

    // declare standard functions and constants

    printf("declare i32 @printf(i8*, ...)\n");
    printf("declare i32 @atoi(i8*)\n");
    printf("\n");
    printf("@.int = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
    printf("@.float = private unnamed_addr constant [7 x i8] c\"%%.08f\\0A\\00\"\n");
    printf("@.strlit = private unnamed_addr constant [4 x i8] c\"%%s\\0A\\00\"\n");
    printf("@.true = private unnamed_addr constant [6 x i8] c\"true\\0A\\00\"\n");
    printf("@.false = private unnamed_addr constant [7 x i8] c\"false\\0A\\00\"\n");
    printf("\n");
    
    string_count = 0;
    declare_strings(program);
    printf("\n");
    string_count = 0;

    // generate code for each function or variable declaration
    struct node* aux = program->child;
    while(aux != NULL){
        if(aux->token->category == FuncDecl){
            codegen_function(aux);
        }

        if(aux->token->category == VarDecl){
            codegen_global_var(aux);
        }

        aux = aux->brother;
    }

    // generate the entry point which calls main(integer) if it exists
    struct symbol_list* entry = search_symbol(global_table, "main");
    if(entry != NULL && entry->node->token->category == FuncDecl)
        printf("define i32 @main(i32 %%argc, i8** %%argv) {\n"
               "\t%%1 = call i32 @_main(i32 %%argc, i8** %%argv)\n"
               "\tret i32 %%1\n"
               "}\n");
}

void codegen_global_var(struct node* var){
    // var = VarDecl

    struct node* type = var->child;             // type = Type
    struct node* identifier = type->brother;    // identifier = Identifier

    printf("@%s = global %s ", identifier->token->value, get_llvm_type(var->child->token->type));

    switch(type->token->category){
    case Bool:
        printf("false\n");
        break;
    case Int:
        printf("0\n");
        break;
    case Float32:
        printf("0.0\n");
        break;
    default:
        break;
    }
}

void codegen_function(struct node* function){
    // function = FuncDecl

    // reset registers
    for(int i = 0; i < 32; i++){
        regs[i].symbol = NULL;
        regs[i].reg = -1;
    }
    reg_index = 0;

    // set temporary register to 1
    temporary = 1;

    // set current function name
    func_name = function->child->child->token->value;

    if(strcmp(func_name, "main") == 0){
        printf("\ndefine i32 @_main(");
    } else {
        type type = find_table(func_name, NULL)->first_symbol->type;
        char* _return = NULL;

        switch(type){
        case integer:
            _return = "i32";
            break;
        case float32:
            _return = "double";
            break;
        case boolean:
            _return = "i1";
            break;  
        case string:
            _return = "i8*";
            break;
        case None:
            _return = "void";
            break;
        }
        printf("\ndefine %s @_%s(", _return, func_name); 
    }
    
    // If the function is main, add the default parameters
    if(strcmp(func_name, "main") == 0){
        printf("i32 %%argc, i8** %%argv");
    }   

    // Codegen parameters
    struct node* parameters = function->child->child->brother;
    while(parameters->token->category != FuncParams){
        parameters = parameters->brother;
    }
    codegen_parameters(parameters);

    printf(") {\n");

    // Go to the func parameters
    parameters = function->child->child->brother;
    while(parameters->token->category != FuncParams){
        parameters = parameters->brother;
    }

    // allocate space for parameters
    struct node* parameter = parameters->child;
    while(parameter != NULL){
        printf("\t%%%d = alloca %s\n", temporary, get_llvm_type(parameter->child->token->type));
        printf("\tstore %s %%%s, %s* %%%d\n", get_llvm_type(parameter->child->token->type), parameter->child->brother->token->value, get_llvm_type(parameter->child->token->type), temporary);
        temporary++;

        // Save the register
        regs[reg_index].symbol = parameter->child->brother->token->value;
        regs[reg_index].reg = temporary - 1;
        reg_index++;

        parameter = parameter->brother;
    } 

    // codegen function body
    codegen_expression(function->child->brother->child);

    if(!find_return(function->child->brother->child) && strcmp(func_name, "main") != 0){
        printf("\tret void\n");
    }
    if(strcmp(func_name, "main") == 0) printf("\tret i32 %%%d\n", temporary-1);
    printf("}\n\n");
}

void codegen_parameters(struct node* parameters){
    // parameters = FuncParams

    struct node* parameter = parameters->child; // parameter = ParamDecl
    if(parameter == NULL){
        return;
    }

    int curr = 0;
    while(parameter != NULL){
        if(curr >= 1){
            printf(", ");
        }
        printf("%s %%%s", get_llvm_type(parameter->child->token->type), parameter->child->brother->token->value);

        curr++;
        parameter = parameter->brother;
    }
}

int codegen_expression(struct node* expression){
    // expression = 1st Expression

    if(expression == NULL){
        return -1;
    }

    int tmp = -1, left_tmp = -1, right_tmp = -1, reg = -1;

    switch(expression->token->category){
        case VarDecl: {
            char* id = expression->child->brother->token->value;
            printf("\t%%%s = alloca %s\n", id, get_llvm_type(expression->child->token->type));
            tmp = temporary;

            // In case there is a global variable with the same name, indicate that it is initialized
            struct symbol_list* symbol = search_symbol(find_table(func_name, NULL), id);
            symbol->is_declared_codegen = 1;

            // go to the next expression
            codegen_expression(expression->brother);
            break;
        }
        case Natural:
            printf("\t%%%d = add i32 %s, 0\n", temporary, expression->token->value);
            tmp = temporary++;
            break;
        case Decimal: {
            char* float_value = convert_to_float(expression->token->value);
            printf("\t%%%d = fadd double %s, 0.0\n", temporary, float_value);
            tmp = temporary++;
            break;
        }
        case Identifier:
            // find the register of the identifier
            reg = find_register(expression->token->value);
            if(reg != -1){
                // if the register is found, load the value
                printf("\t%%%d = load %s, %s* %%%d\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), reg);
            } else {
                struct symbol_list* symbol_l = search_symbol(find_table(func_name, NULL), expression->token->value);
                struct symbol_list* symbol_g = search_symbol(global_table, expression->token->value);

                if(symbol_l == NULL && symbol_g != NULL){
                    // Global Variable
                    printf("\t%%%d = load %s, %s* @%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
                } else if(symbol_l != NULL && symbol_g == NULL){
                    // Local Variable
                    printf("\t%%%d = load %s, %s* %%%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
                } else if(symbol_l != NULL && symbol_g != NULL){
                    // Both -> In this case we have a local and a global variable with the same identifier
                    // We need to find what we should load
                    if(symbol_l->is_declared_codegen){
                        // if local variable is declared
                        // load the local variable
                        printf("\t%%%d = load %s, %s* %%%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
                    } else {
                        // if local variable is not declared
                        // load the global variable
                        printf("\t%%%d = load %s, %s* @%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
                    }
                }
            }
            tmp = temporary++;
            break;
        case Not:
            temporary = codegen_expression(expression->child);
            temporary++;
            printf("\t%%%d = xor i1 %%%d, true\n", temporary, temporary-1);
            tmp = temporary++;
            break;
        case If:
            tmp = codegen_if(expression);
            codegen_expression(expression->brother);
            break;
        case Eq:
        case Ne:
        case Lt:
        case Le:
        case Gt:
        case Ge:
            tmp = codegen_boolean_expression(expression);
            break;
        case Mul:
        case Add:
        case Sub:
        case Div:
            tmp = codegen_arithmetic(expression);
            break;
        case Mod:
            left_tmp = codegen_expression(expression->child);
            right_tmp = codegen_expression(expression->child->brother);

            printf("\t%%%d = srem i32 %%%d, %%%d\n", temporary, left_tmp, right_tmp);
            tmp = temporary++;
            break;
        case Call:
            tmp = codegen_call_function(expression);
            break;
        case Return:
            if(expression->child != NULL){
                // if the return has an expression
                tmp = codegen_expression(expression->child);
                printf("\tret %s %%%d\n", get_llvm_type(expression->child->token->type), tmp);
            } else {
                // if the return has no expression
                printf("\tret void\n");
            }
            break;
        case Assign: {
            struct node* left = expression->child;
            struct node* right = left->brother;

            right_tmp = codegen_expression(right);

            // find the register of the identifier
            reg = find_register(left->token->value);
            if(reg != -1){
                // if the register is found, store the value
                printf("\tstore %s %%%d, %s* %%%d\n", get_llvm_type(left->token->type), right_tmp, get_llvm_type(left->token->type), reg);
            } else {
                // if the register is not found, find the symbol in the symbol table
                struct symbol_list* symbol_l = search_symbol(find_table(func_name, NULL), left->token->value);
                struct symbol_list* symbol_g = search_symbol(global_table, left->token->value);

                if(symbol_l == NULL && symbol_g != NULL){
                    // Global Variable
                    printf("\tstore %s %%%d, %s* @%s\n", get_llvm_type(left->token->type), right_tmp, get_llvm_type(left->token->type), left->token->value);
                } else if(symbol_l != NULL && symbol_g == NULL){
                    // Local Variable
                    printf("\tstore %s %%%d, %s* %%%s\n", get_llvm_type(left->token->type), right_tmp, get_llvm_type(left->token->type), left->token->value);
                } else if(symbol_l != NULL && symbol_g != NULL){
                    // Both -> In this case we have a local and a global variable with the same identifier
                    // We need to find what we should store
                    if(symbol_l->is_declared_codegen){
                        printf("\tstore %s %%%d, %s* %%%s\n", get_llvm_type(left->token->type), right_tmp, get_llvm_type(left->token->type), left->token->value);
                    } else {
                        printf("\tstore %s %%%d, %s* @%s\n", get_llvm_type(left->token->type), right_tmp, get_llvm_type(left->token->type), left->token->value);
                    }
                }
            }
            tmp = codegen_expression(expression->brother);
            break;
        }
        case For:
            tmp = codegen_for(expression);
            break;
        case Block:
            if(expression->child != NULL){
                tmp = codegen_expression(expression->child);
            }
            if(expression->brother != NULL && expression->brother->token->category != Block){
                // avoid that a if and else block are generated at the same time
                tmp = codegen_expression(expression->brother);
            }
            break;
        case Print:
            tmp = codegen_print(expression, 0);
            codegen_expression(expression->brother);
            break;
        case Or:
        case And:
            left_tmp = codegen_expression(expression->child);
            right_tmp = codegen_expression(expression->child->brother);

            if(expression->token->category == Or){
                printf("\t%%%d = or i1 %%%d, %%%d\n", temporary, left_tmp, right_tmp);
            } else {
                printf("\t%%%d = and i1 %%%d, %%%d\n", temporary, left_tmp, right_tmp);
            }
            tmp = temporary++;
            break;
        case ParseArgs: 
            tmp = codegen_parseargs(expression);
            codegen_expression(expression->brother);
            break;
        case Minus:
            tmp = codegen_expression(expression->child);
            if(expression->child->token->category == Decimal){
                printf("\t%%%d = fmul double %%%d, -1.0\n", temporary, tmp);
            } else {
                printf("\t%%%d = mul i32 %%%d,-1\n", temporary, tmp);
            }
            tmp = temporary++;
            break;
        default:
            break;
    }
    return tmp;
}

int codegen_parseargs(struct node* node){
    struct node* left = node->child;
    struct node* right = node->child->brother;
    
    codegen_expression(left); 
    int right_tmp = codegen_expression(right);

    printf("\t%%%d = getelementptr i8*, i8** %%argv, i32 %%%d\n", temporary, right_tmp);
    temporary++;
    printf("\t%%%d = load i8*, i8** %%%d\n", temporary, temporary-1);
    temporary++;
    printf("\t%%%d = call i32 @atoi(i8* %%%d)\n", temporary, temporary-1);
    printf("\tstore i32 %%%d, i32* %%%s\n", temporary, left->token->value);

    return temporary++;
}

int codegen_print(struct node* node, int minus){
    // node = Print

    struct node* expression = NULL; // expression = Identifier | Natural | String 
    if(minus){
        expression = node;
    } else {
        expression = node->child;
    }

    int tmp, true_label, false_label, end_label;

    switch(expression->token->category){
    case Minus: 
        return codegen_print(expression->child, 1);
    case StrLit: {
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds", temporary);
        printf(" ([4 x i8], [4 x i8]* @.strlit, i32 0, i32 0), i8* getelementptr inbounds");
        printf(" ([%d x i8], [%d x i8]* @.str.%d, i32 0, i32 0))\n", 
                count_escape(expression->token->value) + count_regular(expression->token->value) + 1, 
                count_escape(expression->token->value) + count_regular(expression->token->value) + 1, 
                string_count);
        string_count++;
        return temporary++;
    }
    case Natural: {
        if(minus && expression->token->value[0] != '0'){
            printf("\t%%%d = mul i32 %%%d, -1\n", temporary, temporary-1);
            temporary++;
            printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.int, i32 0, i32 0), i32 %s)\n", temporary, expression->token->value);
        } else {
            printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.int, i32 0, i32 0), i32 %s)\n", temporary, expression->token->value);
        }
        return temporary++;
    }
    case Identifier: {
        char* print_type = (expression->token->type == integer) ? "int" : "float";
        char* type = (expression->token->type == integer) ? "i32" : "double";

        // Here, the logic is the same as in the codegen_expression function

        int reg = find_register(expression->token->value);
        if(reg != -1){
            printf("\t%%%d = load %s, %s* %%%d\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), reg);
        } else {
            struct symbol_list* symbol_l = search_symbol(find_table(func_name, NULL), expression->token->value);
            struct symbol_list* symbol_g = search_symbol(global_table, expression->token->value);

            if(symbol_l == NULL && symbol_g != NULL){
                // Global Variable
                printf("\t%%%d = load %s, %s* @%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
            } else if(symbol_l != NULL && symbol_g == NULL){
                // Local Variable
                printf("\t%%%d = load %s, %s* %%%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
            } else if(symbol_l != NULL && symbol_g != NULL){
                if(symbol_l->is_declared_codegen){
                    printf("\t%%%d = load %s, %s* %%%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
                } else {
                    printf("\t%%%d = load %s, %s* @%s\n", temporary, get_llvm_type(expression->token->type), get_llvm_type(expression->token->type), expression->token->value);
                }
            }
        }
        temporary++;

        if(minus){
            if(strcmp(type, "i32") == 0){
                printf("\t%%%d = mul %s %%%d, -1\n", temporary, get_llvm_type(expression->token->type), temporary-1);
            } else {
                printf("\t%%%d = fmul double %%%d, -1.0\n", temporary, temporary-1);
            }
            temporary++;
            printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.%s, i32 0, i32 0), %s %%%d)\n", temporary, print_type, type, temporary - 1);
        } else {
            printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.%s, i32 0, i32 0), %s %%%d)\n", temporary, print_type, type, temporary - 1);
        }
        return temporary++;
    }
    case Decimal: {
        if(minus){
            printf("\t%%%d = fmul double %s, -1.0\n", temporary, expression->token->value);
            temporary++;
            printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.float, i32 0, i32 0), double -%s)\n", temporary, expression->token->value);
        } else {
            printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.float, i32 0, i32 0), double %s)\n", temporary, expression->token->value);
        }
        return temporary++;
    }
    case Call: {
        tmp = codegen_call_function(expression);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.int, i32 0, i32 0), i32 %%%d)\n", temporary, tmp);
        return temporary++;
    }
    case Add:
    case Sub:
    case Mul:
    case Div:
        temporary = codegen_arithmetic(expression);
        temporary++;
        char* print_type = (strcmp(expression->token->annotation, "int") == 0) ? "int" : "float";
        if(minus){
            printf("\t%%%d = mul %s %%%d, -1\n", temporary, get_llvm_type(expression->token->type), temporary-1);
            temporary++;
        }
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.%s, i32 0, i32 0), i32 %%%d)\n", temporary, print_type, temporary-1);
        return temporary++;
    case Mod:
        tmp = codegen_expression(expression);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.int, i32 0, i32 0), i32 %%%d)\n", temporary, tmp);
        return temporary++;
    case And:
    case Or:
        temporary = codegen_expression(expression);
        true_label = temporary++;
        false_label = temporary++;
        end_label = temporary++;
        printf("\tbr i1 %%%d, label %%L%d, label %%L%d\n", temporary-3, true_label, false_label);
        printf("\nL%d:\n", true_label);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.true, i32 0, i32 0))\n", temporary+3);
        printf("\tbr label %%L%d\n", end_label);
        printf("\nL%d:\n", false_label);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.false, i32 0, i32 0))\n", temporary+4);
        printf("\tbr label %%L%d\n", end_label);
        printf("\nL%d:\n", end_label);
        temporary += 4;
        return temporary++;
    case Not:
        temporary = codegen_expression(expression);
        true_label = temporary++;
        false_label = temporary++;
        end_label = temporary++;
        printf("\tbr i1 %%%d, label %%L%d, label %%L%d\n", temporary-3, true_label, false_label);
        printf("\nL%d:\n", true_label);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.true, i32 0, i32 0))\n", temporary+3);
        printf("\tbr label %%L%d\n", end_label);
        printf("\nL%d:\n", false_label);
        printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.false, i32 0, i32 0))\n", temporary+4);
        printf("\tbr label %%L%d\n", end_label);
        printf("\nL%d:\n", end_label);
        temporary += 4;
        return temporary++;
    default:
        break;
    }
    return temporary;
}

int codegen_for(struct node* node) {
    // node = For

    struct node* condition = node->child;
    struct node* body = condition->brother;

    // Labels to control the flow
    int cond_label = temporary++;
    int body_label = temporary++;
    int end_label = temporary++;

    // Condition block
    printf("\tbr label %%L%d\n", cond_label);
    printf("\nL%d:\n", cond_label);
    int cond_tmp = codegen_expression(condition);
    printf("\tbr i1 %%%d, label %%L%d, label %%L%d\n", cond_tmp, body_label, end_label);

    // Body block
    printf("\nL%d:\n", body_label);
    codegen_expression(body);
    printf("\tbr label %%L%d\n", cond_label);

    // End block
    printf("\nL%d:\n", end_label);
    codegen_expression(node->brother);

    return -1;
}

int codegen_if(struct node* node) {
    // node = If

    struct node* condition = node->child;
    struct node* true_block = condition->brother;
    struct node* false_block = true_block ? true_block->brother : NULL;

    int true_label = temporary++;
    int false_label = false_block ? temporary++ : -1;
    int end_label = temporary++;

    // Condition block
    int cond_tmp = codegen_expression(condition);
    if(false_block){
        printf("\tbr i1 %%%d, label %%L%d, label %%L%d\n", cond_tmp, true_label, false_label);
    } else {
        printf("\tbr i1 %%%d, label %%L%d, label %%L%d\n", cond_tmp, true_label, end_label);
    }

    // True block
    printf("\nL%d:\n", true_label);
    codegen_expression(true_block);
    
    if(search_for_return(true_block) == 0){
        printf("\tbr label %%L%d\n", end_label);
    }

    // Fake block to avoid error
    if(false_block){
        printf("\nL%d:\n", false_label);
        codegen_expression(false_block);
        printf("\tbr label %%L%d\n", end_label);
    }

    // End block
    printf("\nL%d:\n", end_label);

    return -1;
}

int codegen_call_function(struct node* node){
    // node = Call

    struct node* func_name = node->child;
    struct node* argument = func_name->brother;

    int tmp;
    char* args = (char*) malloc(50 * sizeof(char));
    char* aux = (char*) malloc(20 * sizeof(char));
    args[0] = '\0';

    while(argument != NULL){
        tmp = codegen_expression(argument);
        sprintf(aux, "%s %%%d", get_llvm_type(argument->token->type), tmp);
        strcat(args, aux);
        strcat(args, ", ");
        
        argument = argument->brother;
    }

    // remove the last comma
    args[strlen(args) - 2] = '\0';

    printf("\t%%%d = tail call i32 @_%s(%s)\n", temporary, func_name->token->value, args);

    return temporary++;
}

int codegen_arithmetic(struct node* node){
    struct node* left = node->child;
    struct node* right = left->brother;

    int left_tmp = codegen_expression(left);
    int right_tmp = codegen_expression(right);

    int tmp = temporary++;
    printf("\t%%%d = %s i32 %%%d, %%%d\n", tmp, get_operator(node->token->category), left_tmp, right_tmp);

    return tmp;
}

int codegen_boolean_expression(struct node* node){
    // node = Eq, Ne, Lt, Le, Gt, Ge

    char* operator = NULL;
    char* operation = NULL;

    struct node* left = node->child; // left = Expression
    struct node* right = left->brother; // right = Expression

    int left_tmp = codegen_expression(left);
    int right_tmp = codegen_expression(right);

    if(left->token->type == integer || left->token->type == boolean){
        operation = "icmp";
        switch(node->token->category){
        case Eq: operator = "eq"; break;
        case Ne: operator = "ne"; break;
        case Lt: operator = "slt"; break;
        case Le: operator = "sle"; break;
        case Gt: operator = "sgt"; break;
        case Ge: operator = "sge"; break;
        default: operator = NULL; break;
        }
    }

    if(left->token->type == float32){
        operation = "fcmp";
        switch(node->token->category){
        case Eq: operator = "oeq"; break;
        case Ne: operator = "one"; break;
        case Lt: operator = "olt"; break;
        case Le: operator = "ole"; break;
        case Gt: operator = "ogt"; break;
        case Ge: operator = "oge"; break;
        default: operator = NULL; break;
        }
    }

    if(operator == NULL || operation == NULL){
        return -1;
    }

    int tmp = temporary++;
    printf("\t%%%d = %s %s %s %%%d, %%%d\n", 
           tmp, operation, operator, get_llvm_type(left->token->type), left_tmp, right_tmp);


    return tmp;
}

void declare_strings(struct node* root){
    // root = Program

    if(root == NULL){
        return;
    }

    if(root->token->category == StrLit){
        // Remove the quotes from the string
        char* aux = root->token->value;
        size_t length = strlen(aux) - 2;
        size_t real_length = 0;

        // Calculate the actual length considering escape sequences
        for (size_t i = 1; i < length + 1; i++) {  // Start from 1 to skip the opening quote
            if(aux[i] == '\\'){
                switch(aux[i + 1]){
                    case 'n':
                    case '\\':
                    case 'f':
                    case 't':
                    case '"':
                    case 'r':
                        real_length += 1;  // Each escape sequence is 1 character
                        i++;  // Skip the next character (escape sequence part)
                        break;
                    default:
                        real_length += 1;  // Just one character for unknown escapes
                        break;
                }
            } else {
                real_length += 1;  // Regular characters
            }
        }

        // Now print the LLVM constant with the correct size
        printf("@.str.%d = private unnamed_addr constant [%zu x i8] c\"", string_count, real_length + 1);  // +1 for the null terminator

        // Now print the actual string with escapes
        for(size_t i = 1; i < length + 1; i++){
            if(aux[i] == '\\'){
                switch(aux[i + 1]){
                    case 'n':
                        printf("\\0A");
                        i++;
                        break;
                    case '\\':
                        printf("\\5C");
                        i++;
                        break;
                    case 'f':
                        printf("\\0C");
                        i++;
                        break;
                    case 't':
                        printf("\\09");
                        i++;
                        break;
                    case '"':
                        printf("\\22");
                        i++;
                        break;
                    case 'r':
                        printf("\\0D");
                        i++;
                        break;
                    default:
                        printf("%c", aux[i]);
                        break;
                }
            } else {
                printf("%c", aux[i]);
            }
        }

        printf("\\00\"\n");
        string_count++;
    }

    declare_strings(root->child);
    declare_strings(root->brother);
}

int count_regular(char* str){
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] != '\\'){
            count++;
        }
    }
    return count;
}

int count_escape(char* str){
    int count = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] == '\\'){
            count++;
            i++;
        }
    }
    return count;
}

char* get_llvm_type(type type){
    switch(type){
        case integer:   return "i32";
        case boolean:   return "i1";
        case float32:   return "double";
        case string:    return "i8*";
        default:        return NULL;
    }
}

char* get_operator(category cat){
    switch(cat){
        case Add: return "add";
        case Sub: return "sub";
        case Mul: return "mul";
        case Div: return "sdiv";
        case Mod: return "srem";
        default: return NULL;
    }
}

char* convert_to_float(char* value){
    double result;
    static char output_str[50];

    if(strchr(value, 'e') != NULL || strchr(value, 'E') != NULL){
        sscanf(value, "%lf", &result);
        sprintf(output_str, "%.1f", result);
    } else {
        strcpy(output_str, value);
    }
    return output_str;
}

int find_register(char* symbol){
    for(int i = 0; i < 32; i++){
        if(regs[i].symbol != NULL && strcmp(regs[i].symbol, symbol) == 0){
            return regs[i].reg;
        }
    }
    return -1;
}

int find_return(struct node* node){
    if(node == NULL){
        return 0;
    }

    if(node->token->category == Return){
        return 1;
    }

    return find_return(node->brother);
}

int search_for_return(struct node* node){
    if(node == NULL){
        return 0;
    }

    if(node->token->category == Return){
        return 1;
    }

    return search_for_return(node->child) || search_for_return(node->brother);
}

// end of codegen.c