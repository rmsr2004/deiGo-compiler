/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues - 2022233032
*/

#ifndef _AST_H
#define _AST_H


enum category { 
    Program, VarDecl, FuncDecl, FuncHeader, FuncParams, FuncBody, ParamDecl, Block, If, For, Return, Call, Print,
    ParseArgs, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Assign, Int, Float32,
    Bool, String, Natural, Decimal, Identifier, StrLit, Error
};

struct node {
    enum category category;             // The category of the node.
    char* token;                        // The lexical token associated with the node (can be null).
    struct node* child;                 // Pointer to the next child node.
    struct node* brother;               // Pointer to the next brother node.
};

struct node* new_node(enum category category, char *token);
void add_child(struct node* parent, struct node* child);
void add_brother(struct node* node, struct node* new_brother);
int count_brothers(struct node* node);
void add_type_to_brothers(struct node* node, struct node* type_node);
void print_ast(struct node* node, int depth);
const char* category_to_string(enum category cat);

#endif  // _AST_H

// end of ast.h