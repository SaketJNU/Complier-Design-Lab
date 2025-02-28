/* Program for shift-reduce parser */

#include<stdio.h>

#include<string.h>

int z = 0, k = 0, i = 0, j = 0, length = 0;

char a[16], ac[20], stk[15], act[10];

void check();

void main() {

        printf("\tGrammer : \n \tS -> S + S \n \tS -> S * S \n \tS -> id\n");
        printf("\nInput : ");
        scanf("%s", a);
        printf("\n");

        length = strlen(a);
        strcpy(act, "SHIFT");
        printf("Stack\t Input \t Action");

        for (i = 0; j < length; i++, j++) {
                if (a[j] == 'i' && a[j + 1] == 'd') {
                        stk[i] = a[j];
                        stk[i + 1] = a[j + 1];
                        stk[i + 2] = '\0';
                        a[j] = ' ';
                        a[j + 1] = ' ';
                        printf("\n$%s\t%s$\t%s", stk, a, act);
                        check();
                } else {
                        stk[i] = a[j];
                        stk[i + 1] = '\0';
                        a[j] = ' ';
                        printf("\n$%s\t%s$\t%s", stk, a, act);
                        check();
                }
        }

        if (stk[0] == 'S' && stk[1] == '\0')
                printf("\n\nString Accepted\n");
        else
                printf("\n\nString Rejected\n");
}

void check() {

        for (z = 0; stk[z] != '\0'; z++) {
                if (stk[z] == 'i' && stk[z + 1] == 'd') {
                        strcpy(ac, "REDUCE (S->id)");
                        stk[z] = 'S';
                        stk[z + 1] = '\0';
                        printf("\n$%s\t%s$\t%s", stk, a, ac);
                        j++;

                }
        }

        for (z = 0; z < strlen(stk); z++) {
                if (stk[z] == 'S' && stk[z + 1] == '+' && stk[z + 2] == 'S') {
                        strcpy(ac, "REDUCE (S->S+S)");

                        stk[z] = 'S';
                        stk[z + 1] = '\0';

                        printf("\n$%s\t%s$\t%s", stk, a, ac);
                        i = i - 2;

                }
        }

        for (z = 0; z < strlen(stk); z++) {
                if (stk[z] == 'S' && stk[z + 1] == '*' && stk[z + 2] == 'S') {
                        strcpy(ac, "REDUCE (S->S*S)");
                        stk[z] = 'S';
                        stk[z + 1] = '\0';
                        printf("\n$%s\t%s$\t%s", stk, a, ac);
                        i = i - 2;

                }
        }

}
