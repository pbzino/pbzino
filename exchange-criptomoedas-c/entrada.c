#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entrada.h"

// Le uma linha inteira e descarta o excesso se a entrada for muito longa.
void lerTexto(char texto[], int tamanho) {
    int i = 0, caractere;
    if (fgets(texto, tamanho, stdin) == NULL) {
        printf("\nEntrada encerrada.\n");
        exit(0);
    }
    while (texto[i] != '\0' && texto[i] != '\n') {
        i++;
    }
    if (texto[i] == '\n') {
        texto[i] = '\0';
    } else {
        caractere = getchar();
        if (caractere != '\n' && caractere != EOF) {
            while (caractere != '\n' && caractere != EOF) {
                caractere = getchar();
            }
            texto[0] = '\0';
            printf("Entrada muito longa.\n");
        }
    }
}

// CPF e senha sao strings para preservar zeros no inicio.
int somenteDigitos(char texto[], int quantidade) {
    int i;
    if (strlen(texto) != (unsigned int) quantidade) {
        return 0;
    }
    for (i = 0; i < quantidade; i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return 0;
        }
    }
    return 1;
}

// O caractere extra detecta entradas como 100abc ou 2.5 no menu( oque é invalido).
int lerOpcao(void) {
    char texto[100], extra;
    int opcao;
    lerTexto(texto, 100);
    if (strlen(texto) > 9) {
        return -1;
    }
    if (sscanf(texto, "%d %c", &opcao, &extra) != 1) {
        return -1;
    }
    return opcao;
}

double lerValor(void) {
    char texto[100], extra;
    double valor;
    lerTexto(texto, 100);
    if (sscanf(texto, "%lf %c", &valor, &extra) != 1) {
        return -1;
    }
    // O limite evita valores exagerados e tambem rejeita infinito.
    if (!(valor > 0 && valor <= 1000000000.0)) {
        return -1;
    }
    return valor;
}
