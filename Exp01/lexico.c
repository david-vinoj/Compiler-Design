#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

// Function to check if a character is a valid operator
int isOperator(char ch) {
    char operators[] = "+-*/=<>^";
    for (int i = 0; i < strlen(operators); i++) {
        if (ch == operators[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a character is a valid punctuation
int isPunctuation(char ch) {
    char punctuations[] = ",;:(){}[]?!|&`~'";
    for (int i = 0; i < strlen(punctuations); i++) {
        if (ch == punctuations[i]) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a string is a valid keyword
int isKeyword(char* str) {
    char keywords[32][10] = {"auto", "break", "case", "char", "const", "continue", "default","do", "double", "else", "enum", "extern", "float", "for","goto", "if", "int", "long", "register", "return", "short",
                             "signed", "sizeof", "static", "struct", "switch", "typedef","union", "unsigned", "void", "volatile", "while"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a string is a valid identifier
int isIdentifier(char* str) {
    if (!isalpha(str[0])) {
        return 0;
    }
    for (int i = 1; i < strlen(str); i++) {
        if (!isalnum(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to check if a string is a valid number
int isNumber(char* str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

// Function to print the token table
void printTokenTable(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_TOKEN_LENGTH];
    int lineNo = 1;

    printf("Token\t\tType\t\tLine No.\n");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, " \t\n");
        while (token != NULL) {
            if (isKeyword(token)) {
                printf("%s\t\tKeyword\t\t%d\n", token, lineNo);
            } else if (isPunctuation(token[0])) {
                printf("%s\t\tPunctuation\t%d\n", token, lineNo);
            } else if (isOperator(token[0])) {
                printf("%s\t\tOperator\t%d\n", token, lineNo);
            } else if (isIdentifier(token)) {
                printf("%s\t\tIdentifier\t%d\n", token, lineNo);
            } else if (isNumber(token)) {
                printf("%s\t\tNumber\t\t%d\n", token, lineNo);
            } else {
                printf("%s\t\tInvalid\t\t%d\n", token, lineNo);
            }
            token = strtok(NULL, " \t\n");
        }
        lineNo++;
    }

    fclose(file);
}

int main() {
    char filename[] = "input.txt";
    printTokenTable(filename);
    return 0;
}
