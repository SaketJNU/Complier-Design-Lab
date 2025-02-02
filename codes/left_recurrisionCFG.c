#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
#define MAX_LEN 100

// Function to remove left recursion
void removeLeftRecursion(char grammar[MAX][MAX_LEN], int n) {
    char newGrammar[MAX][MAX_LEN];
    char nonTerminal;
    char production[MAX_LEN];
    int i, j, k, ruleCount;

    printf("After Removing Left Recursion:\n");

    // Iterate through each production
    for (i = 0; i < n; i++) {
        nonTerminal = grammar[i][0]; // Get the non-terminal of the rule
        int isLeftRecursive = 0;
        int newProductionIndex = 0;

        // Check if the first character of the production is the same as the non-terminal
        if (grammar[i][3] == nonTerminal) {
            isLeftRecursive = 1;
        }

        if (isLeftRecursive) {
            // Remove left recursion
            printf("Left recursion detected in production: %s\n", grammar[i]);

            // Creating the new production
            // A -> β A'
            printf("Rewriting production for %c:\n", nonTerminal);
            
            // Rule A -> β A'
            printf("%c -> ", nonTerminal);
            for (j = 3; grammar[i][j] != '\0' && grammar[i][j] != '|' && grammar[i][j] != ' '; j++) {
                production[newProductionIndex++] = grammar[i][j];
            }
            production[newProductionIndex] = '\0'; // Null-terminate the string
            printf("%sA'\n", production);

            // Now A' -> α A' | ε
            printf("%c' -> ", nonTerminal);
            printf("%s %c' | ε\n", grammar[i] + 3, nonTerminal);  // Assuming the right-hand side after left recursion.

        } else {
            // No left recursion, print the rule as is
            printf("%s\n", grammar[i]);
        }
    }
}

int main() {
    char grammar[MAX][MAX_LEN];
    int n;

    printf("Enter the number of grammar rules: ");
    scanf("%d", &n);

    printf("Enter the grammar rules (one per line):\n");

    // Reading the grammar rules
    for (int i = 0; i < n; i++) {
        scanf("%s", grammar[i]);
    }

    // Removing left recursion
    removeLeftRecursion(grammar, n);

    return 0;
}
