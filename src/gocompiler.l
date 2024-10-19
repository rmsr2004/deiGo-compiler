%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues - 2022233032
    */

    #include <stdio.h>
    #include <stdarg.h>
    #include "y.tab.h"

    int yyparse(void);

    /*
    *   Variables and flags to control the lexical analysis
    */
    
    int line_index = 1, column_index = 1;       // Variables to store the current line and column
    int comment_line = 0, comment_column = 0;   // Variables to store the position where the comment started
    int string_line = 0, string_column = 0;     // Variables to store the position where the string started

    int flag_string = 1;                        // Flag to check if the string is valid (1) or not (0)
    int emit_semicolon = 0;                     // Flag to check if a semicolon should be emitted

    int flag = 0;                               // Flag to check if -l flag is present

    /*
    *   Updates the line and column indexes
    */
    void update_line(){
        line_index++;
        column_index = 1;
    }
    /*
    *   Updates the column index
    */
    void update_column(){
        column_index += yyleng;
    }
    /*
    *   Saves the position where the comment started
    */
    void save_comment_pos(){
        comment_line = line_index;
        comment_column = column_index;
    }
    /*
    *   Saves the position where the string started
    */
    void save_string_pos(){
        string_line = line_index;
        string_column = column_index;
    }
    /*
    *   Prints an error message
    *   Examples:
    *       - error(line_index, column_index, "invalid octal constant (%s)", yytext)
    *       - error(comment_line, comment_column, "unterminated comment")
    */
    void error(int line, int column, const char* format, ...){
        va_list args;
        va_start(args, format);

        printf("Line %d, column %d: ", line, column);
        vprintf(format, args);
        printf("\n");

        va_end(args);
    }
%}

digit           [0-9]
letter          [a-zA-Z]
hex_digit       [0-9a-fA-F]
oct_digit       [0-7]
whitespace      [ \t]
exponent        [eE][+-]?{digit}+
identifier      ({letter}|"_")({digit}|{letter}|"_")*
string 	        ["]([^\n\r\"\\]|(\\n|\\r|\\f|\\t|\\\\|\\\"))*["]
valid_escape    \\[fnrt\\\"]
invalid_escape  \\.|\\
line_break      \n|\r|\r\n
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type|"++"|"--"

%X  COMMENT STRING

%%
{whitespace}+                           { update_column(); }
{line_break}                            {
                                            if(emit_semicolon){
                                                if(flag) printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                                return SEMICOLON;
                                            }
                                            update_line();
                                        }

0[xX]{hex_digit}+                       { if(flag) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; return NATURAL; }
0{oct_digit}+                           { if(flag) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; return NATURAL; }
0{digit}+                               { 
                                            error(line_index, column_index, "invalid octal constant (%s)", yytext);
                                            update_column(); 
                                        }
{digit}+                                { if(flag) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; return NATURAL; }
{digit}+"."{digit}*{exponent}?          { if(flag) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; return DECIMAL; }
"."{digit}+{exponent}*                  { if(flag) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; return DECIMAL; }
{digit}+{exponent}                      { if(flag) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; return DECIMAL; }

"//"[^\r\n]*                            { update_column(); }

"/*"                                    { BEGIN(COMMENT); save_comment_pos(); update_column(); }
<COMMENT>\n                             { update_line(); }
<COMMENT>"*/"                           { BEGIN(INITIAL); update_column(); }
<COMMENT>.                              { update_column(); }
<COMMENT><<EOF>>                        { error(comment_line, comment_column, "unterminated comment"); yyterminate(); }

";"                                     { if(flag) printf("SEMICOLON\n"); update_column(); emit_semicolon = 0; return SEMICOLON; }
","                                     { if(flag) printf("COMMA\n"); update_column(); emit_semicolon = 0; return COMMA; }
"_"                                     { if(flag) printf("BLANKID\n"); update_column(); emit_semicolon = 0; return BLANKID; }
"="                                     { if(flag) printf("ASSIGN\n"); update_column(); emit_semicolon = 0; return ASSIGN; }
"*"                                     { if(flag) printf("STAR\n"); update_column(); emit_semicolon = 0; return STAR; }
"/"                                     { if(flag) printf("DIV\n"); update_column(); emit_semicolon = 0; return DIV; }
"-"                                     { if(flag) printf("MINUS\n"); update_column(); emit_semicolon = 0; return MINUS; }
"+"                                     { if(flag) printf("PLUS\n"); update_column(); emit_semicolon = 0; return PLUS; }
"=="                                    { if(flag) printf("EQ\n"); update_column(); emit_semicolon = 0; return EQ; }
">="                                    { if(flag) printf("GE\n"); update_column(); emit_semicolon = 0; return GE; }
">"                                     { if(flag) printf("GT\n"); update_column(); emit_semicolon = 0; return GT; }
"{"                                     { if(flag) printf("LBRACE\n"); update_column(); emit_semicolon = 0; return LBRACE; }
"<="                                    { if(flag) printf("LE\n"); update_column(); emit_semicolon = 0; return LE; }
"("                                     { if(flag) printf("LPAR\n"); update_column(); emit_semicolon = 0; return LPAR; }
"["                                     { if(flag) printf("LSQ\n"); update_column(); emit_semicolon = 0; return LSQ; }
"<"                                     { if(flag) printf("LT\n"); update_column(); emit_semicolon = 0; return LT; }
"%"                                     { if(flag) printf("MOD\n"); update_column(); emit_semicolon = 0; return MOD; }
"!="                                    { if(flag) printf("NE\n"); update_column(); emit_semicolon = 0; return NE; }
"!"                                     { if(flag) printf("NOT\n"); update_column(); emit_semicolon = 0; return NOT; }
"&&"                                    { if(flag) printf("AND\n"); update_column(); emit_semicolon = 0; return AND; }
"||"                                    { if(flag) printf("OR\n"); update_column(); emit_semicolon = 0; return OR; }
"}"                                     { if(flag) printf("RBRACE\n"); update_column(); emit_semicolon = 1; return RBRACE; }
")"                                     { if(flag) printf("RPAR\n"); update_column(); emit_semicolon = 1; return RPAR; }
"]"                                     { if(flag) printf("RSQ\n"); update_column(); emit_semicolon = 1; return RSQ; }
"package"                               { if(flag) printf("PACKAGE\n"); update_column(); emit_semicolon = 0; return PACKAGE; }
"return"                                { if(flag) printf("RETURN\n"); update_column(); emit_semicolon = 1; return RETURN; }
"else"                                  { if(flag) printf("ELSE\n"); update_column(); emit_semicolon = 0; return ELSE; }
"for"                                   { if(flag) printf("FOR\n"); update_column(); emit_semicolon = 0; return FOR; }
"if"                                    { if(flag) printf("IF\n"); update_column(); emit_semicolon = 0; return IF; }
"var"                                   { if(flag) printf("VAR\n"); update_column(); emit_semicolon = 0; return VAR; }
"int"                                   { if(flag) printf("INT\n"); update_column(); emit_semicolon = 0; return INT; }
"float32"                               { if(flag) printf("FLOAT32\n"); update_column(); emit_semicolon = 0; return FLOAT32; }
"bool"                                  { if(flag) printf("BOOL\n"); update_column(); emit_semicolon = 0; return BOOL; }
"string"                                { if(flag) printf("STRING\n"); update_column(); emit_semicolon = 0; return STRING; }
"fmt.Println"                           { if(flag) printf("PRINT\n"); update_column(); emit_semicolon = 0; return PRINT; }
"strconv.Atoi"                          { if(flag) printf("PARSEINT\n"); update_column(); emit_semicolon = 0; return PARSEINT; }
"func"                                  { if(flag) printf("FUNC\n"); update_column(); emit_semicolon = 0; return FUNC; }
"os.Args"                               { if(flag) printf("CMDARGS\n"); update_column(); emit_semicolon = 0; return CMDARGS; }
{keyword}                               { if(flag) printf("RESERVED(%s)\n", yytext); update_column(); emit_semicolon = 0; return RESERVED; }

{identifier}                            { if(flag) printf("IDENTIFIER(%s)\n", yytext); update_column(); emit_semicolon = 1; return IDENTIFIER; }

\"                                      { BEGIN(STRING); save_string_pos(); update_column();}
<STRING>{valid_escape}                  { update_column(); }
<STRING>{invalid_escape}                {
                                            error(line_index, column_index, "invalid escape sequence (%s)", yytext);
                                            update_column(); 
                                        }
<STRING><<EOF>>                         { 
                                            BEGIN(INITIAL);
                                            error(string_line, string_column, "unterminated string literal");
                                            update_column(); 
                                        }
<STRING>{line_break}                    { 
                                            BEGIN(INITIAL); 
                                            error(string_line, string_column, "unterminated string literal");
                                            update_line();
                                        }
<STRING>\"                              { BEGIN(INITIAL); update_column(); }
<STRING>.                               { update_column(); }

{string}                                { if(flag) printf("STRLIT(%s)\n", yytext); update_column(); emit_semicolon = 1; return STRLIT; }

<<EOF>>                                 { 
                                            if(emit_semicolon){
                                                if(flag) printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                            }
                                            yyterminate();
                                        }

.                                       { error(line_index, column_index, "illegal character (%s)", yytext); update_column(); }
%%
extern int yylex();
int main(int argc, char* argv[]){
    /* Check if -l flag is present */
    if(argc > 1){
        if(strcmp(argv[1], "-l") == 0){
            flag = 1;
            yylex();    /* run the lexical analysis automaton */
        }
    }

    yyparse();  /* run the syntax analysis automaton */
    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}