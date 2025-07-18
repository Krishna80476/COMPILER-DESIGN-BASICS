#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Define token categories
const char *keywords[] = {"if", "else", "while", "int", "float", "return", "void"};
const int num_keywords = 7;
const char operators[] = {"+", "-", "", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!"};
const int num_operators = 14;
const char *separators = ";,.(){}";

// Check if token is a keyword
bool is_keyword(const char *token) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(token, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Check if token is an operator
bool is_operator(const char *token) {
    for (int i = 0; i < num_operators; i++) {
        if (strcmp(token, operators[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Check if character is a separator
bool is_separator(char ch) {
    return strchr(separators, ch) != NULL;
}

// Check if token is a valid identifier
bool is_identifier(const char *token) {
    if (!isalpha(token[0]) && token[0] != '_') {
        return false;
    }
    for (int i = 1; token[i];
