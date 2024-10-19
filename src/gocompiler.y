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

%token  IDENTIFIER STRLIT NATURAL DECIMAL SEMICOLON COMMA BLANKID ASSIGN STAR DIV MINUS PLUS EQ GE GT LBRACE LE LPAR LSQ
%token  LT MOD NE NOT AND OR RBRACE RPAR RSQ PACKAGE RETURN ELSE FOR IF VAR INT FLOAT32 STRING PRINT PARSEINT FUNC CMDARGS RESERVED

%%

%%

void yyerror(char* s){
    printf("Line %d column %d: %s : %s\n", line_index, column_index, s, yytext);
}