%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues - 2022233032
    */

    #include <stdio.h>
    #include <ast.h>
    
    extern int yylex(void);
    extern char* yytext;

    void yyerror(char* s);

    struct node* program;
%}

%union{
    char* token;
    struct node* node;
}

%token  IDENTIFIER STRLIT NATURAL DECIMAL SEMICOLON COMMA BLANKID ASSIGN STAR DIV MINUS PLUS EQ GE GT LBRACE LE LPAR LSQ LT MOD
%token  NE NOT AND OR RBRACE RPAR RSQ PACKAGE RETURN ELSE FOR IF VAR INT FLOAT32 BOOL STRING PRINT PARSEINT FUNC CMDARGS RESERVED

%left PLUS MINUS STAR DIV MOD
%left OR AND
%left EQ NE GT GE LT LE
%right NOT
%right ASSIGN

%type<node> Program Declarations VarDeclaration VarSpec Type FuncDeclaration Parameters FuncBody VarsAndStatements Statement 
%type<node> ParseArgs FuncInvocation Expr

%%

Program:
    PACKAGE IDENTIFIER SEMICOLON Declarations   { ; }
    ;

Declarations:
    | VarDeclaration SEMICOLON Declarations           { ; }
    | FuncDeclaration SEMICOLON Declarations          { ; }
    | /*  null production */                          { ; }

VarDeclaration:
    VAR VarSpec                               { ; }
    | VAR LPAR VarSpec SEMICOLON RPAR         { ; }
    ;

VarSpec:
    IDENTIFIER VarSpecAux Type             { ; }
    ;

VarSpecAux:
    COMMA IDENTIFIER VarSpecAux     { ; }
    | /*  null production */        { ; }
    ;

Type:
    INT               { ; }
    | FLOAT32         { ; }
    | BOOL            { ; }
    | STRING          { ; }
    ;

FuncDeclaration:
    FUNC IDENTIFIER LPAR Parameters RPAR Type FuncBody  { ; }
    | FUNC IDENTIFIER LPAR RPAR FuncBody                { ; }
    | FUNC IDENTIFIER LPAR Parameters RPAR FuncBody     { ; }
    | FUNC IDENTIFIER LPAR RPAR Type FuncBody           { ; }
    ;

Parameters:
    IDENTIFIER Type ParametersAux   { ; }
    ;

ParametersAux:
    COMMA IDENTIFIER Type ParametersAux     { ; }
    | /*  null production */                { ; }

FuncBody:
    LBRACE VarsAndStatements RBRACE { ; }
    ;

VarsAndStatements:
    VarsAndStatements VarDeclaration SEMICOLON  { ; }
    | VarsAndStatements Statement SEMICOLON     { ; }
    | VarsAndStatements SEMICOLON               { ; }
    | /* null production */                     { ; }
    ;

Statement: 
    IDENTIFIER ASSIGN Expr                                                  { ; }
    | LBRACE StatementAux RBRACE                                            { ; }
    | IF Expr LBRACE StatementAux RBRACE ELSE LBRACE StatementAux RBRACE    { ; }
    | IF Expr LBRACE StatementAux RBRACE                                    { ; }
    | FOR Expr LBRACE StatementAux RBRACE                                   { ; }
    | FOR LBRACE StatementAux RBRACE                                        { ; }
    | RETURN Expr                                                           { ; }
    | RETURN                                                                { ; }
    | FuncInvocation                                                        { ; }
    | ParseArgs                                                             { ; }
    | PRINT LPAR Expr RPAR                                                  { ; }
    | PRINT LPAR STRLIT RPAR                                                { ; }
    | error                                                                 { ; }
    ;

StatementAux:
    Statement SEMICOLON StatementAux     { ; }
    | /*  null production */             { ; }
    
ParseArgs:
    IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR       { ; }
    | IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                    { ; }
    ;

FuncInvocation:
    IDENTIFIER LPAR Expr FuncInvocationAux RPAR   { ; }
    IDENTIFIER LPAR RPAR                          { ; }
    | IDENTIFIER LPAR error RPAR                  { ; }
    ;

FuncInvocationAux:
    COMMA Expr FuncInvocationAux     { ; }
    | /*  null production */         { ; }

Expr:
    Expr OR Expr                    { ; }
    | Expr AND Expr                 { ; }
    | Expr LT Expr                  { ; }
    | Expr GT Expr                  { ; }
    | Expr EQ Expr                  { ; }
    | Expr NE Expr                  { ; }
    | Expr LE Expr                  { ; }
    | Expr GE Expr                  { ; }
    | Expr PLUS Expr                { ; }
    | Expr MINUS Expr               { ; }
    | Expr STAR Expr                { ; }
    | Expr DIV Expr                 { ; }
    | Expr MOD Expr                 { ; }
    | NOT Expr                      { ; }
    | MINUS Expr                    { ; }
    | PLUS Expr                     { ; }
    | NATURAL                       { ; }
    | DECIMAL                       { ; }
    | IDENTIFIER                    { ; }
    | LPAR Expr RPAR                { ; }
    | LPAR error RPAR               { ; }
    ;
%%

void yyerror(char* s){
    printf("Line %d column %d: %s : %s\n", line_index, column_index, s, yytext);
}