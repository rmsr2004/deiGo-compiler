%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues - 2022233032
    */

    #include <stdio.h>

    extern int yylex(void);
    extern char* yytext;

    void yyerror(char* s);
%}

%token  IDENTIFIER STRLIT NATURAL DECIMAL SEMICOLON COMMA BLANKID ASSIGN STAR DIV MINUS PLUS EQ GE GT LBRACE LE LPAR LSQ LT MOD
%token  NE NOT AND OR RBRACE RPAR RSQ PACKAGE RETURN ELSE FOR IF VAR INT FLOAT32 BOOL STRING PRINT PARSEINT FUNC CMDARGS RESERVED

%left PLUS MINUS STAR DIV MOD
%left OR AND
%left EQ NE GT GE LT LE
%right NOT
%right ASSIGN

%%

/*
*   
*   To Do:
*       - things inside of {} and []
*
*/

Program:
    PACKAGE IDENTIFIER SEMICOLON Declarations   { ; }
    ;

Declarations:
    ;

VarDeclaration:
    VAR VarSpec                             { ; }
    | VAR LPAR VarSpec SEMICOLON RPAR       { ; }
    ;

VarSpec:
    ;

Type:
    INT             { ; }
    | FLOAT32       { ; }
    | BOOL          { ; }
    | STRING        { ; }
    ;

FuncDeclaration:
    ;

Parameters:
    ;

FuncBody:
    LBRACE VarsAndStatements RBRACE { ; }
    ;

VarsAndStatements:
    ;

Statement: 
    IDENTIFIER ASSIGN Expr       { ; }
    | FuncInvocation | ParseArgs { ; }
    | error                      { ; }
    ;
    
ParseArgs:
    IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR     { ; }
    | IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                  { ; }
    ;

FuncInvocation:
    IDENTIFIER LPAR RPAR                        { ; }
    | IDENTIFIER LPAR error RPAR                { ; }
    ;

Expr:
    Expr OR Expr                { ; }
    | Expr AND Expr             { ; }
    | Expr LT Expr              { ; }
    | Expr GT Expr              { ; }
    | Expr EQ Expr              { ; }
    | Expr NE Expr              { ; }
    | Expr LE Expr              { ; }
    | Expr GE Expr              { ; }
    | Expr PLUS Expr            { ; }
    | Expr MINUS Expr           { ; }
    | Expr STAR Expr            { ; }
    | Expr DIV Expr             { ; }
    | Expr MOD Expr             { ; }
    | NOT Expr                  { ; }
    | MINUS Expr                { ; }
    | PLUS Expr                 { ; }
    | NATURAL                   { ; }
    | DECIMAL                   { ; }
    | IDENTIFIER                { ; }
    | LPAR Expr RPAR            { ; }
    | LPAR error RPAR           { ; }
    ;
%%

void yyerror(char* s){
    printf("Line %d column %d: %s : %s\n", line_index, column_index, s, yytext);
}