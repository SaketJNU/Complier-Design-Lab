/* Write a C program find FOLLOW symbols of non-terminals in a given Grammer. */

#include<stdio.h>
#include<string.h>
#include<ctype.h>
int n,m=0,p,i=0,j=0;
char a[10][10],followResult[10];
void follow(char c);
void first(char c);
void addToResult(char c);
int main()
{
int i;
int choice;
char c, ch;
printf("Enter the no.of productions: ");
scanf("%d",&n);
printf("Enter %d productions\nProduction with multiple terms -------------\n",n);
for(i=0;i<n;i++)
scanf("%s%c",a[i],&ch);
//gets(a[i]);
do
{
m = 0;
printf("Find FOLLOW of --> ");
scanf("%c",&c);
follow(c);
printf("FOLLOW(%c)={",c);
for(i=0;i<m;i++)
printf("%c",followResult[i]);
printf("}\n");
printf("Do you want to continue (Press 1 to continue....)?");
scanf("%d%c",&choice,&ch);
}while(choice==1);
return 0;
}
void follow(char c)
{
if(a[0][0]==c)addToResult('$');
for(i=0;i<n;i++)
{
for(j=2;j<strlen(a[i]);j++)
{
if(a[i][j]==c)
{
if(a[i][j+1]!='\0')first(a[i][j+1]);
if(a[i][j+1]=='\0'&&c!=a[i][0])
follow(a[i][0]);
}
}
}
}
void first(char c)
{
int k;
if(!(isupper(c)))
//f[m++]=c;
addToResult(c);
for(k=0;k<n;k++)
{
if(a[k][0]==c)
{
if(a[k][2]=='$')follow(a[i][0]);
else if(islower(a[k][2]))
//f[m++]=a[k][2];
addToResult(a[k][2]);
else first(a[k][2]);
}
}
}
void addToResult(char c)
{
int i;
for(i=0;i<=m;i++)
if(followResult[i]==c)
return;
followResult[m++]=c;
}

/*Input and Output*/
//
//  saket@DESKTOP-2MBMJIQ:~$ ./a.out
//  Enter the no.of productions: 8
//  Enter 8 productions
//  Production with multiple terms -------------
//  E=TD
//  D=+TD
//  D=$
//  T=FS
//  S=*FS
//  S=$
//  F=(E)
//  F=a
//	Find FOLLOW of --> E
//	FOLLOW(E)={$)}
//	Do you want to continue (Press 1 to continue....)?1
//	Find FOLLOW of --> D
//	FOLLOW(D)={)}
//	Do you want to continue (Press 1 to continue....)?1
//	Find FOLLOW of --> T
//	FOLLOW(T)={+$)}
//	Do you want to continue (Press 1 to continue....)?1
//	Find FOLLOW of --> S
//	FOLLOW(S)={$)}
//	Do you want to continue (Press 1 to continue....)?1
//	Find FOLLOW of --> F
//	FOLLOW(F)={*+$)}
//	Do you want to continue (Press 1 to continue....)?1
//	Find FOLLOW of --> SD
//	FOLLOW(S)={+$)}
//	Do you want to continue (Press 1 to continue....)?Find FOLLOW of --> FOLLOW(D)={$)}
//	Do you want to continue (Press 1 to continue....)?2
	saket@DESKTOP-2MBMJIQ:~$
