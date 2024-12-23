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
    struct node* aux_node2;

    int errors_count = 0;
%}

%union{
    struct token* token;
    struct node* node;
}

%token<token>   SEMICOLON COMMA BLANKID ASSIGN STAR DIV MINUS PLUS EQ GE GT LBRACE LE LPAR LSQ LT MOD NE NOT AND OR 
%token<token>   RBRACE RPAR RSQ PACKAGE RETURN ELSE FOR IF VAR INT FLOAT32 BOOL STRING PRINT PARSEINT FUNC CMDARGS
%token<token>   IDENTIFIER STRLIT NATURAL DECIMAL RESERVED

%left   COMMA
%right  ASSIGN
%left   OR
%left   AND  
%left   LT GT LE GE  EQ NE
%left   PLUS MINUS
%left   STAR DIV MOD
%right  NOT

%nonassoc ELSE_IF
%nonassoc ELSE
%nonassoc RPAR LPAR LSQ RSQ

%type<node> Program Declarations VarDeclaration VarSpec VarSpecAux Type FuncDeclaration Parameters ParametersAux FuncBody VarsAndStatements Statement
%type<node> StatementAux ParseArgs FuncInvocation FuncInvocationAux Expr

%%

Program:
    PACKAGE IDENTIFIER SEMICOLON Declarations   { $$ = program = new_node(Program, NULL, NULL); add_child(program, $4); }
    ;

Declarations:
    VarDeclaration SEMICOLON Declarations           { $$ = $1; add_brother($$, $3); }
    | FuncDeclaration SEMICOLON Declarations        { $$ = $1; add_brother($$, $3); }
    | /*  null production */                        { $$ = NULL; }

VarDeclaration:
    VAR VarSpec                               { $$ = $2; }
    | VAR LPAR VarSpec SEMICOLON RPAR         { $$ = $3; }
    ;

VarSpec:
    IDENTIFIER VarSpecAux Type             {    
                                                $$ = new_node(VarDecl, NULL, NULL); 
                                                add_child($$, $3); 
                                                add_child($$, new_node(Identifier, $1->value, $1)); 

                                                add_type_to_brothers($2, $3->token->category);   // Add the type to all the brothers
                                                
                                                add_brother($$, $2);
                                            }
    ;

VarSpecAux:
    COMMA IDENTIFIER VarSpecAux     { 
                                        $$ = new_node(VarDecl, NULL, NULL); 
                                        add_child($$, new_node(Identifier, $2->value, $2)); 
                                        add_brother($$, $3);
                                    }
    | /*  null production */        { $$ = NULL; }
    ;

Type:
    INT               { $$ = new_node(Int, NULL, NULL); }
    | FLOAT32         { $$ = new_node(Float32, NULL, NULL); }
    | BOOL            { $$ = new_node(Bool, NULL, NULL); }
    | STRING          { $$ = new_node(String, NULL, NULL); }
    ;

FuncDeclaration:
    FUNC IDENTIFIER LPAR Parameters RPAR Type FuncBody  {   
                                                            $$ = new_node(FuncDecl, NULL, NULL);

                                                            // Create the FuncHeader node (Identifier, FuncParams, Type)
                                                            aux_node = new_node(FuncHeader, NULL, NULL);
                                                            add_child(aux_node, new_node(Identifier, $2->value, $2));
                                                            add_child(aux_node, $6);
                                                            add_child(aux_node, $4);

                                                            add_child($$, aux_node);
                                                            add_child($$, $7);
                                                        }
    | FUNC IDENTIFIER LPAR RPAR FuncBody                { 
                                                            $$ = new_node(FuncDecl, NULL, NULL);

                                                            // Create the FuncHeader node (Identifier, FuncParams = NULL)
                                                            aux_node = new_node(FuncHeader, NULL, NULL); 
                                                            add_child(aux_node, new_node(Identifier, $2->value, $2));
                                                            add_child(aux_node, new_node(FuncParams, NULL, NULL));

                                                            add_child($$, aux_node);
                                                            add_child($$, $5);
                                                        }
    | FUNC IDENTIFIER LPAR Parameters RPAR FuncBody     { 
                                                            $$ = new_node(FuncDecl, NULL, NULL);

                                                            // Create the FuncHeader node (Identifier, FuncParams)
                                                            aux_node = new_node(FuncHeader, NULL, NULL);                                                            
                                                            add_child(aux_node, new_node(Identifier, $2->value, $2));
                                                            add_child(aux_node, $4);

                                                            add_child($$, aux_node);
                                                            add_child($$, $6);
                                                        }
    | FUNC IDENTIFIER LPAR RPAR Type FuncBody           { 
                                                            $$ = new_node(FuncDecl, NULL, NULL);
                                                            
                                                            // Create the FuncHeader node (Identifier, FuncParams = NULL, Type)
                                                            aux_node = new_node(FuncHeader, NULL, NULL);
                                                            add_child(aux_node, new_node(Identifier, $2->value, $2));
                                                            add_child(aux_node, $5);
                                                            add_child(aux_node, new_node(FuncParams, NULL, NULL));

                                                            add_child($$, aux_node);
                                                            add_child($$, $6);
                                                        }
    ;

Parameters:
    IDENTIFIER Type ParametersAux   { 
                                        $$ = new_node(FuncParams, NULL, NULL); 

                                        // Create ParamDecl node (Identifier, Type)
                                        aux_node = new_node(ParamDecl, NULL, NULL);
                                        add_child(aux_node, $2); 
                                        add_child(aux_node, new_node(Identifier, $1->value, $1)); 

                                        add_child($$, aux_node);
                                        add_child($$, $3);
                                    }
    ;

ParametersAux:
    COMMA IDENTIFIER Type ParametersAux     { 
                                                $$ = new_node(ParamDecl, NULL, NULL);
                                                add_child($$, $3); 
                                                add_child($$, new_node(Identifier, $2->value, $2)); 
                                                add_brother($$, $4);
                                            }
    | /*  null production */                { $$ = NULL; }

FuncBody:
    LBRACE VarsAndStatements RBRACE     { $$ = new_node(FuncBody, NULL, NULL); add_child($$, $2); }
    ;

VarsAndStatements:
    VarsAndStatements VarDeclaration SEMICOLON      { if($1 == NULL) { $$ = $2; } else { $$ = $1; add_brother($1, $2); } }
    | VarsAndStatements Statement SEMICOLON         { if($1 == NULL) { $$ = $2; } else { $$ = $1; add_brother($1, $2); } }
    | VarsAndStatements SEMICOLON                   { $$ = $1; }
    | /* null production */                        { $$ = NULL; }
    ;

Statement: 
    IDENTIFIER ASSIGN Expr                                                  { 
                                                                                $$ = new_node(Assign, NULL, $2);
                                                                                add_child($$, new_node(Identifier, $1->value, $1));
                                                                                add_child($$, $3);
                                                                            }
    | LBRACE StatementAux RBRACE                                            {
                                                                                if($2 == NULL){
                                                                                    $$ = NULL;
                                                                                } else {
                                                                                    if(count_brothers($2) > 1){
                                                                                        $$ = new_node(Block, NULL, NULL);
                                                                                        add_child($$, $2); 
                                                                                    } else { 
                                                                                        $$ = $2; 
                                                                                    }
                                                                                }
                                                                            }
    | IF Expr LBRACE StatementAux RBRACE ELSE LBRACE StatementAux RBRACE    {
                                                                                $$ = new_node(If, NULL, $1);

                                                                                // Create the If block
                                                                                aux_node = new_node(Block, NULL, NULL);
                                                                                add_child(aux_node, $4);

                                                                                // Create the Else block
                                                                                aux_node2 = new_node(Block, NULL, NULL);
                                                                                add_child(aux_node2, $8);

                                                                                add_child($$, $2);
                                                                                add_child($$, aux_node);
                                                                                add_child($$, aux_node2);
                                                                            }
    | IF Expr LBRACE StatementAux RBRACE %prec ELSE_IF                      { 
                                                                                $$ = new_node(If, NULL, $1);

                                                                                // Create the If block
                                                                                aux_node = new_node(Block, NULL, NULL);
                                                                                add_child(aux_node, $4);

                                                                                add_child($$, $2);
                                                                                add_child($$, aux_node);
                                                                                add_child($$, new_node(Block, NULL, NULL));
                                                                            }
    | FOR Expr LBRACE StatementAux RBRACE                                   { 
                                                                                $$ = new_node(For, NULL, $1);

                                                                                // Create the For block
                                                                                aux_node = new_node(Block, NULL, NULL);
                                                                                add_child(aux_node, $4);

                                                                                add_child($$, $2);
                                                                                add_child($$, aux_node); 
                                                                            }
    | FOR LBRACE StatementAux RBRACE                                        { 
                                                                                $$ = new_node(For, NULL, $1);

                                                                                // Create the For block
                                                                                aux_node = new_node(Block, NULL, NULL);
                                                                                add_child(aux_node, $3);

                                                                                add_child($$, aux_node); 
                                                                            }
    | RETURN Expr                                                           { $$ = new_node(Return, NULL, NULL); add_child($$, $2); }
    | RETURN                                                                { $$ = new_node(Return, NULL, $1); }
    | FuncInvocation                                                        { $$ = $1; }
    | ParseArgs                                                             { $$ = $1; }
    | PRINT LPAR Expr RPAR                                                  { $$ = new_node(Print, NULL, $1); add_child($$, $3); }
    | PRINT LPAR STRLIT RPAR                                                { $$ = new_node(Print, NULL, $1); add_child($$, new_node(StrLit, $3->value, $3)); }
    | error                                                                 { errors_count++; $$ = NULL; }
    ;

StatementAux:
    Statement SEMICOLON StatementAux     { if($$ == NULL){ $$ = $3; } else { $$ = $1; add_brother($1, $3); } }
    | /*  null production */             { $$ = NULL; }
    
ParseArgs:
    IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR CMDARGS LSQ Expr RSQ RPAR     {   
                                                                                    $$ = new_node(ParseArgs, NULL, $5);

                                                                                    aux_node = new_node(Identifier, $1->value, $1);
                                                                                    add_brother(aux_node, $9); 

                                                                                    add_child($$, aux_node);
                                                                                }
    | IDENTIFIER COMMA BLANKID ASSIGN PARSEINT LPAR error RPAR                  { errors_count++; $$ = NULL; }
    ;

FuncInvocation:
    IDENTIFIER LPAR Expr FuncInvocationAux RPAR     {
                                                        $$ = new_node(Call, NULL, $1);

                                                        aux_node = new_node(Identifier, $1->value, $1);
                                                        add_brother(aux_node, $3);
                                                        add_brother(aux_node, $4);

                                                        add_child($$, aux_node);
                                                    }
    | IDENTIFIER LPAR RPAR                          { 
                                                        $$ = new_node(Call, NULL, $1); 
                                                        add_child($$, new_node(Identifier, $1->value, $1));
                                                    }
    | IDENTIFIER LPAR error RPAR                    { errors_count++; $$ = NULL; }
    ;

FuncInvocationAux:
    COMMA Expr FuncInvocationAux     { $$ = $2; add_brother($$, $3); }
    | /*  null production */         { $$ = NULL; }

Expr:
    Expr OR Expr                    { $$ = new_node(Or, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr AND Expr                 { $$ = new_node(And, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr LT Expr                  { $$ = new_node(Lt, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr GT Expr                  { $$ = new_node(Gt, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr EQ Expr                  { $$ = new_node(Eq, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr NE Expr                  { $$ = new_node(Ne, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr LE Expr                  { $$ = new_node(Le, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr GE Expr                  { $$ = new_node(Ge, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr PLUS Expr                { $$ = new_node(Add, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr MINUS Expr               { $$ = new_node(Sub, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr STAR Expr                { $$ = new_node(Mul, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr DIV Expr                 { $$ = new_node(Div, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | Expr MOD Expr                 { $$ = new_node(Mod, NULL, $2); add_child($$, $1); add_child($$, $3); }
    | NOT Expr   %prec NOT          { $$ = new_node(Not, NULL, $1); add_child($$, $2); }
    | MINUS Expr %prec NOT          { $$ = new_node(Minus, NULL, $1); add_child($$, $2); }
    | PLUS Expr  %prec NOT          { $$ = new_node(Plus, NULL, $1); add_child($$, $2); }
    | NATURAL                       { $$ = new_node(Natural, $1->value, $1); }
    | DECIMAL                       { $$ = new_node(Decimal, $1->value, $1); }
    | IDENTIFIER                    { $$ = new_node(Identifier, $1->value, $1); }
    | FuncInvocation                { $$ = $1; }
    | LPAR Expr RPAR                { $$ = $2; }
    | LPAR error RPAR               { errors_count++; $$ = NULL; }
    ;
%%