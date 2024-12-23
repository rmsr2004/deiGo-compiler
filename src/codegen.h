/*  
*   João Afonso dos Santos Simões   -  2022236316
*   Rodrigo Miguel Santos Rodrigues -  2022233032
*/

#ifndef _CODEGEN_H
#define _CODEGEN_H

#include "ast.h"

/**
* @brief Generates LLVM IR code for the given program node.
*
* This function generates the necessary LLVM IR code for the provided program node.
* It starts by checking if the program node is NULL, in which case it returns immediately.
* If the program node has no children, it generates a simple main function that returns 0.
* It then declares several standard functions and constants used in the program.
* After that, it declares strings used in the program and generates code for each function
* or variable declaration found in the program node's children.
*
* @param program A pointer to the root node of the program's abstract syntax tree.
*/
void codegen_program(struct node* program);
/**
* @brief Generates LLVM IR code for a global variable declaration.
*
* This function takes a node representing a global variable declaration
* and generates the corresponding LLVM IR code. The generated code
* includes the variable's name, type, and initial value.
*
* @param var A pointer to the node representing the global variable declaration.
*/
void codegen_global_var(struct node* var);
/**
* @brief Generates LLVM IR code for a given function node.
*
* This function takes a function node from the abstract syntax tree (AST) and generates
* the corresponding LLVM Intermediate Representation (IR) code. It handles the function
* declaration, parameters, and the function body.
*
* @param function A pointer to the function node in the AST.
*/
void codegen_function(struct node* function);
/**
* Generates LLVM code for function parameters.
*
* This function takes a node representing function parameters and generates
* the corresponding LLVM code for each parameter. The parameters are expected
* to be in the form of a linked list of nodes, where each node represents a
* parameter declaration.
*
* @param parameters A pointer to the root node of the function parameters.
*                   The node should have children representing individual
*                   parameter declarations.
*/
void codegen_parameters(struct node* parameters);
/**
* @brief Generates LLVM IR code for a given expression node in the AST.
*
* This function recursively traverses the abstract syntax tree (AST) starting from the given expression node,
* generating the corresponding LLVM Intermediate Representation (IR) code for each node.
*
* @param expression A pointer to the root node of the expression in the AST.
* @return The temporary register number where the result of the expression is stored, or -1 if the expression is NULL.
*/
int codegen_expression(struct node* expression);
/**
* @brief Generates code to parse command line arguments.
*
* This function takes a node representing a parse tree and generates
* LLVM IR code to parse command line arguments. It processes the left
* and right children of the node to generate expressions and then
* generates code to get the argument from the argv array, convert it
* to an integer using the atoi function, and store the result.
*
* @param node A pointer to the root node of the parse tree.
* @return The next available temporary variable index.
*/
int codegen_parseargs(struct node* node);
/**
* Generates LLVM IR code for printing various types of expressions.
*
* @param node The AST node representing the print statement.
* @param minus A flag indicating if the expression should be negated.
* @return The temporary register number used for the generated code.
*/
int codegen_print(struct node* node, int minus);
/**
* Generates LLVM IR code for a 'for' loop node in the AST.
*
* This function handles the code generation for a 'for' loop construct.
* It generates the necessary labels and branches to control the flow
* of the loop, including the condition check, the loop body, and the
* end of the loop.
*
* @param node A pointer to the 'for' loop node in the AST.
*
* @return Always returns -1.
*/
int codegen_for(struct node* node);
/**
* Generates LLVM IR code for an if statement.
*
* @param node A pointer to the root node of the if statement in the AST.
* @return Always returns -1.
*/
int codegen_if(struct node* node);
/**
* Generates LLVM IR code for a function call.
*
* This function takes a node representing a function call in the abstract syntax tree (AST)
* and generates the corresponding LLVM IR code. It handles the function name and its arguments,
* formats them appropriately, and prints the LLVM IR call instruction.
*
* @param node A pointer to the AST node representing the function call.
* @return The temporary variable number used for the result of the function call.
*/
int codegen_call_function(struct node* node);
/**
* Generates code for an arithmetic operation.
*
* This function takes a node representing an arithmetic operation in the 
* abstract syntax tree (AST) and generates the corresponding intermediate 
* representation (IR) code for the operation. It recursively generates code 
* for the left and right operands, and then combines them using the operator 
* specified in the node.
*
* @param node A pointer to the node representing the arithmetic operation in the AST.
* @return The temporary variable number where the result of the arithmetic operation is stored.
*/
int codegen_arithmetic(struct node* node);
/**
* Generates LLVM IR code for a boolean expression node.
*
* This function takes a boolean expression node and generates the corresponding
* LLVM IR code for it. The boolean expression can be one of the following:
* Eq (equal), Ne (not equal), Lt (less than), Le (less than or equal), Gt (greater than),
* or Ge (greater than or equal). The function handles both integer/boolean and float32
* types for the operands.
*
* @param node A pointer to the boolean expression node.
* @return The temporary variable number where the result of the boolean expression is stored,
*         or -1 if an error occurs (e.g., unsupported operation or type).
*/
int codegen_boolean_expression(struct node* node);
/**
* @brief Declares LLVM string constants for string literals found in the AST.
*
* This function traverses the abstract syntax tree (AST) starting from the given root node,
* identifies nodes containing string literals, and generates corresponding LLVM string
* constants. The string literals are processed to handle escape sequences and to calculate
* the correct length of the resulting string.
*
* @param root Pointer to the root node of the AST.
*/
void declare_strings(struct node* root);
/**
* @brief Counts the number of regular characters in a string, excluding backslashes.
*
* This function iterates through the given string and counts the number of characters
* that are not backslashes ('\\'). It stops counting when it reaches the null terminator.
*
* @param str The input string to be processed.
* @return The count of regular characters in the string.
*/
int count_regular(char* str);
/**
* @brief Counts the number of escape sequences in a given string.
*
* This function iterates through the input string and counts the number of
* escape sequences (i.e., backslashes followed by another character).
*
* @param str The input string to be analyzed.
* @return The number of escape sequences found in the input string.
*/
int count_escape(char* str);
/**
* @brief Converts a custom type to its corresponding LLVM type representation.
*
* This function takes a custom type and returns a string representing the
* equivalent LLVM type.
*
* @param type The custom type to be converted.
* @return A string representing the LLVM type.
*/
char* get_llvm_type(type type);
/**
* @brief Returns the string representation of the given operator category.
*
* This function takes an operator category as input and returns the corresponding
* string representation of the operator.
* @param cat The operator category.
* @return The string representation of the operator, or NULL if the category is not recognized.
*/
char* get_operator(category cat);
/**
* @brief Converts a string representation of a number to a float with one decimal place if it contains an exponent.
*
* This function takes a string representing a number and checks if it contains an exponent ('e' or 'E').
* If it does, the function converts the string to a double and then formats it as a float with one decimal place.
* If the string does not contain an exponent, it simply copies the input string to the output.
*
* @param value The input string representing a number.
* @return A pointer to a static string containing the formatted number.
*/
char* convert_to_float(char* value);
/**
* @brief Finds the register associated with a given symbol.
*
* This function searches through an array of registers to find the one
* that is associated with the provided symbol. If the symbol is found,
* the function returns the register number. If the symbol is not found,
* the function returns -1.
*
* @param symbol The symbol to search for in the register array.
* @return The register number associated with the symbol, or -1 if the symbol is not found.
*/
int find_register(char* symbol);
/**
* @brief Recursively searches for a return statement in the given node and its siblings.
*
* This function checks if the provided node or any of its sibling nodes contain a return statement.
* It returns 1 if a return statement is found, otherwise it returns 0.
*
* @param node A pointer to the node to be checked.
* @return int 1 if a return statement is found, 0 otherwise.
*/
int find_return(struct node* node);
/**
* @brief Recursively searches for a return statement in the given syntax tree node.
*
* This function traverses the syntax tree starting from the given node and checks
* if any node in the tree represents a return statement. It returns 1 if a return
* statement is found, otherwise it returns 0.
*
* @param node A pointer to the root node of the syntax tree to search.
* @return int 1 if a return statement is found, 0 otherwise.
*/
int search_for_return(struct node* node);

#endif  // _CODEGEN_H

// end of codegen.h