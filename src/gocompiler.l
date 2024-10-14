%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues - 2022233032
    */

    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>
    
    int line_index = 1, column_index = 1;

    int comment_line = 0, comment_column = 0;

    int string_line = 0, string_column = 0;
    char current_string[128] = "";
    int flag_string = 1;    // Flag to check if the string is valid (1) or not (0)

    int emit_semicolon = 0;

    void update_line(){
        line_index++;
        column_index = 1;
    }
    
    void update_column(){
        column_index += yyleng;
    }

    void save_comment_pos(){
        comment_line = line_index;
        comment_column = column_index;
    }

    void save_string_pos(){
        string_line = line_index;
        string_column = column_index;
    }

    void clear_string(){
        memset(current_string, 0, sizeof(current_string));
    }

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
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type|"++"|"--"
valid_escape    \\[fnrt\\\"]
invalid_escape  \\.|\\
line_break      \n|\r|\r\n


%X  COMMENT STRING

%%
{whitespace}+                           { update_column(); }
{line_break}                            {
                                            if(emit_semicolon){
                                                printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                            }
                                            update_line();
                                        }

0[xX]{hex_digit}+                       { printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
0{oct_digit}+                           { printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
0{digit}+                               { 
                                            error(line_index, column_index, "invalid octal constant (%s)", yytext);
                                            update_column(); 
                                        }
{digit}+                                { printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
{digit}+"."{digit}*{exponent}?          { printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
"."{digit}+{exponent}*                  { printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }
{digit}+{exponent}                      { printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; }

"//"[^\r\n]*                            { update_column(); }

"/*"                                    { BEGIN(COMMENT); save_comment_pos(); update_column(); }
<COMMENT>\n                             { update_line(); }
<COMMENT>"*/"                           { BEGIN(INITIAL); update_column(); }
<COMMENT>.                              { update_column(); }
<COMMENT><<EOF>>                        { error(comment_line, comment_column, "unterminated comment"); yyterminate(); }

";"                                     { printf("SEMICOLON\n"); update_column(); emit_semicolon = 0; }
","                                     { printf("COMMA\n"); update_column(); emit_semicolon = 0; }
"_"                                     { printf("BLANKID\n"); update_column(); emit_semicolon = 0; }
"="                                     { printf("ASSIGN\n"); update_column(); emit_semicolon = 0; }
"*"                                     { printf("STAR\n"); update_column(); emit_semicolon = 0; }
"/"                                     { printf("DIV\n"); update_column(); emit_semicolon = 0; }
"-"                                     { printf("MINUS\n"); update_column(); emit_semicolon = 0; }
"+"                                     { printf("PLUS\n"); update_column(); emit_semicolon = 0; }
"=="                                    { printf("EQ\n"); update_column(); emit_semicolon = 0; }
">="                                    { printf("GE\n"); update_column(); emit_semicolon = 0; }
">"                                     { printf("GT\n"); update_column(); emit_semicolon = 0; }
"{"                                     { printf("LBRACE\n"); update_column(); emit_semicolon = 0; }
"<="                                    { printf("LE\n"); update_column(); emit_semicolon = 0;  }
"("                                     { printf("LPAR\n"); update_column(); emit_semicolon = 0; }
"["                                     { printf("LSQ\n"); update_column(); emit_semicolon = 0; }
"<"                                     { printf("LT\n"); update_column(); emit_semicolon = 0; }
"%"                                     { printf("MOD\n"); update_column(); emit_semicolon = 0; }
"!="                                    { printf("NE\n"); update_column(); emit_semicolon = 0; }
"!"                                     { printf("NOT\n"); update_column(); emit_semicolon = 0; }
"&&"                                    { printf("AND\n"); update_column(); emit_semicolon = 0; }
"||"                                    { printf("OR\n"); update_column(); emit_semicolon = 0; }
"}"                                     { printf("RBRACE\n"); update_column(); emit_semicolon = 1; }
")"                                     { printf("RPAR\n"); update_column(); emit_semicolon = 1; }
"]"                                     { printf("RSQ\n"); update_column(); emit_semicolon = 1; }
"package"                               { printf("PACKAGE\n"); update_column(); emit_semicolon = 0; }
"return"                                { printf("RETURN\n"); update_column(); emit_semicolon = 1; }
"else"                                  { printf("ELSE\n"); update_column(); emit_semicolon = 0; }
"for"                                   { printf("FOR\n"); update_column(); emit_semicolon = 0; }
"if"                                    { printf("IF\n"); update_column(); emit_semicolon = 0; }
"var"                                   { printf("VAR\n"); update_column(); emit_semicolon = 0; }
"int"                                   { printf("INT\n"); update_column(); emit_semicolon = 0; }
"float32"                               { printf("FLOAT32\n"); update_column(); emit_semicolon = 0; }
"bool"                                  { printf("BOOL\n"); update_column(); emit_semicolon = 0; }
"string"                                { printf("STRING\n"); update_column(); emit_semicolon = 0; }
"fmt.Println"                           { printf("PRINT\n"); update_column(); emit_semicolon = 0; }
"strconv.Atoi"                          { printf("PARSEINT\n"); update_column(); emit_semicolon = 0; }
"func"                                  { printf("FUNC\n"); update_column(); emit_semicolon = 0; }
"os.Args"                               { printf("CMDARGS\n"); update_column(); emit_semicolon = 0; }
{keyword}                               { printf("RESERVED(%s)\n", yytext); update_column(); emit_semicolon = 0; }

({letter}|"_")({digit}|{letter}|"_")*   { printf("IDENTIFIER(%s)\n", yytext); update_column(); emit_semicolon = 1; }

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
                                            if(flag_string){
                                                printf("STRLIT(\"%s\")\n", current_string);
                                                emit_semicolon = 1;
                                            } 
                                            update_column();
                                            
                                        }
<STRING>.                               { strcat(current_string, yytext); update_column(); }

<<EOF>>                                 { 
                                            if(emit_semicolon){
                                                printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                            }
                                            return 0; 
                                        }

.                                       { error(line_index, column_index, "illegal character (%s)", yytext); update_column(); }
%%
extern int yylex();
int main(){
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}