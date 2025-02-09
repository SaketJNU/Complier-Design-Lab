/* Write a lex Program to Find Given Character is Keyword, Identifier, Number or 
Invalid. */ 
 
%{  
#include <stdio.h> 
%}  
%%  
if|else|while|int|switch|for|char {printf("keyword");} 
[a-z]([a-z]|[0-9])* {printf("identifier");} 
[0-9]* {printf("number");}  
.* {printf("invalid");} 
%%  
main() 
{  
yylex(); 
return 0;  
} 
int yywrap()  
{ 
}

/*Input and Output */
// saket@DESKTOP-2MBMJIQ:~$ ./a.out
// saket
// identifier
// int
// keyword
// 887
// number
// #
// invalid