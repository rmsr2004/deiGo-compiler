%{
    /*  
    *   João Afonso dos Santos Simões   -  2022236316
    *   Rodrigo Miguel Santos Rodrigues -  2022233032
    */
  
    #include <stdio.h>
    #include <stdarg.h>
    #include "y.tab.h"
    #include "ast.h"
    #include "symbols.h"

    int yyparse(void);

    extern struct node* program;
    extern int errors_count;

    /*
    *   Variables and flags to control the lexical analysis
    */
    
    int line_index = 1, column_index = 1;       // Variables to store the current line and column
    int comment_line = 0, comment_column = 0;   // Variables to store the position where the comment started
    int string_line = 0, string_column = 0;     // Variables to store the position where the string started
    int line_aux, column_aux;                   // Variables to store the position where the error occurred

    int flag_string = 1;                        // Flag to check if the string is valid (1) or not (0)
    int emit_semicolon = 0;                     // Flag to check if a semicolon should be emitted

    int flag = 0;                               // Flag to check if -l flag is present
    int eof_flag = 0;                           // Flag to check if the EOF was reached
    int error_newline = 0;                      // Flag to check if the error occurred in a new line

    /*
    *   Increments the line index and resets the column index
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
strlit 	        ["]([^\n\r\"\\]|(\\n|\\r|\\f|\\t|\\\\|\\\"))*["]
valid_escape    \\[fnrt\\\"]
invalid_escape  \\.|\\
line_break      \n|\r|\r\n
keyword         break|case|chan|const|continue|default|defer|fallthrough|go|goto|import|interface|map|range|select|struct|switch|type|"++"|"--"

%X  COMMENT_STATE STRLIT_STATE

%%
{whitespace}+                           { update_column(); }
{line_break}                            {
                                          line_aux = line_index;
                                          column_aux = column_index;
                                          update_line();
                                          if(emit_semicolon){
                                              if(flag == -1) printf("SEMICOLON\n");
                                              emit_semicolon = 0;
                                              if(flag == 2) return SEMICOLON;
                                          } else{
                                              emit_semicolon = 0;
                                          }
                                        }

0[xX]{hex_digit}+                       { if(flag == -1) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext); if(flag == 2) return NATURAL;                                          
                                        }
0{oct_digit}+                           { if(flag == -1) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1;  
                                          yylval.token = (char*) strdup(yytext); if(flag == 2) return NATURAL;                                          
                                        }
0{digit}+                               { 
                                          error(line_index, column_index, "invalid octal constant (%s)", yytext);
                                          update_column(); 
                                        }
{digit}+                                { if(flag == -1) printf("NATURAL(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext); if(flag == 2) return NATURAL;                                        
                                        }
{digit}+"."{digit}*{exponent}?          { if(flag == -1) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext);
                                          if(flag == 2) return DECIMAL;                                          
                                        }
"."{digit}+{exponent}*                  { if(flag == -1) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext);
                                          if(flag == 2) return DECIMAL;                                          
                                        }
{digit}+{exponent}                      { if(flag == -1) printf("DECIMAL(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext);
                                          if(flag == 2) return DECIMAL;                                           
                                        }

"//"[^\r\n]*                            { update_column(); }

"/*"                                    { BEGIN(COMMENT_STATE); save_comment_pos(); update_column(); }
<COMMENT_STATE>\n                       { update_line(); }
<COMMENT_STATE>"*/"                     { BEGIN(INITIAL); update_column(); }
<COMMENT_STATE>.                        { update_column(); }
<COMMENT_STATE><<EOF>>                  { 
                                          BEGIN(INITIAL);
                                          error(comment_line, comment_column, "unterminated comment"); 
                                          update_column();
                                          yyterminate(); 
                                        }

";"                                     { if(flag == -1) printf("SEMICOLON\n"); update_column(); emit_semicolon = 0; if(flag == 2) return SEMICOLON; }
","                                     { if(flag == -1) printf("COMMA\n"); update_column(); emit_semicolon = 0; if(flag == 2) return COMMA; }
"_"                                     { if(flag == -1) printf("BLANKID\n"); update_column(); emit_semicolon = 0; if(flag == 2) return BLANKID; }
"="                                     { if(flag == -1) printf("ASSIGN\n"); update_column(); emit_semicolon = 0; if(flag == 2) return ASSIGN; }
"*"                                     { if(flag == -1) printf("STAR\n"); update_column(); emit_semicolon = 0; if(flag == 2) return STAR; }
"/"                                     { if(flag == -1) printf("DIV\n"); update_column(); emit_semicolon = 0; if(flag == 2) return DIV; }
"-"                                     { if(flag == -1) printf("MINUS\n"); update_column(); emit_semicolon = 0; if(flag == 2) return MINUS; }
"+"                                     { if(flag == -1) printf("PLUS\n"); update_column(); emit_semicolon = 0; if(flag == 2) return PLUS; }
"=="                                    { if(flag == -1) printf("EQ\n"); update_column(); emit_semicolon = 0; if(flag == 2) return EQ; }
">="                                    { if(flag == -1) printf("GE\n"); update_column(); emit_semicolon = 0; if(flag == 2) return GE; }
">"                                     { if(flag == -1) printf("GT\n"); update_column(); emit_semicolon = 0; if(flag == 2) return GT; }
"{"                                     { if(flag == -1) printf("LBRACE\n"); update_column(); emit_semicolon = 0; if(flag == 2) return LBRACE; }
"<="                                    { if(flag == -1) printf("LE\n"); update_column(); emit_semicolon = 0; if(flag == 2) return LE; }
"("                                     { if(flag == -1) printf("LPAR\n"); update_column(); emit_semicolon = 0; if(flag == 2) return LPAR; }
"["                                     { if(flag == -1) printf("LSQ\n"); update_column(); emit_semicolon = 0; if(flag == 2) return LSQ; }
"<"                                     { if(flag == -1) printf("LT\n"); update_column(); emit_semicolon = 0; if(flag == 2) return LT; }
"%"                                     { if(flag == -1) printf("MOD\n"); update_column(); emit_semicolon = 0; if(flag == 2) return MOD; }
"!="                                    { if(flag == -1) printf("NE\n"); update_column(); emit_semicolon = 0; if(flag == 2) return NE; }
"!"                                     { if(flag == -1) printf("NOT\n"); update_column(); emit_semicolon = 0; if(flag == 2) return NOT; }
"&&"                                    { if(flag == -1) printf("AND\n"); update_column(); emit_semicolon = 0; if(flag == 2) return AND; }
"||"                                    { if(flag == -1) printf("OR\n"); update_column(); emit_semicolon = 0; if(flag == 2) return OR; }
"}"                                     { if(flag == -1) printf("RBRACE\n"); update_column(); emit_semicolon = 1; if(flag == 2) return RBRACE; }
")"                                     { if(flag == -1) printf("RPAR\n"); update_column(); emit_semicolon = 1; if(flag == 2) return RPAR; }
"]"                                     { if(flag == -1) printf("RSQ\n"); update_column(); emit_semicolon = 1; if(flag == 2) return RSQ; }
"package"                               { if(flag == -1) printf("PACKAGE\n"); update_column(); emit_semicolon = 0; if(flag == 2) return PACKAGE; }
"return"                                { if(flag == -1) printf("RETURN\n"); update_column(); emit_semicolon = 1; if(flag == 2) return RETURN; }
"else"                                  { if(flag == -1) printf("ELSE\n"); update_column(); emit_semicolon = 0; if(flag == 2) return ELSE; }
"for"                                   { if(flag == -1) printf("FOR\n"); update_column(); emit_semicolon = 0; if(flag == 2) return FOR; }
"if"                                    { if(flag == -1) printf("IF\n"); update_column(); emit_semicolon = 0; if(flag == 2) return IF; }
"var"                                   { if(flag == -1) printf("VAR\n"); update_column(); emit_semicolon = 0; if(flag == 2) return VAR; }
"int"                                   { if(flag == -1) printf("INT\n"); update_column(); emit_semicolon = 0; if(flag == 2) return INT; }
"float32"                               { if(flag == -1) printf("FLOAT32\n"); update_column(); emit_semicolon = 0; if(flag == 2) return FLOAT32; }
"bool"                                  { if(flag == -1) printf("BOOL\n"); update_column(); emit_semicolon = 0; if(flag == 2) return BOOL; }
"string"                                { if(flag == -1) printf("STRING\n"); update_column(); emit_semicolon = 0; if(flag == 2) return STRING; }
"fmt.Println"                           { if(flag == -1) printf("PRINT\n"); update_column(); emit_semicolon = 0; if(flag == 2) return PRINT; }
"strconv.Atoi"                          { if(flag == -1) printf("PARSEINT\n"); update_column(); emit_semicolon = 0; if(flag == 2) return PARSEINT; }
"func"                                  { if(flag == -1) printf("FUNC\n"); update_column(); emit_semicolon = 0; if(flag == 2) return FUNC; }
"os.Args"                               { if(flag == -1) printf("CMDARGS\n"); update_column(); emit_semicolon = 0; if(flag == 2) return CMDARGS; }
{keyword}                               { if(flag == -1) printf("RESERVED(%s)\n", yytext); update_column(); emit_semicolon = 0; 
                                          yylval.token = (char*) strdup(yytext); 
                                          if(flag == 2) return RESERVED;
                                        }

{identifier}                            { if(flag == -1) printf("IDENTIFIER(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext);
                                          if(flag == 2) return IDENTIFIER;
                                        }

\"                                      { BEGIN(STRLIT_STATE); save_string_pos(); update_column();}
<STRLIT_STATE>{valid_escape}            { update_column(); }
<STRLIT_STATE>{invalid_escape}          {
                                          error(line_index, column_index, "invalid escape sequence (%s)", yytext);
                                          update_column(); 
                                        }
<STRLIT_STATE><<EOF>>                   { 
                                          BEGIN(INITIAL);
                                          eof_flag = 1;
                                          error(string_line, string_column, "unterminated string literal");
                                          update_column();
                                          yyterminate();
                                        }
<STRLIT_STATE>{line_break}              { 
                                          BEGIN(INITIAL); 
                                          error(string_line, string_column, "unterminated string literal");
                                          update_line();
                                        }
<STRLIT_STATE>\"                        { BEGIN(INITIAL); update_column(); }
<STRLIT_STATE>.                         { update_column(); }

{strlit}                                { if(flag == -1) printf("STRLIT(%s)\n", yytext); update_column(); emit_semicolon = 1; 
                                          yylval.token = (char*) strdup(yytext);
                                          if(flag == 2) return STRLIT;
                                        }

<<EOF>>                                 {
                                          update_column();
                                          if(emit_semicolon){
                                              if(flag == -1) printf("SEMICOLON\n");
                                                emit_semicolon = 0;
                                              if(flag == 2) return SEMICOLON;
                                          }
                                          yyterminate();
                                        }

.                                       { error(line_index, column_index, "illegal character (%s)", yytext); update_column(); }
%%
extern int yylex();
int main(int argc, char* argv[]){
    /* Check if the -l or -t flag is present */
    if(argc > 1){
      if(strcmp(argv[1], "-l") == 0){
          flag = -1;
          yylex();    /* run the lexical analysis automaton */
      }

      if(strcmp(argv[1], "-t") == 0){
          flag = 2;
          yyparse();  /* run the syntax analysis automaton */

          if(errors_count == 0) print_ast(program, 0);
      }

      if(strcmp(argv[1], "-s") == 0){
          flag = 2;
          yyparse();  /* run the syntax analysis automaton */
          if(errors_count == 0){
              errors_count = check_program(program);
              if(errors_count == 0){
                  print_symbol_table();
                  print_ast(program, 0);
              }
          }
      }
    } else {
      flag = 2;
      yyparse();
    }

    delete_ast(program);

    return 0;
}

int yywrap() {  /* called on EOF, return 1 to terminate */
    return 1;
}

void yyerror(char* s){
    if(eof_flag){
        // EOF was reached
        printf("Line %d, column %d: %s: %s\n", line_aux, column_aux, s, yytext);
    } else if(strcmp(yytext, "\r") == 0 || strcmp(yytext, "\n") == 0){
        // Error occurred in a new line
        printf("Line %d, column %d: %s: %s\n", line_index-1, column_aux, s, yytext);
    } else {
        printf("Line %d, column %d: %s: %s\n", line_index, column_index-yyleng, s, yytext);
    }
}