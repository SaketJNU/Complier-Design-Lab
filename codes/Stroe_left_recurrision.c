/* Write a C program which reads a production and check for Left-Recursion (may contain in more than one alternatives) and if found eliminate it and store in another production and display the result. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 50

// Function to check if a production is left-recursive
int is_left_recursive(char *production) {
    return production[0] == production[0]; // Left recursive if the first symbol is the same non-terminal
}

// Function to eliminate left recursion from a set of productions
void eliminate_left_recursion(char non_terminal, char productions[MAX_PRODUCTIONS][MAX_LENGTH], int num_productions) {
    char new_non_terminal = non_terminal + 1;  // To create a new non-terminal like A' from A
    char new_productions[MAX_PRODUCTIONS][MAX_LENGTH];
    int i, j, k;

    printf("Original productions for %c:\n", non_terminal);
    for (i = 0; i < num_productions; i++) {
        printf("%s\n", productions[i]);
    }

    // Step 1: Identify the productions that are left-recursive
    int has_left_recursion = 0;
    for (i = 0; i < num_productions; i++) {
        if (productions[i][0] == non_terminal) {
            has_left_recursion = 1;
            break;
        }
    }

    if (has_left_recursion) {
        printf("\nEliminating left recursion for %c...\n", non_terminal);

        // Step 2: Separate left-recursive and non-left-recursive productions
        char left_recursive[MAX_PRODUCTIONS][MAX_LENGTH];
        char non_left_recursive[MAX_PRODUCTIONS][MAX_LENGTH];
        int left_rec_count = 0, non_left_rec_count = 0;

        for (i = 0; i < num_productions; i++) {
            if (productions[i][0] == non_terminal) {
                strcpy(left_recursive[left_rec_count++], &productions[i][1]);  // Skip the non-terminal
            } else {
                strcpy(non_left_recursive[non_left_rec_count++], productions[i]);
            }
        }

        // Step 3: Create the new production rules
        // A -> βA'
        for (i = 0; i < non_left_rec_count; i++) {
            printf("%c -> %s%c\n", non_terminal, non_left_recursive[i], new_non_terminal);
        }

        // A' -> αA' | ε
        printf("%c' -> ", new_non_terminal);
        for (i = 0; i < left_rec_count; i++) {
            for (j = 0; j < strlen(left_recursive[i]); j++) {
                if (left_recursive[i][j] != non_terminal) {
                    printf("%c", left_recursive[i][j]);
                }
            }
            if (i != left_rec_count - 1) {
                printf(" | ");
            }
        }
        printf(" | ε\n");
    } else {
        printf("No left recursion found for %c.\n", non_terminal);
    }
}

int main() {
    char non_terminal;
    char productions[MAX_PRODUCTIONS][MAX_LENGTH];
    int num_productions;

    // Input the non-terminal and productions
    printf("Enter the non-terminal for the grammar (e.g., A): ");
    scanf("%c", &non_terminal);
    getchar(); // To clear the newline left by scanf

    printf("Enter the number of productions for %c: ", non_terminal);
    scanf("%d", &num_productions);
    getchar(); // To clear the newline left by scanf

    printf("Enter the productions for %c (e.g., A->Aalpha|beta):\n", non_terminal);
    for (int i = 0; i < num_productions; i++) {
        fgets(productions[i], MAX_LENGTH, stdin);
        productions[i][strcspn(productions[i], "\n")] = '\0';  // Remove trailing newline
    }

    // Eliminate left recursion
    eliminate_left_recursion(non_terminal, productions, num_productions);

    return 0;
}

/* Input and Output*/
// Enter the non-terminal for the grammar (e.g., A): A
// Enter the number of productions for A: 2
// Enter the productions for A (e.g., A->Aalpha|beta):
// A->Aa|b
// 
// Original productions for A:
// A->Aa|b
// 
// Eliminating left recursion for A...
// A -> B
// B' -> ->a|b | ε