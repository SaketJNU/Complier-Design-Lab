/* Write a C program which takes a grammar and check for Left-Recursion (may contain left recursion in more than one production) and if found eliminate it display the resultant grammar.  */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 50

// Function to remove left recursion from a given non-terminal
void removeLeftRecursion(char nonTerminal, char productions[MAX_PRODUCTIONS][MAX_LENGTH], int numProductions) {
    char newNonTerminal = nonTerminal + 1;  // We create a new non-terminal
    printf("\nEliminating left recursion for '%c':\n", nonTerminal);

    // Step 1: Separate productions into left-recursive and non-left-recursive
    char alpha[MAX_PRODUCTIONS][MAX_LENGTH];  // To store recursive parts
    char beta[MAX_PRODUCTIONS][MAX_LENGTH];   // To store non-recursive parts
    int recCount = 0, nonRecCount = 0;

    for (int i = 0; i < numProductions; i++) {
        int len = strlen(productions[i]);
        if (productions[i][0] == nonTerminal) {  // Left recursion exists
            // Remove the first character (which is the non-terminal itself)
            strncpy(alpha[recCount], productions[i] + 1, len - 1);
            alpha[recCount][len - 1] = '\0';  // Null-terminate the string
            recCount++;
        } else {  // Non-left recursion
            strcpy(beta[nonRecCount], productions[i]);
            nonRecCount++;
        }
    }

    // Step 2: Print the non-recursive productions
    printf("%c -> ", nonTerminal);
    for (int i = 0; i < nonRecCount; i++) {
        if (i > 0) printf(" | ");
        printf("%s%c", beta[i], newNonTerminal);
    }
    printf("\n");

    // Step 3: Print the new non-terminal productions
    printf("%c -> ", newNonTerminal);
    for (int i = 0; i < recCount; i++) {
        printf("%s%c", alpha[i], newNonTerminal);
        if (i < recCount - 1) printf(" | ");
    }
    printf(" | ε\n");
}

// Function to handle the input and output of the grammar
void processGrammar(char grammar[MAX_PRODUCTIONS][MAX_LENGTH], int numProductions) {
    // For each non-terminal, check and remove left recursion
    for (int i = 0; i < numProductions; i++) {
        char nonTerminal = grammar[i][0]; // Non-terminal is the first character in the production
        removeLeftRecursion(nonTerminal, grammar, numProductions);
    }
}

int main() {
    char grammar[MAX_PRODUCTIONS][MAX_LENGTH];
    int numProductions;

    // Input the number of productions
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);
    
    // Input the productions
    printf("Enter the productions (one per line):\n");
    for (int i = 0; i < numProductions; i++) {
        getchar();  // to consume newline character from previous input
        fgets(grammar[i], MAX_LENGTH, stdin);
        grammar[i][strcspn(grammar[i], "\n")] = '\0';  // Remove the newline character
    }

    // Process and eliminate left recursion
    processGrammar(grammar, numProductions);
    
    return 0;
}

/*  Input and Output */
// Enter the number of productions: 2
// Enter the productions (one per line):
// A->Aa|b
// B->c|Bd
// 
// Eliminating left recursion for 'A':
// A -> ->c|BdB
// B -> ->Aa|bB | ε
// 
// Eliminating left recursion for '-':
// - -> A->Aa|b.
// . -> >c|Bd. | ε