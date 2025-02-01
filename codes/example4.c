/*Write a program which reads the productions  display the grammar.*/


#include<stdio.h>
#include<string.h>
#define SIZE 10  

 int main () 
{  

    char production[10][SIZE];
    int num,i;
			 /* starting of the string following "->" */  

printf("Enter Number of Production : ");
scanf("%d",&num);
printf("Enter the grammar as E->E-A :\n");

 for(i=0;i<num;i++)
{  
scanf("%s",production[i]);
       }  

printf ("The productions of the grammare are \n");
printf("_____________________\n");
for(i=0;i<num;i++)
{  
    printf("%s",production[i]);
    printf("\n");

  }   
}
