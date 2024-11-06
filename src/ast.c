/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues - 2022233032
*/

#include <stdlib.h>
#include <stdio.h>

#include "ast.h"

/**
* Creates a new node with the specified category and token.
*
* @param category The category of the node.
* @param token The token associated with the node.
* @return A pointer to the newly created node.
*/
struct node* new_node(enum category category, char *token) {
    struct node *new = malloc(sizeof(struct node));
    new->category = category;
    new->token = token;
    new->children = malloc(sizeof(struct node_list));
    new->children->node = NULL;
    new->children->next = NULL;
    return new;
}
/**
* Adds a child node to the given parent node.
*
* This function allocates memory for a new node_list structure,
* assigns the child node to it, and appends it to the end of the
* parent's children list.
*
* @param parent A pointer to the parent node to which the child will be added.
* @param child A pointer to the child node to be added to the parent.
*/
void add_child(struct node* parent, struct node* child){
    if(parent == NULL || child == NULL) return;

    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;

    struct node_list* children = parent->children;
    while(children->next != NULL)
        children = children->next;
    children->next = new;
}
/**
* @brief Adds a new brother node to the list of brothers of a given node.
*
* This function takes two node pointers, `node` and `new_brother`.
* It creates a new node_list element for `new_brother` and appends it to the
* list of brothers of `node`. If `node` or `new_brother` is NULL,
* the function does nothing.
*
* @param node Pointer to the node to which the new brother will be added.
* @param new_brother Pointer to the new brother node to be added.
*/
void add_brother(struct node* node, struct node* new_brother){
    if(node == NULL || new_brother == NULL) return;

    struct node_list* new_brother_node = malloc(sizeof(struct node_list));
    new_brother_node->node = new_brother;
    new_brother_node->next = NULL;

    if(node->brothers == NULL){
        node->brothers = new_brother_node;
    } 
    else{
        struct node_list* current = node->brothers;
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_brother_node;
    }
}
/**
* @brief Counts the number of brother nodes.
*
* This function traverses the linked list of brother nodes starting from the given node
* and counts the number of nodes in the list.
*
* @param node A pointer to the starting node.
* @return The number of brother nodes. Returns -1 if the input node is NULL.
*/
int count_brothers(struct node* node){
    if(node == NULL) return -1;

    int count = 0;

    struct node_list* current = node->brothers;
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}
/**
* @brief Prints the abstract syntax tree (AST) starting from the given node.
*
* This function recursively prints the AST, starting from the specified node.
* It prints each node's category and token (if available), with indentation
* based on the depth of the node in the tree. The function first prints the
* current node, then recursively prints its children and siblings.
*
* @param node Pointer to the root node of the AST or subtree to be printed.
* @param depth The depth of the current node in the tree, used for indentation.
*/
void print_ast(struct node* node, int depth) {
    if(node == NULL) return;

    for(int i = 0; i < depth; i++){
        printf("..");
    }

    printf("%s", category_to_string(node->category));

    if(node->token != NULL){
        printf("(%s)", node->token);
    }

    printf("\n");

    // Print children of the node
    struct node_list* current = node->children;
    while (current != NULL) {
        print_ast(current->node, depth + 1);
        current = current->next;
    }

    // Print brothers of the node
    current = node->brothers;
    while(current != NULL){
        print_ast(current->node, depth);
        current = current->next;
    }
}
/**
* Converts an enum value of type `category` to its corresponding string representation.
*
* @param cat The enum value of type `category` to be converted.
* @return A constant character pointer to the string representation of the enum value.
*         If the enum value does not match any known category, "Unknown" is returned.
*/
const char* category_to_string(enum category cat){
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
    case Identifier:        return "Identifier";
    case StrLit:            return "StrLit";
    default:                return "Unknown";
    }
}

// end of ast.c