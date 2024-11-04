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
void add_child(struct node* parent, struct node* child) {
    struct node_list *new = malloc(sizeof(struct node_list));
    new->node = child;
    new->next = NULL;
    struct node_list *children = parent->children;
    while(children->next != NULL)
        children = children->next;
    children->next = new;
}


/**
 * @brief Adds a new brother node to the list of children of the given node.
 *
 * This function adds a new brother node to the list of children of the given node.
 * If either the given node or the new brother node is NULL, the function does nothing.
 * If the given node has no children, the new brother node is added as the first child.
 * Otherwise, the new brother node is added to the end of the list of children.
 *
 * @param aux_brother Pointer to the node to which the new brother node will be added.
 * @param new_brother Pointer to the new brother node to be added.
 */
void add_brother(struct node* aux_brother, struct node* new_brother){
    if(aux_brother == NULL || new_brother == NULL){
        return;
    }

    struct node_list* current = aux_brother->children;
    if(current == NULL){
        aux_brother->children = malloc(sizeof(struct node_list));
        aux_brother->children->node = new_brother;
        aux_brother->children->next = NULL;
    } else{
        while(current->next != NULL){
            current = current->next;
        }

        struct node_list* new_list_node = malloc(sizeof(struct node_list));
        new_list_node->node = new_brother;
        new_list_node->next = NULL;
        current->next = new_list_node;
    }
}

/**
* This function recursively prints the AST, starting from the specified node.
* Each level of depth in the tree is indicated by a series of underscores.
*
* @param node A pointer to the root node of the AST to be printed.
* @param depth The current depth in the tree, used for indentation.
*
* The function prints the category of each node, and if the node has an associated
* token, it prints the token as well. It then recursively prints all child nodes.
*/
void print_ast(struct node *node, int depth) {
    if (node == NULL) return;

    for (int i = 0; i < depth; i++) {
        printf("..");
    }

    printf("%s", category_to_string(node->category));

    if (node->token != NULL) {
        printf("(%s)", node->token);
    }

    printf("\n");

    struct node_list *child = node->children;
    while (child != NULL) {
        print_ast(child->node, depth + 1);
        child = child->next;
    }
}

/**
* Converts an enum value of type `category` to its corresponding string representation.
*
* @param cat The enum value of type `category` to be converted.
* @return A constant character pointer to the string representation of the enum value.
*         If the enum value does not match any known category, "Unknown" is returned.
*/
const char* category_to_string(enum category cat) {
    switch (cat) {
    case Program: return "Program";
    case VarDecl: return "VarDecl";
    case FuncDecl: return "FuncDecl";
    case FuncHeader: return "FuncHeader";
    case FuncParams: return "FuncParams";
    case FuncBody: return "FuncBody";
    case ParamDecl: return "ParamDecl";
    case Block: return "Block";
    case If: return "If";
    case For: return "For";
    case Return: return "Return";
    case Call: return "Call";
    case Print: return "Print";
    case ParseArgs: return "ParseArgs";
    case Or: return "Or";
    case And: return "And";
    case Eq: return "Eq";
    case Ne: return "Ne";
    case Lt: return "Lt";
    case Gt: return "Gt";
    case Le: return "Le";
    case Ge: return "Ge";
    case Add: return "Add";
    case Sub: return "Sub";
    case Mul: return "Mul";
    case Div: return "Div";
    case Mod: return "Mod";
    case Not: return "Not";
    case Minus: return "Minus";
    case Plus: return "Plus";
    case Assign: return "Assign";
    case Int: return "Int";
    case Float32: return "Float32";
    case Bool: return "Bool";
    case String: return "String";
    case Natural: return "Natural";
    case Identifier: return "Identifier";
    case StrLit: return "StrLit";
    default: return "Unknown";
    }
}

// end of ast.c