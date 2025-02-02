#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 50
#define MAX_RULES 50
#define NON_TERMINALS 26 // A-Z

// Structure to store the production rules
struct Production {
    char left;         // Left-hand side (non-terminal)
    char right[MAX];   // Right-hand side (production)
};

// Global arrays to store the grammar and FIRST sets
struct Production productions[MAX_RULES];
char first[NON_TERMINALS][MAX];    // FIRST sets (for A-Z)
bool visited[NON_TERMINALS];       // To avoid recomputation of FIRST sets

// Function to check if a character is a terminal
bool isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

// Function to add a symbol to the FIRST set of a non-terminal
void addToFirstSet(int index, char symbol) {
    // Avoid adding duplicates in the FIRST set
    for (int i = 0; first[index][i] != '\0'; i++) {
        if (first[index][i] == symbol) {
            return;
        }
    }
    // Add the symbol to the FIRST set
    int i = 0;
    while (first[index][i] != '\0') {
        i++;
    }
    first[index][i] = symbol;
    first[index][i + 1] = '\0';
}

// Function to calculate FIRST set for a non-terminal
void findFirst(int nonTerminalIndex, int n) {
    if (visited[nonTerminalIndex]) {
        return; // Avoid redundant calculations
    }
    visited[nonTerminalIndex] = true;

    // Iterate over all production rules
    for (int i = 0; i < n; i++) {
        if (productions[i].left == 'A' + nonTerminalIndex) {
            // For each production of the non-terminal
            char* rhs = productions[i].right;

            // Iterate over symbols on the right-hand side
            for (int j = 0; rhs[j] != '\0'; j++) {
                char symbol = rhs[j];

                // If the symbol is a terminal, add it to the FIRST set
                if (isTerminal(symbol)) {
                    addToFirstSet(nonTerminalIndex, symbol);
                    break; // Stop after the first terminal
                }

                // If it's a non-terminal, recursively calculate its FIRST set
                findFirst(symbol - 'A', n);

                // Add all the FIRST set of the non-terminal to the current FIRST set
                for (int k = 0; first[symbol - 'A'][k] != '\0'; k++) {
                    addToFirstSet(nonTerminalIndex, first[symbol - 'A'][k]);
                }

                // If the non-terminal produces epsilon (empty string), continue
                // We only need to continue to the next symbol if we can get epsilon
                if (strchr(first[symbol - 'A'], '\0') != NULL) {
                    continue;
                } else {
                    break; // No epsilon, stop after processing the first symbol
                }
            }
        }
    }
}

// Function to print the FIRST sets
void printFirstSets(int n) {
    // Print FIRST sets for non-terminals (based on their actual characters)
    for (int i = 0; i < n; i++) {
        printf("FIRST(%c) = { ", productions[i].left);
        for (int j = 0; first[productions[i].left - 'A'][j] != '\0'; j++) {
            printf("%c ", first[productions[i].left - 'A'][j]);
        }
        printf("}\n");
    }
}

int main() {
    int n;

    // Input the number of production rules
    printf("Enter the number of production rules: ");
    scanf("%d", &n);
    getchar(); // To consume the newline character after the integer input

    // Read each production rule
    for (int i = 0; i < n; i++) {
        printf("Enter production %d (e.g., A->AB or A->a): ", i + 1);
        char rule[MAX];
        fgets(rule, sizeof(rule), stdin);
        rule[strcspn(rule, "\n")] = '\0'; // Remove the newline character

        productions[i].left = rule[0];  // Left side (non-terminal)
        strcpy(productions[i].right, rule + 3); // Right side (production)
    }

    // Initialize FIRST sets to empty
    memset(first, '\0', sizeof(first));
    memset(visited, 0, sizeof(visited));

    // Calculate FIRST sets for all non-terminals
    for (int i = 0; i < n; i++) {
        findFirst(productions[i].left - 'A', n);
    }

    // Print the FIRST sets
    printFirstSets(n);

    return 0;
}

/* Input and Output */
// Enter the number of production rules: 4
// Enter production 1 (e.g., A->AB or A->a): E->TR
// Enter production 2 (e.g., A->AB or A->a): T->F*
// Enter production 3 (e.g., A->AB or A->a): F->(E)
// Enter production 4 (e.g., A->AB or A->a): F->a
// FIRST(E) = { ( a * }
// FIRST(T) = { ( a * }
// FIRST(F) = { ( a }
// FIRST(F) = { ( a }
