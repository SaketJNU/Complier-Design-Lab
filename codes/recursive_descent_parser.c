/* Write a C program to implement Recursive Descent Parser for any given grammar */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

char lookahead;

// Function to get the next character from the input
void advance() {
    lookahead = getchar();
}

// Function to match the expected terminal
void match(char t) {
    if (lookahead == t) {
        advance();
    } else {
        printf("Syntax Error: Unexpected character '%c'\n", lookahead);
        exit(1);
    }
}

// Forward declarations for non-terminal functions
void E();
void E_prime();
void T();
void T_prime();
void F();

// The start symbol: E -> T E'
void E() {
    T();
    E_prime();
}

// E' -> + T E' | ε
void E_prime() {
    if (lookahead == '+') {
        match('+');
        T();
        E_prime();
    } // epsilon production: do nothing if lookahead is not '+'
}

// T -> F T'
void T() {
    F();
    T_prime();
}

// T' -> * F T' | ε
void T_prime() {
    if (lookahead == '*') {
        match('*');
        F();
        T_prime();
    } // epsilon production: do nothing if lookahead is not '*'
}

// F -> ( E ) | id
void F() {
    if (lookahead == '(') {
        match('(');
        E();
        match(')');
    } else if (isalnum(lookahead)) {
        match(lookahead);  // Assume it's an identifier (e.g., a variable or number)
    } else {
        printf("Syntax Error: Unexpected character '%c' in F\n", lookahead);
        exit(1);
    }
}

// Main function to start parsing
int main() {
    printf("Enter an arithmetic expression: ");
    advance();  // Initialize lookahead by getting the first character

    E();  // Start the parsing from the start symbol (E)

    if (lookahead == '\n' || lookahead == EOF) {
        printf("Parsing successful.\n");
    } else {
        printf("Syntax Error: Unexpected characters after end of expression.\n");
    }

    return 0;
}

/* Input and Output */
// 3 + 5 * (2 + 8)
// Parsing successful.