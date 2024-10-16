%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues - 2022233032
    */

    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>

    /*
    *   Variables and flags to control the lexical analysis
    */
    
    int line_index = 1, column_index = 1;       // Variables to store the current line and column
    int comment_line = 0, comment_column = 0;   // Variables to store the position where the comment started
    int string_line = 0, string_column = 0;     // Variables to store the position where the string started

    char current_string[128] = "";              // Buffer to store the current string

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
    *   Clears the string buffer
    */
    void clear_string(){
        memset(current_string, 0, sizeof(current_string));
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
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type|"++"|"--"
valid_escape    \\[fnrt\\\"]
invalid_escape  \\.|\\
line_break      \n|\r|\r\n

%X  COMMENT STRING

%%
{whitespace}+                           { update_column(); }
{line_break}                            {
                                            if(emit_semicolon){
                                                if(flag) printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                            }
                                            update_line();
                                        }

0[xX]{hex_digit}+                       { if(flag) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
0{oct_digit}+                           { if(flag) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
0{digit}+                               { 
                                            error(line_index, column_index, "invalid octal constant (%s)", yytext);
                                            update_column(); 
                                        }
{digit}+                                { if(flag) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
{digit}+"."{digit}*{exponent}?          { if(flag) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
"."{digit}+{exponent}*                  { if(flag) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
{digit}+{exponent}                      { if(flag) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }

"//"[^\r\n]*                            { update_column(); }

"/*"                                    { BEGIN(COMMENT); save_comment_pos(); update_column(); }
<COMMENT>\n                             { update_line(); }
<COMMENT>"*/"                           { BEGIN(INITIAL); update_column(); }
<COMMENT>.                              { update_column(); }
<COMMENT><<EOF>>                        { error(comment_line, comment_column, "unterminated comment"); yyterminate(); }

";"                                     { if(flag) printf("SEMICOLON\n"); update_column(); emit_semicolon = 0; }
","                                     { if(flag) printf("COMMA\n"); update_column(); emit_semicolon = 0; }
"_"                                     { if(flag) printf("BLANKID\n"); update_column(); emit_semicolon = 0; }
"="                                     { if(flag) printf("ASSIGN\n"); update_column(); emit_semicolon = 0; }
"*"                                     { if(flag) printf("STAR\n"); update_column(); emit_semicolon = 0; }
"/"                                     { if(flag) printf("DIV\n"); update_column(); emit_semicolon = 0; }
"-"                                     { if(flag) printf("MINUS\n"); update_column(); emit_semicolon = 0; }
"+"                                     { if(flag) printf("PLUS\n"); update_column(); emit_semicolon = 0; }
"=="                                    { if(flag) printf("EQ\n"); update_column(); emit_semicolon = 0; }
">="                                    { if(flag) printf("GE\n"); update_column(); emit_semicolon = 0; }
">"                                     { if(flag) printf("GT\n"); update_column(); emit_semicolon = 0; }
"{"                                     { if(flag) printf("LBRACE\n"); update_column(); emit_semicolon = 0; }
"<="                                    { if(flag) printf("LE\n"); update_column(); emit_semicolon = 0;  }
"("                                     { if(flag) printf("LPAR\n"); update_column(); emit_semicolon = 0; }
"["                                     { if(flag) printf("LSQ\n"); update_column(); emit_semicolon = 0; }
"<"                                     { if(flag) printf("LT\n"); update_column(); emit_semicolon = 0; }
"%"                                     { if(flag) printf("MOD\n"); update_column(); emit_semicolon = 0; }
"!="                                    { if(flag) printf("NE\n"); update_column(); emit_semicolon = 0; }
"!"                                     { if(flag) printf("NOT\n"); update_column(); emit_semicolon = 0; }
"&&"                                    { if(flag) printf("AND\n"); update_column(); emit_semicolon = 0; }
"||"                                    { if(flag) printf("OR\n"); update_column(); emit_semicolon = 0; }
"}"                                     { if(flag) printf("RBRACE\n"); update_column(); emit_semicolon = 1; }
")"                                     { if(flag) printf("RPAR\n"); update_column(); emit_semicolon = 1; }
"]"                                     { if(flag) printf("RSQ\n"); update_column(); emit_semicolon = 1; }
"package"                               { if(flag) printf("PACKAGE\n"); update_column(); emit_semicolon = 0; }
"return"                                { if(flag) printf("RETURN\n"); update_column(); emit_semicolon = 1; }
"else"                                  { if(flag) printf("ELSE\n"); update_column(); emit_semicolon = 0; }
"for"                                   { if(flag) printf("FOR\n"); update_column(); emit_semicolon = 0; }
"if"                                    { if(flag) printf("IF\n"); update_column(); emit_semicolon = 0; }
"var"                                   { if(flag) printf("VAR\n"); update_column(); emit_semicolon = 0; }
"int"                                   { if(flag) printf("INT\n"); update_column(); emit_semicolon = 0; }
"float32"                               { if(flag) printf("FLOAT32\n"); update_column(); emit_semicolon = 0; }
"bool"                                  { if(flag) printf("BOOL\n"); update_column(); emit_semicolon = 0; }
"string"                                { if(flag) printf("STRING\n"); update_column(); emit_semicolon = 0; }
"fmt.Println"                           { if(flag) printf("PRINT\n"); update_column(); emit_semicolon = 0; }
"strconv.Atoi"                          { if(flag) printf("PARSEINT\n"); update_column(); emit_semicolon = 0; }
"func"                                  { if(flag) printf("FUNC\n"); update_column(); emit_semicolon = 0; }
"os.Args"                               { if(flag) printf("CMDARGS\n"); update_column(); emit_semicolon = 0; }
{keyword}                               { if(flag) printf("RESERVED(%s)\n", yytext); update_column(); emit_semicolon = 0; }

{identifier}                            { if(flag) printf("IDENTIFIER(%s)\n", yytext); update_column(); emit_semicolon = 1; }

\"                                      { 
                                            BEGIN(STRING); 
                                            flag_string = 1; 
                                            save_string_pos();
                                            clear_string(); 
                                            update_column();
                                        }
<STRING>{valid_escape}                  { strcat(current_string, yytext); update_column(); }
<STRING>{invalid_escape}                {
                                            error(line_index, column_index, "invalid escape sequence (%s)", yytext);
                                            flag_string = 0;
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
<STRING>\"                              { 
                                            BEGIN(INITIAL); 
                                            if(flag_string ){
                                                if(flag) printf("STRLIT(\"%s\")\n", current_string);
                                                emit_semicolon = 1;
                                            } 
                                            update_column();
                                        }
<STRING>.                               { strcat(current_string, yytext); update_column(); }

<<EOF>>                                 { 
                                            if(emit_semicolon){
                                                if(flag) printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                            }
                                            return 0; 
                                        }

.                                       { error(line_index, column_index, "illegal character (%s)", yytext); update_column(); }
%%
extern int yylex();
int main(int argc, char* argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "-l") == 0){
            flag = 1;
        }
    }
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}