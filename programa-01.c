// Código fonte do programa 1 - Conversão de expressão infixa para pós-fixa

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Função para verificar se o caractere é um operador
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Função para definir a precedência dos operadores
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// Função para converter expressão infixa para pós-fixa
void infixToPostfix(char* infix, char* postfix) {
    char stack[MAX];
    int top = -1;
    int k = 0;
    for (int i = 0; infix[i]; i++) {
        // Ignorar espaços
        if (infix[i] == ' ') continue;

        // Se o caractere é um dígito, adicioná-lo à saída
        if (isdigit(infix[i])) {
            while (isdigit(infix[i])) {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
            i--; // Corrige o incremento adicional
        }
        // Se o caractere é um operador
        else if (isOperator(infix[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[k++] = stack[top--];
                postfix[k++] = ' ';
            }
            stack[++top] = infix[i];
        }
    }
    // Desempilhar os operadores restantes
    while (top != -1) {
        postfix[k++] = stack[top--];
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Digite uma expressão infixa: ");
    fgets(infix, MAX, stdin);

    infixToPostfix(infix, postfix);

    printf("Expressão pós-fixa: %s\n", postfix);

    return 0;
}

/* 
  Exemplo de expressões infixas (sem parênteses):
  - 1 + 2                         => Resultado: 1 2 +
  - 1 + 2 * 3                     => Resultado: 1 2 3 * +
  - 1 + 2 * 3 - 4                 => Resultado: 1 2 3 * + 4 -
  - 1 + 2 * 3 - 4 / 5 * 6         => Resultado: 1 2 3 * + 4 5 / 6 * -
  - 1 + 2 * 3 - 4 / 5 * 6 + 7     => Resultado: 1 2 3 * + 4 5 / 6 * - 7 +
  - 1 + 2 * 3 - 4 / 5 * 6 + 7 * 8 => Resultado: 1 2 3 * + 4 5 / 6 * - 7 8 * +
*/

