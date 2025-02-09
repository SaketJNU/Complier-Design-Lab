/* Write a C program which reads a grammar and find First and FOLLOW symbols of all non-terminals. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

// Global variables to hold the grammar, First and Follow sets
char nonTerminals[MAX], terminals[MAX], rules[MAX][MAX];
char first[MAX][MAX], follow[MAX][MAX];
int numNonTerminals, numTerminals, numRules;

// Function to check if a symbol is a terminal
int isTerminal(char symbol) {
    return !isupper(symbol);  // Terminals are non-uppercase
}

// Function to add a symbol to a set if it's not already present
void addToSet(char *set, char symbol) {
    if (!strchr(set, symbol)) {
        strncat(set, &symbol, 1);
    }
}

// Function to find First of a non-terminal
void findFirst(int index) {
    int i, j, k;
    char current = nonTerminals[index];
    
    // If the First set for this non-terminal is already computed, return
    if (first[index][0] != '\0') {
        return;
    }

    for (i = 0; i < numRules; i++) {
        if (rules[i][0] == current) {
            // Rule of the form: A -> X1 X2 ... Xn
            for (j = 2; j < strlen(rules[i]); j++) {
                char nextSymbol = rules[i][j];
                if (isTerminal(nextSymbol)) {
                    // If terminal, add to First(A)
                    addToSet(first[index], nextSymbol);
                    break;
                } else {
                    // If non-terminal, recursively find First of that non-terminal
                    int nextIndex = strchr(nonTerminals, nextSymbol) - nonTerminals;
                    findFirst(nextIndex);
                    for (k = 0; k < strlen(first[nextIndex]); k++) {
                        char firstSymbol = first[nextIndex][k];
                        if (firstSymbol != 'e') {
                            addToSet(first[index], firstSymbol);
                        }
                    }
                    // If epsilon ('e') is in First of next non-terminal, continue checking the next symbols
                    if (strchr(first[nextIndex], 'e') == NULL) {
                        break;
                    }
                }
            }
            // If the production is of the form: A -> ε, add 'e' to First(A)
            if (rules[i][2] == 'e') {
                addToSet(first[index], 'e');
            }
        }
    }
}

// Function to find Follow of a non-terminal
void findFollow(int index) {
    int i, j, k;
    char current = nonTerminals[index];
    
    // If the Follow set for this non-terminal is already computed, return
    if (follow[index][0] != '\0') {
        return;
    }

    // Add '$' to Follow(S) (start symbol)
    if (current == nonTerminals[0]) {
        addToSet(follow[index], '$');
    }

    // Traverse all rules and check when the current non-terminal appears
    for (i = 0; i < numRules; i++) {
        for (j = 2; j < strlen(rules[i]); j++) {
            if (rules[i][j] == current) {
                // Case 1: If there's a terminal or a non-terminal after the current symbol
                if (j + 1 < strlen(rules[i])) {
                    char nextSymbol = rules[i][j + 1];
                    if (isTerminal(nextSymbol)) {
                        // If terminal, add it to Follow of the current non-terminal
                        addToSet(follow[index], nextSymbol);
                    } else {
                        // If non-terminal, recursively find First of the next symbol
                        int nextIndex = strchr(nonTerminals, nextSymbol) - nonTerminals;
                        findFirst(nextIndex);
                        for (k = 0; k < strlen(first[nextIndex]); k++) {
                            char firstSymbol = first[nextIndex][k];
                            if (firstSymbol != 'e') {
                                addToSet(follow[index], firstSymbol);
                            }
                        }
                        // If First of the next non-terminal contains epsilon, also add Follow of the next non-terminal
                        if (strchr(first[nextIndex], 'e')) {
                            int nextFollowIndex = strchr(nonTerminals, nextSymbol) - nonTerminals;
                            findFollow(nextFollowIndex);
                            for (k = 0; k < strlen(follow[nextFollowIndex]); k++) {
                                addToSet(follow[index], follow[nextFollowIndex][k]);
                            }
                        }
                    }
                } else {
                    // Case 2: If there's no symbol after the current non-terminal, add Follow of the left-hand side to Follow of the current non-terminal
                    int leftIndex = strchr(nonTerminals, rules[i][0]) - nonTerminals;
                    findFollow(leftIndex);
                    for (k = 0; k < strlen(follow[leftIndex]); k++) {
                        addToSet(follow[index], follow[leftIndex][k]);
                    }
                }
            }
        }
    }
}

int main() {
    int i, j;

    // Input the number of non-terminals and terminals
    printf("Enter the number of non-terminals: ");
    scanf("%d", &numNonTerminals);

    printf("Enter the non-terminals (one per line):\n");
    for (i = 0; i < numNonTerminals; i++) {
        scanf(" %c", &nonTerminals[i]);
    }

    printf("Enter the number of terminals: ");
    scanf("%d", &numTerminals);

    printf("Enter the terminals (one per line):\n");
    for (i = 0; i < numTerminals; i++) {
        scanf(" %c", &terminals[i]);
    }

    // Input the number of rules
    printf("Enter the number of rules: ");
    scanf("%d", &numRules);

    printf("Enter the production rules (e.g., S->AB):\n");
    for (i = 0; i < numRules; i++) {
        scanf(" %[^\n]", rules[i]);
    }

    // Initialize First and Follow sets
    for (i = 0; i < numNonTerminals; i++) {
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    // Calculate First sets
    for (i = 0; i < numNonTerminals; i++) {
        findFirst(i);
    }

    // Calculate Follow sets
    for (i = 0; i < numNonTerminals; i++) {
        findFollow(i);
    }

    // Display First and Follow sets
    printf("\nFirst sets:\n");
    for (i = 0; i < numNonTerminals; i++) {
        printf("First(%c) = {", nonTerminals[i]);
        for (j = 0; j < strlen(first[i]); j++) {
            printf("%c", first[i][j]);
            if (j != strlen(first[i]) - 1)
                printf(", ");
        }
        printf("}\n");
    }

    printf("\nFollow sets:\n");
    for (i = 0; i < numNonTerminals; i++) {
        printf("Follow(%c) = {", nonTerminals[i]);
        for (j = 0; j < strlen(follow[i]); j++) {
            printf("%c", follow[i][j]);
            if (j != strlen(follow[i]) - 1)
                printf(", ");
        }
        printf("}\n");
    }

    return 0;
}

/* Input and Output */
// saket@DESKTOP-2MBMJIQ:~$ ./a.out
// Enter the number of non-terminals: 3
// Enter the non-terminals (one per line):
// S
// A
// B
// Enter the number of terminals: 3
// Enter the terminals (one per line):
// a
// b
// c
// Enter the number of rules: 4
// Enter the production rules (e.g., S->AB):
// S=AB
// A=aA
// A=a
// B=b
// 
// First sets:
// First(S) = {a}
// First(A) = {a}
// First(B) = {b}
//  
// Follow sets:
// Follow(S) = {$}
// Follow(A) = {b}
// Follow(B) = {$}