%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues -  2022233032
    */

    #include <stdio.h>
    #include "ast.h"
    
    int yylex(void);
    extern char* yytext;

    void yyerror(char* s);

    struct node* program;
    struct node* aux_node;
%}

%union{
    char* token;
    struct node* node;
}

%token          SEMICOLON COMMA BLANKID ASSIGN STAR DIV MINUS PLUS EQ GE GT LBRACE LE LPAR LSQ LT MOD NE NOT AND OR 
%token          RBRACE RPAR RSQ PACKAGE RETURN ELSE FOR IF VAR INT FLOAT32 BOOL STRING PRINT PARSEINT FUNC CMDARGS
%token<token>   IDENTIFIER STRLIT NATURAL DECIMAL RESERVED

%left PLUS MINUS STAR DIV MOD
%left OR AND
%left EQ NE GT GE LT LE
%right NOT
%right ASSIGN

%type<node> Program Declarations VarDeclaration VarSpec VarSpecAux Type FuncDeclaration Parameters ParametersAux FuncBody VarsAndStatements Statement
%type<node> StatementAux ParseArgs FuncInvocation Expr

%%

Program:
    PACKAGE IDENTIFIER SEMICOLON Declarations   { 
                                                    $$ = program = new_node(Program, NULL);
                                                    add_child(program, $4);
                                                }
    ;

Declarations:
    VarDeclaration SEMICOLON Declarations           { add_child($$, $3); $$ = $1; }
    | FuncDeclaration SEMICOLON Declarations        { add_child($$, $3); $$ = $1; }
    | /*  null production */                        { $$ = NULL; }

VarDeclaration:
    VAR VarSpec                               { $$ = $2; }
    | VAR LPAR VarSpec SEMICOLON RPAR         { $$ = $3;  }
    ;

VarSpec:
    IDENTIFIER VarSpecAux Type             {    
                                                $$ = new_node(VarDecl, NULL);
                                                add_brother($$, $2); 
                                                add_child($$, new_node(Identifier, $1)); 
                                                add_child($$, $3); 
                                            }
    ;

VarSpecAux:
    COMMA IDENTIFIER VarSpecAux     { $$ = new_node(VarDecl, NULL); add_brother($$, $3); add_child($$, new_node(Identifier, $2)); }
    | /*  null production */        { $$ = NULL; }
    ;

Type:
    INT               { $$ = new_node(Int, NULL); }
    | FLOAT32         { $$ = new_node(Float32, NULL); }
    | BOOL            { $$ = new_node(Bool, NULL); }
    | STRING          { $$ = new_node(String, NULL); }
    ;

FuncDeclaration:
    FUNC IDENTIFIER LPAR Parameters RPAR Type FuncBody  { 
                                                            $$ = new_node(FuncDecl, NULL);
                                                            aux_node = new_node(FuncHeader, NULL);
                                                            add_child(aux_node, new_node(Identifier, $2));
                                                            add_child(aux_node, $6);
                                                            add_child(aux_node, $4);
                                                            add_child($$, aux_node);
                                                            add_brother($$, $7);
                                                        }
    | FUNC IDENTIFIER LPAR RPAR FuncBody                { 
                                                            $$ = new_node(FuncDecl, NULL); 
                                                            aux_node = new_node(FuncHeader, NULL); 
                                                            add_child(aux_node, new_node(Identifier, $2)); 
                                                            add_child($$, aux_node); 
                                                            add_brother($$, $5); 
                                                        }
    | FUNC IDENTIFIER LPAR Parameters RPAR FuncBody     { 
                                                            $$ = new_node(FuncDecl, NULL);
                                                            aux_node = new_node(FuncHeader, NULL);
                                                            add_child(aux_node, new_node(Identifier, $2));
                                                            add_child(aux_node, $4);
                                                            add_child($$, aux_node);
                                                            add_brother($$, $6);
                                                        }
    | FUNC IDENTIFIER LPAR RPAR Type FuncBody           { 
                                                            $$ = new_node(FuncDecl, NULL);
                                                            aux_node = new_node(FuncHeader, NULL);
                                                            add_child(aux_node, new_node(Identifier, $2));
                                                            add_child(aux_node, $5);
                                                            add_child($$, aux_node);
                                                            add_brother($$, $6);
                                                        }
    ;

Parameters:
    IDENTIFIER Type ParametersAux   { 
                                        $$ = new_node(FuncParams, NULL); 
                                        aux_node = new_node(ParamDecl, NULL); 
                                        add_child(aux_node, new_node(Identifier, $1)); 
                                        add_child(aux_node, $2); 
                                        add_child($$, aux_node);
                                        add_brother(aux_node, $3); 
                                    }
    ;

ParametersAux:
    COMMA IDENTIFIER Type ParametersAux     { $$ = new_node(ParamDecl, NULL); add_child($$, new_node(Identifier, $2)); add_child($$, $3); add_brother($$, $4); }
    | /*  null production */                { $$ = NULL; }

FuncBody:
    LBRACE VarsAndStatements RBRACE { $$ = new_node(FuncBody, NULL); add_child($$, $2); }
    ;

VarsAndStatements:
    VarsAndStatements VarDeclaration SEMICOLON  { add_child($$, $2); $$ = $1; }
    | VarsAndStatements Statement SEMICOLON     { add_child($$, $2); $$ = $1; }
    | VarsAndStatements SEMICOLON               { $$ = $1; }
    | /* null production */                     { $$ = NULL; }
    ;

Statement: 
    IDENTIFIER ASSIGN Expr                                                  { 
                                                                                $$ = new_node(Assign, NULL);
                                                                                add_child($$, new_node(Identifier, $1)); 
                                                                                add_child($$, $3); 
                                                                            }
    | LBRACE StatementAux RBRACE                                            { add_child($$, $2); }
    | IF Expr LBRACE StatementAux RBRACE ELSE LBRACE StatementAux RBRACE    {
                                                                                $$ = new_node(If, NULL);
                                                                                add_child($$, $2);

                                                                                // Create the If block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, $4);
                                                                                add_child($$, aux_node);

                                                                                // Create the Else block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, $8);
                                                                                add_child($$, aux_node);
                                                                            }
    | IF Expr LBRACE StatementAux RBRACE                                    { 
                                                                                $$ = new_node(If, NULL);
                                                                                add_child($$, $2);

                                                                                // Create the If block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, $4);
                                                                                add_child($$, aux_node);
                                                                            }
    | FOR Expr LBRACE StatementAux RBRACE                                   { 
                                                                                $$ = new_node(For, NULL);
                                                                                add_child($$, $2);

                                                                                // Create the For block
                                                                                aux_node = new_node(Block, NULL);
                                                                                add_child(aux_node, $4);
                                                                                add_child($$, aux_node); 
                                                                            }
    | FOR LBRACE StatementAux RBRACE                                        { 
                                                                                $$ = new_node(For, NULL);
                                                                                add_child($$, $3); 
                                                                            }
    | RETURN Expr                                                           { 
                                                                                $$ = new_node(Return, NULL);
                                                                                add_child($$, $2); 
                                                                            }
    | RETURN                                                                { $$ = new_node(Return, NULL); }
    | FuncInvocation                                                        { $$ = $1; }
    | ParseArgs                                                             { $$ = $1; }
    | PRINT LPAR Expr RPAR                                                  { $$ = new_node(Print, NULL); add_child($$, $3); }
    | PRINT LPAR STRLIT RPAR                                                { $$ = new_node(Print, NULL); add_child($$, new_node(String, $3)); }
    | error                                                                 { ; }
    ;

StatementAux:
    Statement SEMICOLON StatementAux     { $$ = $1; add_brother($$, $3); }
    | /*  null production */             { $$ = NULL; }
    
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