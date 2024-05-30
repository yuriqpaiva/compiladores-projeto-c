#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100
#define MAX_SIMBOLOS 100

typedef struct {
    char identificador[MAX];
    int linha;
} Simbolo;

Simbolo tabelaSimbolos[MAX_SIMBOLOS];
int contadorSimbolos = 0;
char erros[MAX][MAX];
int contadorErros = 0;

char *palavrasChave[] = {"int", "float", "if", "else", "while", "return", NULL};

// Função para adicionar um identificador à tabela de símbolos
void adicionarSimbolo(char *identificador, int linha) {
    strcpy(tabelaSimbolos[contadorSimbolos].identificador, identificador);
    tabelaSimbolos[contadorSimbolos].linha = linha;
    contadorSimbolos++;
}

// Função para registrar um erro
void adicionarErro(char *erro, int linha) {
    sprintf(erros[contadorErros], "Linha %d: %s", linha, erro);
    contadorErros++;
}

// Função para imprimir a tabela de símbolos
void imprimirSimbolos() {
    printf("\nSímbolos:\n");
    for (int i = 0; i < contadorSimbolos; i++) {
        printf("%s (Linha %d)\n", tabelaSimbolos[i].identificador, tabelaSimbolos[i].linha);
    }
}

// Função para imprimir os erros
void imprimirErros() {
    if (contadorErros > 0) {
        printf("\nErros:\n");
        for (int i = 0; i < contadorErros; i++) {
            printf("%s\n", erros[i]);
        }
    } else {
        printf("Nenhum erro encontrado.\n");
    }
}

// Função para verificar se um caractere é um operador aritmético ou relacional
int eOperador(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '<' || c == '>' || c == '=' || c == '!');
}

// Função para verificar se uma string é um operador relacional
int eOperadorRelacional(char *str) {
    return (!strcmp(str, "==") || !strcmp(str, "!=") || !strcmp(str, "<=") || !strcmp(str, ">="));
}

// Função para verificar se uma string é uma palavra-chave
int ePalavraChave(char *str) {
    for (int i = 0; palavrasChave[i]; i++) {
        if (strcmp(str, palavrasChave[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Função para processar a entrada e identificar tokens
void processarEntrada(char *entrada) {
    char token[MAX];
    int i = 0, j = 0, linha = 1;

    while (entrada[i]) {
        // Ignorar espaços, tabulações e quebras de linha
        if (entrada[i] == ' ' || entrada[i] == '\t' || entrada[i] == '\n') {
            if (entrada[i] == '\n') linha++;
            i++;
            continue;
        }

        // Ignorar comentários de linha
        if (entrada[i] == '/' && entrada[i + 1] == '/') {
            while (entrada[i] && entrada[i] != '\n') i++;
            continue;
        }

        // Ignorar comentários de bloco
        if (entrada[i] == '/' && entrada[i + 1] == '*') {
            i += 2;
            while (entrada[i] && !(entrada[i] == '*' && entrada[i + 1] == '/')) {
                if (entrada[i] == '\n') linha++;
                i++;
            }
            if (entrada[i]) i += 2;
            continue;
        }

        // Reconhecer números (incluindo decimais)
        if (isdigit(entrada[i])) {
            j = 0;
            while (isdigit(entrada[i]) || entrada[i] == '.') {
                token[j++] = entrada[i++];
            }
            token[j] = '\0';
            printf("Número: %s (Linha %d)\n", token, linha);
            continue;
        }

        // Reconhecer identificadores e palavras-chave
        if (isalpha(entrada[i])) {
            j = 0;
            while (isalnum(entrada[i]) || entrada[i] == '_') {
                token[j++] = entrada[i++];
            }
            token[j] = '\0';
            if (ePalavraChave(token)) {
                printf("Palavra-chave: %s (Linha %d)\n", token, linha);
            } else {
                adicionarSimbolo(token, linha);
                printf("Identificador: %s (Linha %d)\n", token, linha);
            }
            continue;
        }

        // Reconhecer operadores aritméticos e relacionais
        if (eOperador(entrada[i])) {
            j = 0;
            while (eOperador(entrada[i])) {
                token[j++] = entrada[i++];
            }
            token[j] = '\0';
            if (eOperadorRelacional(token)) {
                printf("Operador Relacional: %s (Linha %d)\n", token, linha);
            } else {
                printf("Operador: %s (Linha %d)\n", token, linha);
            }
            continue;
        }

        // Reconhecer parênteses
        if (entrada[i] == '(' || entrada[i] == ')') {
            printf("Parêntese: %c (Linha %d)\n", entrada[i], linha);
            i++;
            continue;
        }

        // Tratar caracteres inválidos
        adicionarErro("Caractere inválido", linha);
        printf("Caractere inválido: %c (Linha %d)\n", entrada[i], linha);
        i++;
    }
}

int main() {
    char entrada[MAX * MAX];
    char linha[MAX];
    int comprimentoEntrada = 0;

    printf("Digite o código (termine com uma linha vazia):\n");

    // Leitura contínua até encontrar uma linha vazia
    while (1) {
        fgets(linha, MAX, stdin);
        if (strcmp(linha, "\n") == 0) {
            break;
        }
        strcpy(&entrada[comprimentoEntrada], linha);
        comprimentoEntrada += strlen(linha);
    }

    // Processar a entrada
    processarEntrada(entrada);
    imprimirSimbolos();
    imprimirErros();

    return 0;
}
