/* Write a program which reads a production and check for Left- Recursion (may contain in more than one alternatives) and if found eliminate it and store in another production and display the result. */
#include<stdio.h>
#include<string.h>
#define SIZE 10  

 int main () 
{  
    char non_terminal;  
    char beta,alpha[5];  
    int num,i,j=0;  
    char production[10][SIZE];  
     int index=3,k=4;			 /* starting of the string following "->" */  

printf("Enter Number of Production : ");  
scanf("%d",&num);  
printf("Enter the grammar as E->E-A :\n");  

 for(i=0;i<num;i++)
{  
scanf("%s",production[i]);  
       }  

for(i=0;i<num;i++)
{  
printf("\nGRAMMAR : : : %s",production[i]);  
non_terminal=production[i][0];  
            if(non_terminal==production[i][index]) 
	{ 
	for(j=1;production[i][k]!='|';j++)
	{
                 alpha[j]=production[i][k];
		k++;
	}
printf(" is left recursive.\n");  
                while(production[i][index]!=0 && production[i][index]!='|')  
                index++;  

  if(production[i][index]!=0) 
	{  
                      beta=production[i][index+1];  
printf("Grammar without left recursion:\n");  
printf("%c->%c%c\'",non_terminal,beta,non_terminal);  
printf("\n%c\'->",non_terminal);  
			for(j=1;alpha[j]!='\0';j++)
			printf("%c",alpha[j]);
			printf("%c\'|999",non_terminal);
                }  
                 else  
printf(" can't be reduced\n");  
            }  
            else  
printf(" is not left recursive.\n");  
            index=3;  
       }  
  }   
