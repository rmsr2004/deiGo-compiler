%{
    #include <stdio.h>
    #include <string.h>
    #include <stdarg.h>

    #define TOK_IDENTIFIER 1
    #define TOK_LITERAL 2
    #define TOK_RETURN 3
    #define TOK_RPAR_RSQ_RBRACE 4

    int last_token_type = 0;
    
    int line_index = 1, column_index = 1;

    int comment_line = 0, comment_column = 0;

    int string_line = 0, string_column = 0;
    char current_string[128] = "";
    int flag_string = 1;    // Flag to check if the string is valid (1) or not (0)

    void update_line(){
        line_index++;
        column_index = 1;        
    }
    
    void update_column(){
        column_index += yyleng;
    }

    void emit_semicolon(){
        switch(last_token_type){
            case TOK_IDENTIFIER:
            case TOK_LITERAL:
            case TOK_RETURN:
            case TOK_RPAR_RSQ_RBRACE:
                printf("SEMICOLON\n");
                break;
        }
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
newline         \n
exponent        [eE][+-]?{digit}+
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type|"++"|"--"
valid_escape    \\[fnrt\\\"]
invalid_escape  \\.|\\
line_break      \n|\r|\r\n


%X  COMMENT STRING

%%
{whitespace}+                           { update_column(); }
{newline}                               { emit_semicolon(); update_line(); }

0[xX]{hex_digit}+                       { printf("NATURAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
0{oct_digit}+                           { printf("NATURAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
0{digit}+                               { 
                                            error(line_index, column_index, "invalid octal constant (%s)", yytext);
                                            update_column(); 
                                        }
{digit}+                                { printf("NATURAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
{digit}+"."{digit}*{exponent}?          { printf("DECIMAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }
"."{digit}+{exponent}*                  { printf("DECIMAL(%s)\n", yytext); update_column(); last_token_type = TOK_LITERAL; }

"/*"                                    { BEGIN(COMMENT); save_comment_pos(); }
<COMMENT>[^*\n]+                        { update_column(); }
<COMMENT>\n                             { update_line(); }
<COMMENT>"*/"                           { BEGIN(INITIAL); update_column(); }
<COMMENT><<EOF>>                        { error(comment_line, comment_column, "unterminated comment"); BEGIN(INITIAL); }

"//".*                                  { update_line(); }

";"                                     { printf("SEMICOLON\n"); update_column(); }
","                                     { printf("COMMA\n"); update_column(); }
"_"                                     { printf("BLANKID\n"); update_column(); }
"="                                     { printf("ASSIGN\n"); update_column(); }
"*"                                     { printf("STAR\n"); update_column(); }
"/"                                     { printf("DIV\n"); update_column(); }
"-"                                     { printf("MINUS\n"); update_column(); }
"+"                                     { printf("PLUS\n"); update_column(); }
"=="                                    { printf("EQ\n"); update_column(); }
">="                                    { printf("GE\n"); update_column(); }
">"                                     { printf("GT\n"); update_column(); }
"{"                                     { printf("LBRACE\n"); update_column(); }
"<="                                    { printf("LE\n"); update_column(); }
"("                                     { printf("LPAR\n"); update_column(); }
"["                                     { printf("LSQ\n"); update_column(); }
"<"                                     { printf("LT\n"); update_column(); }
"%"                                     { printf("MOD\n"); update_column(); }
"!="                                    { printf("NE\n"); update_column(); }
"!"                                     { printf("NOT\n"); update_column(); }
"&&"                                    { printf("AND\n"); update_column(); }
"||"                                    { printf("OR\n"); update_column(); }
"}"                                     { printf("RBRACE\n"); update_column(); last_token_type = TOK_RPAR_RSQ_RBRACE; }
")"                                     { printf("RPAR\n"); update_column(); last_token_type = TOK_RPAR_RSQ_RBRACE; }
"]"                                     { printf("RSQ\n"); update_column(); last_token_type = TOK_RPAR_RSQ_RBRACE; }
"package"                               { printf("PACKAGE\n"); update_column(); }
"return"                                { printf("RETURN\n"); update_column(); last_token_type = TOK_RETURN; }
"else"                                  { printf("ELSE\n"); update_column(); }
"for"                                   { printf("FOR\n"); update_column(); }
"if"                                    { printf("IF\n"); update_column(); }
"var"                                   { printf("VAR\n"); update_column(); }
"int"                                   { printf("INT\n"); update_column(); }
"float32"                               { printf("FLOAT32\n"); update_column(); }
"bool"                                  { printf("BOOL\n"); update_column(); }
"string"                                { printf("STRING\n"); update_column(); }
"fmt.Println"                           { printf("PRINT\n"); update_column(); }
"strconv.Atoi"                          { printf("PARSEINT\n"); update_column(); }
"func"                                  { printf("FUNC\n"); update_column(); }
"os.Args"                               { printf("CMDARGS\n"); update_column(); }
{keyword}                               { printf("RESERVERD\n"); update_column(); }

({letter}|"_")({digit}|{letter}|"_")*   { 
                                            printf("IDENTIFIER(%s)\n", yytext); 
                                            update_column(); 
                                            last_token_type = TOK_IDENTIFIER;
                                        }

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
                                            if(flag_string) printf("STRLIT(\"%s\")\n", current_string); 
                                            update_column(); 
                                        }
<STRING>.                               { strcat(current_string, yytext); update_column(); }

.                                       { error(line_index, column_index, "illegal character"); update_column(); }
%%
extern int yylex();
int main(){
    yylex();    /* run the lexical analysis automaton */
    return 0;
}
int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}