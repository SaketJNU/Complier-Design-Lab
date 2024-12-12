%{
#include <stdio.h>
#include <stdlib.h>
%}

%% 

[a-zA-Z][a-zA-Z0-9]* {
                          /* Check for simple identifier */
                          if (yytext[strlen(yytext)-1] == '(')
                              printf("Function: %s\n", yytext);
                          else if (yytext[strlen(yytext)-1] == ']')
                              printf("Array: %s\n", yytext);
                          else if (strchr(yytext, '.') != NULL)
                              printf("Structure: %s\n", yytext);
                          else
                              printf("Variable: %s\n", yytext);
                      }

[a-zA-Z][a-zA-Z0-9]*\[.*\]   { printf("Array: %s\n", yytext); }

[a-zA-Z][a-zA-Z0-9]*\(.*\)    { printf("Function: %s\n", yytext); }

[a-zA-Z][a-zA-Z0-9]*\..*     { printf("Structure: %s\n", yytext); }

[0-9]+                    { printf("Integer Constant: %s\n", yytext); }

[0-9]+\.[0-9]+             { printf("Real Constant: %s\n", yytext); }

.                          { /* Ignore any other character */ }

%%

int main(int argc, char **argv) {
    yylex();
    return 0;
}
