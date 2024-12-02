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
	int is_func;                        // Flag to indicate if the symbol is a function.
    int is_used;                        // Flag to indicate if the symbol is used.
    int is_declared;                    // Flag to indicate if the symbol is declared.
    int is_global;                      // Flag to indicate if the symbol is global.
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
* @brief Fills the global symbol table with the given function node.
*
* This function checks if the function identifier is already present in the global symbol table.
* If the identifier is not present, it inserts the function symbol into the global symbol table.
* If the identifier is already present, it prints an error message indicating that the symbol is already defined
* and increments the semantic error count.
*
* @param function A pointer to the function node (FuncDecl) to be added to the global symbol table.
*/
void fill_global_table(struct node* function);
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
/**
* @brief Checks the semantic correctness of an expression in the given symbol table.
*
* This function performs semantic analysis on the provided expression node by checking
* its type, annotations, and ensuring that identifiers are declared and used correctly.
* It also verifies the compatibility of operators and operands, and handles various
* expression types such as identifiers, literals, binary and unary operators, control
* flow statements, function calls, and more.
*
* @param table Pointer to the symbol table where the expression is being checked.
* @param expression Pointer to the expression node to be checked.
*/
void check_expression(struct table* table, struct node* expression);
/**
* @brief Checks the validity of applying an operator to the given operands.
*
* This function verifies if the operator specified in the `operation` node
* can be applied to the types of the `left` and `right` operand nodes. If the
* operator is not applicable to the operand types, an error message is printed
* and the `semantic_errors` counter is incremented.
*
* @param left Pointer to the left operand node.
* @param right Pointer to the right operand node.
* @param operation Pointer to the operation node containing the operator.
* 
* For each operator, the function checks if the operand types are compatible
* with the operator. If not, an error message is printed with the line and
* column of the operation, the operator, and the operand types. The function
* also sets the `annotation` and `type` fields of the `operation` node if the
* operator is applicable.
*/
void check_operators(struct node* left, struct node* right, struct node* operation);
/**
* @brief Checks for unused symbols in the symbol table and reports them.
*
* This function iterates through the global symbol table and its subsequent tables,
* checking each symbol to see if it has been used. If a symbol is found that has not
* been used, is not a function, and is not a parameter, a message is printed indicating
* the line and column where the symbol was declared, along with the symbol's identifier.
* The count of semantic errors is incremented for each unused symbol found.
*/
void check_unused_symbols();
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
struct table* new_table(char* name, char* type, struct node* node);
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
struct table* find_table(char* name, char* params);
/**
* @brief Frees the memory allocated for the global symbol table.
*
* This function iterates through the linked list of symbol tables starting from
* the global_table and frees the memory allocated for each table.
*/
void free_tables();
/**
* @brief Annotates the abstract syntax tree (AST) for a function declaration.
*
* This function processes the AST node representing a function declaration or variable declaration.
* It skips variable declarations and checks expressions within the function body.
* If a variable declaration is found, it marks the variable as declared in the local symbol table.
*
* @param node Pointer to the AST node to be annotated. This node should represent a function declaration.
*/
void anotate_ast(struct node* node);
/**
* @brief Retrieves the parameter types of a function as a string.
*
* This function takes a function node and extracts the parameter types,
* returning them as a string in the format "(type1,type2,...)". If the
* function has no parameters, it returns "()".
*
* @param function A pointer to the function node (expected to be of type FuncDecl).
* @return A dynamically allocated string containing the parameter types.
*         The caller is responsible for freeing the allocated memory.
*/
char* get_params(struct node* function);
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
/**
* Converts an operator category to its corresponding string representation.
*
* @param cat The operator category to be converted.
* @return A string representing the operator, or NULL if the category is not recognized.
*/
char* operator_to_str(category cat);

#endif // _SYMBOLS_H

// end of symbols.h