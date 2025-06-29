
#include <ctype.h>

const char *keywords[] = {
    "auto","break","case","char","const","continue","default",
    "do","double","else","enum","extern","float","for","goto",
    "if","int","long","register","return","short","signed",
    "sizeof","static","struct","switch","typedef","union",
    "unsigned","void","volatile","while"
};

int isKeyword(const char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=' || ch == '<' || ch == '>' || ch == '%';
}

void analyze(FILE *fp) {
    char ch, buffer[100];
    int i = 0;

    while ((ch = fgetc(fp)) != EOF) {
        if (isOperator(ch)) {
            printf("Operator: %c\n", ch);
        } else if (isalnum(ch) || ch == '_') {
            buffer[i++] = ch;
        } else if (isspace(ch) || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}') {
            if (i != 0) {
                buffer[i] = '\0';
                i = 0;

                if (isKeyword(buffer)) {
                    printf("Keyword: %s\n", buffer);
                } else {
                    printf("Identifier: %s\n", buffer);
                }
            }
        }
    }
}

int main() {
    FILE *fp = fopen("input.txt", "r");

    if (!fp) {
        printf("Error: Cannot open file\n");
        return 1;
    }

    printf("Lexical Analysis:\n\n");
    analyze(fp);
    fclose(fp);
    return 0;
}

