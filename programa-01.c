// Código fonte do programa 1 - Conversão de expressão infixa para pós-fixa

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Função para verificar se o caractere é um operador
int ehOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Função para definir a precedência dos operadores
int precedencia(char op) {
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
void infixaParaPosfixa(char* infixa, char* posfixa) {
    char pilha[MAX];
    int topo = -1;
    int k = 0;
    for (int i = 0; infixa[i]; i++) {
        // Ignorar espaços
        if (infixa[i] == ' ') continue;

        // Se o caractere é um dígito, adicioná-lo à saída
        if (isdigit(infixa[i])) {
            while (isdigit(infixa[i])) {
                posfixa[k++] = infixa[i++];
            }
            posfixa[k++] = ' ';
            i--; // Corrige o incremento adicional
        }
        // Se o caractere é um operador
        else if (ehOperador(infixa[i])) {
            while (topo != -1 && precedencia(pilha[topo]) >= precedencia(infixa[i])) {
                posfixa[k++] = pilha[topo--];
                posfixa[k++] = ' ';
            }
            pilha[++topo] = infixa[i];
        }
    }
    // Desempilhar os operadores restantes
    while (topo != -1) {
        posfixa[k++] = pilha[topo--];
        posfixa[k++] = ' ';
    }
    posfixa[k] = '\0';
}

int main() {
    char infixa[MAX], posfixa[MAX];

    printf("Digite uma expressão infixa: ");
    fgets(infixa, MAX, stdin);

    infixaParaPosfixa(infixa, posfixa);

    printf("Expressão pós-fixa: %s\n", posfixa);

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
