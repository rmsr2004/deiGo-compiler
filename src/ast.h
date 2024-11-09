/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues -  2022233032
*/

#ifndef _AST_H
#define _AST_H

/**
* @enum category
* @brief Represents the different categories of AST nodes.
* 
* This enumeration defines the various types of nodes that can appear in the AST.
*/
typedef enum category { 
    Program, VarDecl, FuncDecl, FuncHeader, FuncParams, FuncBody, ParamDecl, Block, If, For, Return, Call, Print,
    ParseArgs, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Add, Sub, Mul, Div, Mod, Not, Minus, Plus, Assign, Int, Float32,
    Bool, String, Natural, Decimal, Identifier, StrLit, Error
} category;

/**
* @struct node
* @brief Represents a node in the abstract syntax tree (AST).
* 
* This structure is used to represent a node in the AST.
*/
struct node {
    category category;                  // The category of the node.
    char* token;                        // The lexical token associated with the node (can be null).
    struct node* child;                 // Pointer to the next child node.
    struct node* brother;               // Pointer to the next brother node.
};
/**
* Creates a new node with the specified category and token.
*
* @param category The category of the node.
* @param token The token associated with the node.
* @return A pointer to the newly created node.
*/
struct node* new_node(enum category category, char *token);
/**
* Adds a child node to the given parent node.
*
* @param parent A pointer to the parent node.
* @param child A pointer to the child node to be added.
*/
void add_child(struct node* parent, struct node* child);
/**
* Adds a new brother node to the given node.
*
* This function adds a new brother node to the given node. If the given node
* already has a brother, it traverses the list of brothers until it finds the
* last brother and adds the new brother there.
*
* @param node The node to which the new brother will be added.
* @param new_brother The new brother node to be added.
*/
void add_brother(struct node* node, struct node* new_brother);
/**
* Counts the number of brother nodes of a given node.
*
* @param node Pointer to the starting node of the linked list.
* @return The number of brother nodes in the linked list.
*/
int count_brothers(struct node* node);
/**
* Adds a new node with the specified type to each brother of the given node.
*
* This function traverses the list of brothers starting from the given node and 
* adds a new node with the specified type as a child to each brother.
*
* @param node Pointer to the starting node.
* @param type The type to be assigned to the new nodes.
*/
void add_type_to_brothers(struct node* node, category type);
/**
* @brief Prints the abstract syntax tree (AST) starting from the given node.
*
* This function recursively prints the AST, starting from the specified node,
* with indentation representing the depth of each node in the tree.
*
* @param node A pointer to the root node of the AST to be printed.
* @param depth The current depth of the node in the tree, used for indentation.
*/
void print_ast(struct node* node, int depth);
/**
* @brief Recursively deletes AST node and its children.
*
* This function frees the memory allocated for the given AST node, its token,
* and recursively deletes its child and brother nodes.
*
* @param node A pointer to the AST node to be deleted. If the node is NULL, the function returns immediately.
*/
void delete_ast(struct node* node);
/**
* Converts an enum value of type `category` to its corresponding string representation.
*
* @param cat The enum value of type `category` to be converted.
* @return A constant character pointer to the string representation of the enum value.
*         If the enum value does not match any known category, "Unknown" is returned.
*/
char* category_to_string(category cat);

#endif  // _AST_H

// end of ast.h