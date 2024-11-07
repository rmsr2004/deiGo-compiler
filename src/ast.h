/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues - 2022233032
*/

#ifndef _AST_H
#define _AST_H

/**
* @enum category
* @brief Enumeration of various AST node categories.
* 
* This enumeration defines the different categories of Abstract Syntax Tree (AST) nodes
* used in the deiGo compiler. Each enumerator represents a specific type of node that
* can appear in the AST.
*/
enum category { 
    Program, VarDecl, FuncDecl, FuncHeader, FuncParams, FuncBody, ParamDecl, Block, If, For, Return, Call, Print,
    ParseArgs, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Assign, Int, Float32,
    Bool, String, Natural, Decimal, Identifier, StrLit, Error
};
/**
* @struct node
* @brief Represents a node in the abstract syntax tree (AST).
* 
* This structure is used to represent a node in the AST, which is a fundamental
* component in the compilation process. Each node contains a category, a token,
* and a list of child nodes.
*/
struct node {
    enum category category;             // The category of the node.
    char* token;                        // The lexical token associated with the node (can be null).
    struct node_list* children;         // A list of child nodes.
    struct node_list* brothers;         // A list of brother nodes.
};
/**
* @struct node_list
* @brief A structure to represent a linked list of nodes.
* 
* This structure is used to create a linked list where each element
* contains a pointer to a node and a pointer to the next element in the list.
*/
struct node_list {
    struct node *node;              // A pointer to a node in the list.
    struct node_list *next;         // A pointer to the next element in the list.
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