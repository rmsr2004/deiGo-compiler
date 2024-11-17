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
    Bool, String, Natural, Decimal, Identifier, StrLit
} category;
/**
* @enum type
* @brief Represents the different data types available.
* 
* This enumeration defines the various data types that can be used in the program.
*/
typedef enum type {
    integer, float32, boolean, string, None
} type;
/**
* @struct token
* @brief Represents a token in the abstract syntax tree (AST).
*
* This structure holds information about a token, including its value,
* category, type, and position (line and column) in the source code.
*/
struct token {
    char* value;                    // The value of the token.
    category category;              // The category of the token.
    type type;                      // The type of the token.
    char* annotation;               // The annotation of the token.
    int line;                       // The line in the source code where the token appears.
    int column;                     // The column in the source code where the token appears.                    
};
/**
* @struct node
* @brief Represents a node in the abstract syntax tree (AST).
* 
* This structure is used to represent a node in the AST.
*/
struct node {
    struct token* token;                // The token associated with the node.
    struct node* child;                 // Pointer to the next child node.
    struct node* brother;               // Pointer to the next brother node.
};
/**
* Creates a new node with the specified category and token.
*
* @param category The category of the node.
* @param value The value associated with the node.
* @return A pointer to the newly created node.
*/
struct node* new_node(enum category category, char* value);
/**
* Adds a child node to the given parent node.
*
* @param parent A pointer to the parent node.
* @param child A pointer to the child node to be added.
*/
void add_child(struct node* parent, struct node* child);
/**
* @brief Retrieves the child node at a specified index from a parent node.
*
* This function traverses the child nodes of the given parent node and returns
* the child node at the specified index. If the parent node is NULL or the index
* is out of bounds, the function returns NULL.
*
* @param parent A pointer to the parent node.
* @param index The index of the child node to retrieve.
* @return A pointer to the child node at the specified index, or NULL if the parent
*         node is NULL or the index is out of bounds.
*/
struct node* get_child(struct node* parent, int index);
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
char* category_to_str(category cat);
/**
* Converts a type enumeration value to its corresponding string representation.
*
* @param t The type enumeration value to be converted.
* @return A string representation of the type.
*/
const char* type_to_str(type t);
/**
* Converts a category to its corresponding type.
*
* @param cat The category to be converted.
* @return The corresponding type for the given category.
*/
type cat_to_type(category cat);

#endif  // _AST_H

// end of ast.h