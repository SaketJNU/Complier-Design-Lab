/* Implement the C Program for identifying constant and classify whether it is integer or real. */
#include<stdio.h>
#include<string.h>
int main()
{
int state=0,i=0;
char a[20];
printf("enter the input ending with X = ");
gets(a);
int n=strlen(a);

while(i<=n)
{
switch(state)
{
 case 0: 
  if(a[i]=='X')
  {
state=6;break;
}
 else if(a[i]=='0'||a[i]=='1'||a[i]=='2'||a[i]=='3'||a[i]=='4'||a[i]=='5'||a[i]=='6'||a[i]=='7'||a[i]=='8'||a[i]=='9')
 {
 state=1;break;}
 else
 {state=6;break;}
 case 1:
    if(a[i]=='X')
     {state=2;break;}
      else if(a[i]=='0'||a[i]=='1'||a[i]=='2'||a[i]=='3'||a[i]=='4'||a[i]=='5'||a[i]=='6'||a[i]=='7'||a[i]=='8'||a[i]=='9')
     {
     state=1;break;}
     else if(a[i]=='.')
{ state=3;break;}
     else{state=6;break;}
case 2:
printf("it is a integer");return 0;
case 3:
    if(a[i]=='X')
      {state=6;break;}
     else if(a[i]=='0'||a[i]=='1'||a[i]=='2'||a[i]=='3'||a[i]=='4'||a[i]=='5'||a[i]=='6'||a[i]=='7'||a[i]=='8'||a[i]=='9')
     {
     state=4;break;}
     else
     {state=6;break;}
case 4:
      if(a[i]=='X')
      {state=5;break;}
      else if(a[i]=='0'||a[i]=='1'||a[i]=='2'||a[i]=='3'||a[i]=='4'||a[i]=='5'||a[i]=='6'||a[i]=='7'||a[i]=='8'||a[i]=='9')
     {
     state=4;break;}
     else{state=6;break;}
case 5:
printf("it is real number");return 0;
case 6:
printf("not accepted");return 0;
default:
printf("invalid input");return 0;
}i++;
}
}
