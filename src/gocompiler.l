%{
    int line_index = 1;
    int column_index = 1;

    void update_line(){
        line_index++;
        column_index = 1;        
    }
    void update_column(){
        column_index += yyleng;
    }
%}

digit           [0-9]
letter          [a-zA-Z]
whitespace      [ \t]
newline         \n
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type

%%
{whitespace}+                   { update_column(); }
{newline}                       { update_line(); }

{digit}+                        { printf("NATURAL(%s)\n", yytext); update_column(); }
{digit}*"."{digit}+             { printf("DECIMAL(%s)\n", yytext); update_column(); }

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