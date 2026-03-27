#include <stdio.h>
#include <ctype.h> 
#include <math.h>

char stack[100]; int top = -1;

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }
char peek() { return stack[top]; }

int prec(char c) {
    if (c == '^') return 3;
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}
void toPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    while (infix[i]) {
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) postfix[j++] = infix[i++];
            postfix[j++] = ' ';
        }
        else if (infix[i] == '(') push(infix[i++]);
        else if (infix[i] == ')') {
            while (peek() != '(') {postfix[j++] = pop(); postfix[j++] = ' ';}
            pop(); i++;
        }
        else {
            while (top != -1 && (prec(peek()) > prec(infix[i]) ||
                   (prec(peek()) == prec(infix[i]) && infix[i] != '^'))) {
                postfix[j++] = pop(); postfix[j++] = ' ';
            }
            push(infix[i++]);
        }
    }
    while (top != -1) { postfix[j++] = pop(); postfix[j++] = ' ';}
    postfix[j] = '\0';
}
int evaluate(char* postfix) {
    int stack[100], top = -1, i = 0;
    while (postfix[i]) {
        if (postfix[i] == ' ') { i++; continue; }
        if (isdigit(postfix[i])) {
            int num = 0;
            while (isdigit(postfix[i])) num = num * 10 + (postfix[i++] - '0');
            stack[++top] = num;
        } else {
            int b = stack[top--], a = stack[top--];
            if (postfix[i] == '+') stack[++top] = a + b;
            if (postfix[i] == '-') stack[++top] = a - b;
            if (postfix[i] == '*') stack[++top] = a * b;
            if (postfix[i] == '/') stack[++top] = a / b;
            if (postfix[i] == '^') stack[++top] = pow(a, b);
            i++;
        }
    }
    return stack[top];
}
int main() {
    char infix[100], postfix[100];
    printf("Enter infix: ");
    scanf("%[^\n]", infix);
    toPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    printf("Result: %d", evaluate(postfix));
    return 0;
}