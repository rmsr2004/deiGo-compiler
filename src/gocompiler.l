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

%%
{whitespace}+                   { update_column(); }
{newline}                       { update_line(); }

{digit}+                        { printf("NATURAL(%s)\n", yytext); update_column(); }
{digit}*"."{digit}+             { printf("DECIMAL(%s)\n", yytext); update_column(); }

if                              { printf("IF\n"); update_column(); }
else                            { printf("ELSE\n"); update_column(); }
then                            { printf("THEN\n"); update_column(); }
integer                         { printf("INTEGER\n"); update_column(); }
double                          { printf("DOUBLE\n"); update_column(); }

"("                             { printf("%s\n", yytext); update_column(); }
")"                             { printf("%s\n", yytext); update_column(); }
"="                             { printf("%s\n", yytext); update_column(); }
","                             { printf("%s\n", yytext); update_column(); }
"*"                             { printf("%s\n", yytext); update_column(); }
"/"                             { printf("%s\n", yytext); update_column(); }
"+"                             { printf("%s\n", yytext); update_column(); }
"-"                             { printf("%s\n", yytext); update_column(); }

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