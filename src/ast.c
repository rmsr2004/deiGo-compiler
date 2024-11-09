/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues -  2022233032
*/

#include <stdlib.h>
#include <stdio.h>

#include "ast.h"

struct node* new_node(enum category category, char *token){
    struct node* new = (struct node*) malloc(sizeof(struct node));

    *new = (struct node) {
        .category = category,
        .token = token,
        .child = NULL,
        .brother = NULL
    };

    return new;
}

void add_child(struct node* parent, struct node* child){
    if(parent == NULL || child == NULL) return;

    if(parent->child == NULL){
        parent->child = child;
    } else {
        struct node* current = parent->child;
        while(current->brother != NULL){
            current = current->brother;
        }
        current->brother = child;
    }
}

void add_brother(struct node* node, struct node* new_brother){
    if(node == NULL || new_brother == NULL) return;

    struct node* current = node;
    if(current->brother == NULL){
        current->brother = new_brother;
    } else {
        while(current->brother != NULL){
            current = current->brother;
        }
        current->brother = new_brother;
    }
}

int count_brothers(struct node* node){
    if(node == NULL) return 0;

    int count = 0;
    while(node != NULL){
        count++;
        node = node->brother;
    }
    return count;
}

void add_type_to_brothers(struct node* node, category type){
    if(node == NULL) return;

    struct node* aux = NULL;
    struct node* current = node;
    while(current != NULL){
        aux = new_node(type, NULL);
        aux->brother = current->child;
        current->child = aux;
        
        current = current->brother;
    }
}

void print_ast(struct node* node, int depth){
    if(node == NULL) return;

    for(int i = 0; i < depth; i++){
        printf("..");
    }

    printf("%s", category_to_string(node->category));

    if(node->token != NULL){
        printf("(%s)", node->token);
    }

    printf("\n");

    print_ast(node->child, depth + 1);
    print_ast(node->brother, depth);
}

void delete_ast(struct node* node){
    if(node == NULL) return;

    if(node != NULL) free(node->token);
    delete_ast(node->child);
    delete_ast(node->brother);

    free(node);
}

char* category_to_string(category cat){
    switch(cat){
    case Program:           return "Program";
    case VarDecl:           return "VarDecl";
    case FuncDecl:          return "FuncDecl";
    case FuncHeader:        return "FuncHeader";
    case FuncParams:        return "FuncParams";
    case FuncBody:          return "FuncBody";
    case ParamDecl:         return "ParamDecl";
    case Block:             return "Block";
    case If:                return "If";
    case For:               return "For";
    case Return:            return "Return";
    case Call:              return "Call";
    case Print:             return "Print";
    case ParseArgs:         return "ParseArgs";
    case Or:                return "Or";
    case And:               return "And";
    case Eq:                return "Eq";
    case Ne:                return "Ne";
    case Lt:                return "Lt";
    case Gt:                return "Gt";
    case Le:                return "Le";
    case Ge:                return "Ge";
    case Add:               return "Add";
    case Sub:               return "Sub";
    case Mul:               return "Mul";
    case Div:               return "Div";
    case Mod:               return "Mod";
    case Not:               return "Not";
    case Minus:             return "Minus";
    case Plus:              return "Plus";
    case Assign:            return "Assign";
    case Int:               return "Int";
    case Float32:           return "Float32";
    case Bool:              return "Bool";
    case String:            return "String";
    case Natural:           return "Natural";
    case Decimal:           return "Decimal";
    case Identifier:        return "Identifier";
    case StrLit:            return "StrLit";
    default:                return "Error";
    }
}

// end of ast.c