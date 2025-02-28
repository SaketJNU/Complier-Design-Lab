/* Program for recursive-descent parser */

#include <stdio.h>

#include <stdlib.h>

char * c;
char str[20];

int E();

int T();

int Edash();

int Tdash();

int F();

void main() {
        printf("Input  : ");
        scanf("%s", str);

        printf("\nInput\t\tAction\n");
        c = str;
        printf("--------------------------------\n");

        if (E() && * c == '\0') {
                printf("\n-------------------------\n");
                printf("\nString accepted\n");
        } else {
                printf("\n------------------------\n");
                printf("\nString Not accepted\n");
        }
}

int E() {
        printf("%-16s E -> T E' \n", c);
        if (T()) {
                if (Edash()) {
                        return 1;
                } else {
                        return 0;
                }
        }
        return 0;
}

int Edash() {

        if ( * c == '+') {
                printf("%-16s E' -> + T E\n", c);
                c++;
                if (T()) {
                        if (Edash()) {
                                return 1;
                        } else {
                                return 0;
                        }
                } else {
                        return 0;
                }
        } else {
                printf("%-16s E' -> NULL\n", c);
                return 1;
        }
}

int T() {
        printf("%-16s T -> F T'\n", c);
        if (F()) {
                if (Tdash()) {
                        return 1;
                } else {
                        return 0;
                }
        } else {
                return 0;
        }
}

int Tdash() {
        if ( * c == '*') {
                printf("%-16s T' -> * F T'\n", c);
                c++;
                if (F()) {
                        if (Tdash()) {
                                return 1;
                        } else {
                                return 0;
                        }
                } else {
                        return 0;
                }
        } else {
                printf("%-16s T' -> NULL\n", c);
                return 1;
        }
}

int F() {
        if ( * c == '(') {
                printf("%-16s F -> ( E )\n", c);
                c++;
                if (E()) {
                        if ( * c == ')') {
                                c++;
                                return 1;
                        } else {
                                return 0;
                        }
                } else {
                        return 0;
                }
        } else if ( * c == 'i') {
                c++;
                printf("%-16s F -> i\n", c);
                return 1;
        } else {
                return 0;
        }
}
