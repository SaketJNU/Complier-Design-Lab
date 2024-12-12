#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TOKEN_LEN 100

// Function to classify the identifier
void classify_identifier(char *identifier) {
    // Check for array (identifier followed by '[' and ']')
    if (strchr(identifier, '[') && strchr(identifier, ']')) {
        printf("Array: %s\n", identifier);
    }
    // Check for function (identifier followed by '(' and ')')
    else if (strchr(identifier, '(') && strchr(identifier, ')')) {
        printf("Function: %s\n", identifier);
    }
    // Check for structure (identifier followed by '.')
    else if (strchr(identifier, '.')) {
        printf("Structure: %s\n", identifier);
    }
    // Default: it's a variable
    else {
        printf("Variable: %s\n", identifier);
    }
}

// Function to classify the constant
void classify_constant(char *constant) {
    int has_dot = 0;
    
    // Check if the constant contains a dot (for real constant)
    for (int i = 0; constant[i] != '\0'; i++) {
        if (constant[i] == '.') {
            has_dot = 1;
            break;
        }
    }
    
    // If it has a dot, it's a real constant; otherwise, it's an integer constant
    if (has_dot) {
        printf("Real Constant: %s\n", constant);
    } else {
        printf("Integer Constant: %s\n", constant);
    }
}

// Function to extract tokens and classify them
void process_input(char *input) {
    int i = 0;
    char token[MAX_TOKEN_LEN];
    int token_index = 0;
    
    while (input[i] != '\0') {
        // Skip whitespace characters
        if (isspace(input[i])) {
            i++;
            continue;
        }

        // If it's a letter or underscore, it's an identifier
        if (isalpha(input[i]) || input[i] == '_') {
            // Collect the identifier
            token_index = 0;
            while (isalnum(input[i]) || input[i] == '_' || input[i] == '[' || input[i] == ']' || input[i] == '(' || input[i] == ')') {
                token[token_index++] = input[i++];
            }
            token[token_index] = '\0';
            classify_identifier(token); // Classify the identifier
        }
        // If it's a digit, it's a constant (integer or real)
        else if (isdigit(input[i])) {
            // Collect the constant
            token_index = 0;
            while (isdigit(input[i]) || input[i] == '.') {
                token[token_index++] = input[i++];
            }
            token[token_index] = '\0';
            classify_constant(token); // Classify the constant
        }
        // Skip unrecognized characters
        else {
            i++;
        }
    }
}

int main() {
    char input[MAX_TOKEN_LEN];
    
    printf("Enter the input string: ");
    fgets(input, sizeof(input), stdin); // Get input string
    
    process_input(input); // Process the input string and classify tokens
    
    return 0;
}
