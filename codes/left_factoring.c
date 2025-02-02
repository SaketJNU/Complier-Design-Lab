/* Write a C program for applying left factoring to a given grammar. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 10
#define MAX_LEN 50

// Structure to store a production
typedef struct {
    char lhs;             // Left-hand side (non-terminal)
    char rhs[MAX_RULES][MAX_LEN];  // Right-hand side (multiple alternatives)
    int ruleCount;        // Number of rules for this non-terminal
} Grammar;

// Function to check if two strings start with the same prefix
int isPrefix(char *s1, char *s2) {
    int i = 0;
    while (s1[i] && s2[i] && s1[i] == s2[i]) {
        i++;
    }
    return i > 0;  // If there's any common prefix, return true
}

// Function to perform left factoring on the given grammar
void leftFactor(Grammar *grammar, int numNonTerminals) {
    for (int i = 0; i < numNonTerminals; i++) {
        Grammar *g = &grammar[i];
        
        for (int j = 0; j < g->ruleCount; j++) {
            for (int k = j + 1; k < g->ruleCount; k++) {
                // Check if two rules share a common prefix
                if (isPrefix(g->rhs[j], g->rhs[k])) {
                    // Find the longest common prefix
                    int prefixLength = 0;
                    while (g->rhs[j][prefixLength] == g->rhs[k][prefixLength] && g->rhs[j][prefixLength] != '\0') {
                        prefixLength++;
                    }
                    
                    // Create a new non-terminal (X)
                    char newNonTerminal = g->lhs + 1;  // Assume new non-terminal is just next character
                    
                    // Factor out the common prefix and create new rules
                    printf("Left factoring rule for %c:\n", g->lhs);
                    printf("  %c → %sX\n", g->lhs, g->rhs[j]);
                    printf("  X → %s | %s\n", g->rhs[j] + prefixLength, g->rhs[k] + prefixLength);
                    
                    // Modify the grammar to reflect the changes
                    g->rhs[j][prefixLength] = '\0'; // Shorten the prefix of the original rules
                    break;  // Once we have factored out one pair of rules, we move to the next rule
                }
            }
        }
    }
}

int main() {
    Grammar grammar[MAX_RULES];
    int numNonTerminals;
    
    // Input number of non-terminals
    printf("Enter the number of non-terminals: ");
    scanf("%d", &numNonTerminals);
    
    // Input the grammar
    for (int i = 0; i < numNonTerminals; i++) {
        printf("Enter the non-terminal for rule %d: ", i + 1);
        getchar();  // Consume newline
        scanf("%c", &grammar[i].lhs);
        printf("Enter the number of rules for %c: ", grammar[i].lhs);
        scanf("%d", &grammar[i].ruleCount);
        
        for (int j = 0; j < grammar[i].ruleCount; j++) {
            printf("Enter rule %d for %c: ", j + 1, grammar[i].lhs);
            scanf("%s", grammar[i].rhs[j]);
        }
    }

    // Apply left factoring
    leftFactor(grammar, numNonTerminals);

    return 0;
}

/* Input */
Enter the number of non-terminals: 1
Enter the non-terminal for rule 1: 5
Enter the number of rules for 5: 2
Enter rule 1 for 5: abX
Enter rule 2 for 5: abY
Left factoring rule for 5:

/* Output */
  5 → abXX
  X → X | Y