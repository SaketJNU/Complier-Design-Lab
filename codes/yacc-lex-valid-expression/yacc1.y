/* A YACC program to check a valid epression using lex program */


%{
#include<stdio.h>
%}
%token NUMBER ID
%left '+' '-'
%left '*' '/'
%%
expr: expr '+' expr
|expr '-' expr
|expr '*' expr
|expr '/' expr
|'-'NUMBER
|'-'ID
|'('expr')'
|NUMBER
|ID
;
%%
main()
{
printf("Enter the expression\n");
yyparse();
printf("\nExpression is valid\n");
exit(0);
}
int yyerror(char *s)
{
printf("\nExpression is invalid");
exit(0);
}

/*

save the file as filename.l and filename.y
compile the yacc code "yacc -d filename.y"

compile the lex code "flex filename.l"
now compile c file code "cc lex.yy.c y.tab.c -ll"
execute the file "./a.out"


*/
