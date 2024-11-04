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
%type<node> StatementAux ParseArgs FuncInvocation  FuncInvocationAux Expr

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
    VarsAndStatements VarDeclaration SEMICOLON  { $$ = $1; add_brother($1,$2); }
    | VarsAndStatements Statement SEMICOLON     { $$ = $1; add_brother($1,$2); }
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
    IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR       {$$=new_node(ParseArgs, NULL); aux_node = new_node(Identifier, $1); add_child($$, aux_node); add_brother(aux_node, $9);} 
    | IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                    { ; }
    ;

FuncInvocation:
    
    IDENTIFIER LPAR RPAR                          { $$ = new_node(Call, NULL); aux_node=new_node(Identifier,$1); add_child($$,aux_node); } 
    | IDENTIFIER LPAR Expr FuncInvocationAux RPAR   { $$ = new_node(Call, NULL); aux_node=new_node(Identifier,$1); add_child($$,aux_node); add_brother(aux_node,$3); add_brother($3, $4); } 
    | IDENTIFIER LPAR error RPAR                  { ; }
    ;

FuncInvocationAux:
    COMMA Expr FuncInvocationAux     { $$ =  $2; add_brother( $2,$3); }
    | /*  null production */         { $$ = NULL; }

Expr:
    Expr OR Expr                    { $$ = new_node(Or, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr AND Expr                 { $$ = new_node(And, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr LT Expr                  { $$ = new_node(Lt, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr GT Expr                  { $$ = new_node(Gt, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr EQ Expr                  { $$ = new_node(Eq, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr NE Expr                  { $$ = new_node(Ne, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr LE Expr                  { $$ = new_node(Le, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr GE Expr                  { $$ = new_node(Ge, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr PLUS Expr                { $$ = new_node(Add, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr MINUS Expr               { $$ = new_node(Sub, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr STAR Expr                { $$ = new_node(Mul, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr DIV Expr                 { $$ = new_node(Div, NULL); add_child($$, $1); add_child($$, $3); }
    | Expr MOD Expr                 { $$ = new_node(Mod, NULL); add_child($$, $1); add_child($$, $3); }
    | NOT Expr                      { $$ = new_node(Not, NULL); add_child($$, $2); }
    | MINUS Expr                    { $$ = new_node(Sub, NULL); add_child($$, $2); }
    | PLUS Expr                     { $$ = new_node(Add, NULL); add_child($$, $2); }
    | NATURAL                       { $$ = new_node(Natural, $1); }
    | DECIMAL                       { $$ = new_node(Float32, $1); }
    | IDENTIFIER                    { $$ = new_node(Identifier, $1); }
    | FuncInvocation                { $$ = $1; }
    | LPAR Expr RPAR                { $$ = $2; }
    | LPAR error RPAR               { ; }
    ;
%%
