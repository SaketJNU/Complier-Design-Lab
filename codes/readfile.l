/* Write a lex program to read lines, characters, words in a given input file. */
%{
                 int wc = 0, cc = 0, lc = 0, bc=0;
                char infile[25];
%}

%%
\n  {lc++,cc++;}
[^ \t\n]+  {wc++,cc+=yyleng;}
"  "  {bc++,cc++;}
.  {cc++;}
%%

int main()
{
printf(" Read the Input File Name \n ");
scanf("%s",infile);
yyin=fopen(infile,"r");     
yylex();
fclose(yyin);
printf("   No.   of   Chars:   %d\n   No.   of   Words:   %d\n   No.of   Lines:   %d\n   No.   of     Blanks: %d\n",cc,wc,lc,bc); 
return 0;
}
