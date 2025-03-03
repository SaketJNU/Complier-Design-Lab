/* Program to compute First and Follow of a given Grammer */
#include <ctype.h>

#include <stdio.h>

char a[8][8];
int cnt;
struct firTab {
        int n;
        char firT[5];
};
struct folTab {
        int n;
        char folT[5];
};
struct folTab follow[5];
struct firTab first[5];
int col;
int num;
void findFirst(char, int);
void findFollow(char, int);
void folTabOperation(char, int);
void firTabOperation(char, int);
void main() {
        int i, j, c = 0;
        char ip;
        char b[8];
        printf("Number of productions:");
        scanf("%d", & num);
        for (i = 0; i < num; i++) {
                scanf("%s", a[i]);
        }
        for (i = 0; i < num; i++) {
                c = 0;
                for (j = 0; j < i + 1; j++) {
                        if (a[i][0] == b[j]) {
                                c = 1;
                                break;
                        }
                }
                if (c != 1) {
                        b[cnt] = a[i][0];
                        cnt++;
                }
        }

        printf("\n");
        for (i = 0; i < cnt; i++) {
                col = 1;
                first[i].firT[0] = b[i];
                first[i].n = 0;
                findFirst(b[i], i);
        }
        for (i = 0; i < cnt; i++) {
                col = 1;
                follow[i].folT[0] = b[i];
                follow[i].n = 0;
                findFollow(b[i], i);
        }
        printf("\n");
        for (i = 0; i < cnt; i++) {
                for (j = 0; j <= first[i].n; j++) {
                        if (j == 0) {
                                printf("First(%c) : {", first[i].firT[j]);
                        } else if (j > 0 && j < first[i].n) {
                                printf(" %c,", first[i].firT[j]);
                        } else {
                                printf(" %c", first[i].firT[j]);
                        }
                }
                printf(" } ");
                printf("\n");
        }
        printf("\n");
        for (i = 0; i < cnt; i++) {
                for (j = 0; j <= follow[i].n; j++) {
                        if (j == 0) {
                                printf("Follow(%c) : {", follow[i].folT[j]);
                        } else if (j > 0 && j < follow[i].n) {
                                printf(" %c,", follow[i].folT[j]);
                        } else {
                                printf(" %c", follow[i].folT[j]);
                        }
                }
                printf(" } ");
                printf("\n");
        }
}
void findFirst(char ip, int pos) {
        int i;
        for (i = 0; i < num; i++) {
                if (ip == a[i][0]) {
                        if (isupper(a[i][3])) {
                                findFirst(a[i][3], pos);

                        } else {
                                first[pos].firT[col] = a[i][3];
                                first[pos].n++;
                                col++;
                        }
                }
        }
}
void findFollow(char ip, int row) {
        int i, j;
        if (row == 0 && col == 1) {
                follow[row].folT[col] = '$';
                col++;
                follow[row].n++;
        }
        for (i = 0; i < num; i++) {
                for (j = 3; j < 7; j++) {
                        if (a[i][j] == ip) {
                                if (a[i][j + 1] == '\0') {
                                        if (a[i][j] != a[i][0]) {
                                                folTabOperation(a[i][0], row);
                                        }
                                } else if (isupper(a[i][j + 1])) {
                                        if (a[i][j + 1] != a[i][0]) {
                                                firTabOperation(a[i][j + 1], row);
                                        }
                                } else {
                                        follow[row].folT[col] = a[i][j + 1];
                                        col++;
                                        follow[row].n++;
                                }
                        }
                }
        }
}
void folTabOperation(char ip, int row) {
        int i, j;
        for (i = 0; i < cnt; i++) {
                if (ip == follow[i].folT[0]) {
                        for (j = 1; j <= follow[i].n; j++) {
                                follow[row].folT[col] = follow[i].folT[j];
                                col++;
                                follow[row].n++;
                        }
                }
        }
}
void firTabOperation(char ip, int row) {

        int i, j;
        for (i = 0; i < cnt; i++) {
                if (ip == first[i].firT[0]) {
                        for (j = 1; j <= first[i].n; j++) {
                                if (first[i].firT[j] != '0') {
                                        follow[row].folT[col] = first[i].firT[j];
                                        follow[row].n++;
                                        col++;
                                } else {
                                        folTabOperation(ip, row);
                                }
                        }
                }
        }
}
