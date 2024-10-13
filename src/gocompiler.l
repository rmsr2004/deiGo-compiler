%{
    int line_index = 1;
    int column_index = 1;
    
    int last_token_type = 0;
    #define TOK_IDENTIFIER 1
    #define TOK_LITERAL 2
    #define TOK_RETURN 3
    #define TOK_RPAR_RSQ_RBRACE 4


    void update_line(){
        line_index++;
        column_index = 1;        
    }
    void update_column(){
        column_index += yyleng;
    }
    void emit_semicolon_if_needed(){
        if (last_token_type == TOK_IDENTIFIER || 
            last_token_type == TOK_LITERAL || 
            last_token_type == TOK_RETURN || 
            last_token_type == TOK_RPAR_RSQ_RBRACE) {
            printf("SEMICOLON\n");
        }
    }
%}

digit           [0-9]
letter          [a-zA-Z]
hex_digit       [0-9a-fA-F]
oct_digit       [0-7]
whitespace      [ \t]
newline         \n
exponent        [eE][+-]?{digit}+
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type

%%
{whitespace}+                   { update_column(); }
{newline}                       { emit_semicolon_if_needed(); update_line(); }

0[xX]{hex_digit}+               { printf("HEX(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
0{oct_digit}+                   { printf("OCTAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
0{digit}+                       { printf("Line %d, column %d: invalid octal constant (%s)\n", line_index, column_index, yytext);
                                  update_column(); }
{digit}+                        { printf("NATURAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
{digit}+"."{digit}*{exponent}?  { printf("DECIMAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
"."{digit}+{exponent}*          { printf("DECIMAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }

"return"                        { printf("RETURN\n"); update_column(); last_token_type = TOK_RETURN; }

{letter}({digit}|{letter})*     { printf("IDENTIFIER(%s)\n", yytext); update_column(); last_token_type = TOK_IDENTIFIER; }

")"                             { printf("RPAR\n"); update_column(); last_token_type = TOK_RPAR_RSQ_RBRACE; }
"]"                             { printf("RSQ\n"); update_column(); last_token_type = TOK_RPAR_RSQ_RBRACE; }
"}"                             { printf("RBRACE\n"); update_column(); last_token_type = TOK_RPAR_RSQ_RBRACE; }



";"                             { printf("SEMICOLON\n"); update_column(); }
","                             { printf("COMMA\n"); update_column(); }
"_"                             { printf("BLANKID\n"); update_column(); }
"="                             { printf("ASSIGN\n"); update_column(); }
"*"                             { printf("STAR\n"); update_column(); }
"/"                             { printf("DIV\n"); update_column(); }
"-"                             { printf("MINUS\n"); update_column(); }
"+"                             { printf("PLUS\n"); update_column(); }
"=="                            { printf("EQ\n"); update_column(); }
">="                            { printf("GE\n"); update_column(); }
">"                             { printf("GT\n"); update_column(); }
"{"                             { printf("LBRACE\n"); update_column(); }
"<="                            { printf("LE\n"); update_column(); }
"("                             { printf("LPAR\n"); update_column(); }
"["                             { printf("LSQ\n"); update_column(); }
"<"                             { printf("LT\n"); update_column(); }
"%"                             { printf("MOD\n"); update_column(); }
"!="                            { printf("NE\n"); update_column(); }
"!"                             { printf("NOT\n"); update_column(); }
"&&"                            { printf("AND\n"); update_column(); }
"||"                            { printf("OR\n"); update_column(); }
"}"                             { printf("RBRACE\n"); update_column(); }
")"                             { printf("RPAR\n"); update_column(); }
"]"                             { printf("RSQ\n"); update_column(); }
"package"                       { printf("PACKAGE\n"); update_column(); }
"return"                        { printf("RETURN\n"); update_column(); }
"else"                          { printf("ELSE\n"); update_column(); }
"for"                           { printf("FOR\n"); update_column(); }
"if"                            { printf("IF\n"); update_column(); }
"var"                           { printf("VAR\n"); update_column(); }
"int"                           { printf("INT\n"); update_column(); }
"float32"                       { printf("FLOAT32\n"); update_column(); }
"bool"                          { printf("BOOL\n"); update_column(); }
"string"                        { printf("STRING\n"); update_column(); }
"fmt.Println"                   { printf("PRINT\n"); update_column(); }
"strconv.Atoi"                  { printf("PARSEINT\n"); update_column(); }
"func"                          { printf("FUNC\n"); update_column(); }
"os.Args"                       { printf("CMDARGS\n"); update_column(); }
{keyword}                       { printf("RESERVERD\n"); update_column(); }


{letter}({digit}|{letter})*     { printf("IDENTIFIER(%s)\n", yytext); update_column(); }

.                               { printf("\nLine %d, column %d: unrecognized character (%s)\n", line_index, column_index, yytext); update_column(); }
%%
extern int yylex();
int main() {
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}