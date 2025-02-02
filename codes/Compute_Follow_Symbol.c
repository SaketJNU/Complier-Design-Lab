/* Write a C program which reads a grammar and find FOLLOW symbols of all non-terminals */
#include<stdio.h>
#include<string.h>
intn,m=0,p,i=0,j=0;
chara[10][10],followResult[10];
voidfollow(charc);
voidfirst(charc);
voidaddToResult(char);
intmain()
{
inti;
intchoice;
charc,ch;
printf("Entertheno.ofproductions:");
scanf("%d",&n);
printf("Enter%dproductions\nProductionwithmultipletermsshouldbegiveasseparateproductions\n",n);
for(i=0;i<n;i++)
scanf("%s%c",a[i],&ch);
//gets(a[i]);
do
{
m=0;
printf("FindFOLLOWof-->");
scanf("%c",&c);
follow(c);
printf("FOLLOW(%c)={",c);
for(i=0;i<m;i++)
printf("%c",followResult[i]);
printf("}\n");
printf("Doyouwanttocontinue(Press1tocontinue....)?");
scanf("%d%c",&choice,&ch);
}
while(choice==1);
}
voidfollow(charc)
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
voidfirst(charc)
{
intk;
if(!(isupper(c)))
//f[m++]=c;
addToResult(c);
for(k=0;k<n;k++)
{
if(a[k][0]==c)
{
if(a[k][2]=='$')follow(a[i][0]);
elseif(islower(a[k][2]))
//f[m++]=a[k][2];
addToResult(a[k][2]);
elsefirst(a[k][2]);
}
}
}
voidaddToResult(charc)
{
inti;
for(i=0;i<=m;i++)
if(followResult[i]==c)
return;
followResult[m++]=c;
}

/* Input and Output */
// Enter the no.of productions:4
// Enter 4 productions
// Production with multiple terms should be give as separate productions.
// E=TD
// D=+TD
// D=$
// T=FS
// Find FOLLOW of-->E
// FOLLOW(E)={$}
// Do you want to continue (Press 1 to continue....)?1
// Find FOLLOW of-->D
// FOLLOW(D)={}
// Do you want to continue (Press 1 to continue....)?1
// Find FOLLOW of-->T
// FOLLOW(T)={+$}
// Do you want to continue (Press 1 to continue....)?^C