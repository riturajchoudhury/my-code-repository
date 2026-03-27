#include <stdio.h>
#define MAX 1000

char stack[MAX];
int top = -1;

void push(char ch) {
    if (top < MAX - 1)
        stack[++top] = ch;
}

char pop() {
    if (top >= 0)
        return stack[top--];
    return '\0';
}

int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int checkParentheses(FILE *fp) {
    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '(' || ch == '{' || ch == '[')
            push(ch);
        else if (ch == ')' || ch == '}' || ch == ']') {
            char open = pop();
            if (!isMatchingPair(open, ch))
                return 0;
        }
    }
    return top == -1;
}

int main() {
    char filename[100];
    FILE *fp;

    printf("Enter the filename to check: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    if (checkParentheses(fp))
        printf("Parentheses are balanced.\n");
    else
        printf("Parentheses are NOT balanced.\n");

    fclose(fp);
    return 0;
}