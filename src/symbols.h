/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues -  2022233032
*/

#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#include "ast.h"

/**
* @struct symbol_list
* @brief Represents a list of symbols.
* 
* This structure is used to store information about symbols in a list format.
* Each symbol has an identifier, type, a flag indicating if it is a parameter,
* a pointer to the node where it was declared, and a pointer to the next symbol in the list.
*
*/
struct symbol_list {
	char* identifier;                   // The identifier of the symbol.   
	type type;                          // The type of the symbol.
    int is_param;                       // Flag to indicate if the symbol is a parameter.
	struct node* node;                  // The node where the symbol was declared.
	struct symbol_list* next;           // Pointer to the next symbol in the list.
};
/**
* @struct table 
* @brief Represents a symbol table.
* 
* This structure is used to represent a symbol table, which contains a list of
* symbols and a pointer to the next table in the list.
*/
struct table {
    char* name;                         // The name of the table.
    char* type;                         // The type of the table (global or local).
    char* params;                       // The parameters of the table.
    struct symbol_list* first_symbol;   // Pointer to the first symbol in the table.
    struct table* next;                 // Pointer to the next table in the list.
};
/**
* @brief Checks the program's syntax and semantics.
*
* This function creates the global symbol table and iterates through the 
* program's child nodes to check for function declarations and variable 
* declarations. It processes each function declaration by calling 
* `check_function` and each variable declaration by calling 
* `check_declaration`.
*
* @param program A pointer to the root node of the program's abstract syntax tree.
* @return The number of semantic errors found in the program.
*/
int check_program(struct node* program);
/**
* @brief Checks the function declaration and processes its symbol table.
*   
* This function processes the function declaration node, creates a new local symbol table
* for the function, and checks the function's return type, parameters, and body.
* It then inserts the function symbol in the global symbol table.
*
* @param function A pointer to the node representing the function declaration (FuncDecl).
*/
void check_function(struct node *function);
/**
* @brief Checks the return type of a function declaration node and inserts a symbol for the return type into the symbol table.
*
* This function examines the return type of a function declaration node. If the category of the return type is `FuncParams`,
* it sets the return type to `None`, indicating that the function has no return type. It then inserts a symbol for the return
* type into the provided symbol table.
*
* @param table A pointer to the symbol table where the return type symbol will be inserted.
* @param node A pointer to the function declaration node to be checked.
* @return The return type of the function.
*/
type check_func_type(struct table* table, struct node* node);
/**
* @brief Checks the parameters of a function and inserts them into the symbol table.
*
* This function iterates through the list of parameters provided in the AST (Abstract Syntax Tree)
* and checks if each parameter has already been declared in the symbol table. If a parameter is not
* found in the symbol table, it is inserted with its corresponding type and marked as a parameter.
* If a parameter is already declared, an error message is printed and the semantic error count is incremented.
*
* @param table A pointer to the symbol table where parameters will be checked and inserted.
* @param parameters A pointer to the AST node representing the function parameters (FuncParams).
*/
void check_parameters(struct table* table, struct node* parameters);
/**
* @brief Checks the body of a function for variable declarations and processes them.
*
* This function iterates through the statements in the function body and checks for
* variable declarations. If a variable declaration is found, it calls the 
* check_declaration function to process it.
*
* @param table A pointer to the symbol table.
* @param body A pointer to the node representing the function body.
*/
void check_body(struct table* table, struct node* body);
/**
* @brief Checks if a variable declaration is already present in the symbol table.
* 
* This function verifies if a variable (represented by the node) has already been declared
* in the provided symbol table. If the variable is not found in the table, it inserts the
* new symbol into the table. If the variable is already declared, it prints an error message
* and increments the semantic error count.
* 
* @param table Pointer to the symbol table where the variable declarations are stored.
* @param node Pointer to the node representing the variable declaration (VarDecl).
*/
void check_declaration(struct table* table, struct node* node);
void check_expression(struct table* table, struct node* expression);
/**
* @brief Inserts a new symbol into the symbol table.
*
* This function creates a new symbol with the given identifier, type, and node,
* and inserts it into the provided symbol table. If the symbol already exists
* in the table, the function returns NULL.
*
* @param table Pointer to the symbol table where the symbol will be inserted.
* @param identifier The identifier of the symbol to be inserted.
* @param type The type of the symbol to be inserted.
* @param node Pointer to the node associated with the symbol.
* @return Pointer to the newly inserted symbol, or NULL if the symbol already exists.
*/
struct symbol_list* insert_symbol(struct table* table, char* identifier, type type, struct node* node);
/**
* @brief Searches for a symbol in the given table by its identifier.
*
* This function iterates through the symbol list in the provided table and 
* compares each symbol's identifier with the given identifier. If a match is 
* found, the corresponding symbol is returned. If no match is found, the 
* function returns NULL.
*
* @param table A pointer to the table where the symbol search will be performed.
* @param identifier A string representing the identifier of the symbol to search for.
* @return A pointer to the symbol_list structure containing the symbol if found, 
*         or NULL if the symbol is not found.
*/
struct symbol_list* search_symbol(struct table* table, char* identifier);
/**
* Creates a new symbol table entry.
*
* @param name The name of the table.
* @param type The type of the table (e.g., "Global").
* @param node The AST node associated with the table.
* @return A pointer to the newly created table.
*
* The function allocates memory for a new table and initializes its fields.
* If the table type is "Global", it sets the params field to an empty string.
* Otherwise, it initializes the params field with the function parameters
* extracted from the AST node.
*
* The function also inserts the new table into the symbol table list.
*/
struct table* new_table(char* name, char* type, struct node*);
/**
* @brief Inserts a new table into the global table list.
*
* This function traverses the global table list until it finds the last table
* and then inserts the new table at the end of the list.
*
* @param new_table Pointer to the table to be inserted.
*/
void insert_table(struct table* new_table);
/**
* @brief Finds a table by its name in the global table list.
*
* This function searches through the global table list to find a table
* with the specified name. If a table with the given name is found, it
* returns a pointer to that table. If no table with the given name is
* found, it returns NULL.
*
* @param name The name of the table to find.
* @return A pointer to the table with the specified name, or NULL if no
*         such table is found.
*/
struct table* find_table(char* name);
/**
* @brief Prints the symbol table, including both global and local symbol tables.
* 
* This function iterates through the global symbol table and prints each symbol's
* identifier and type. If the symbol is a function, it also prints the function's
* parameters. After printing the global symbol table, it iterates through each
* local symbol table and prints the symbols in a similar manner.
* 
* The function assumes that the global symbol table is pointed to by the global_table
* variable and that each table structure contains a linked list of symbols.
*/
void print_symbol_table();
char *change_type(char *type);



#endif // _SYMBOLS_H

// end of symbols.h