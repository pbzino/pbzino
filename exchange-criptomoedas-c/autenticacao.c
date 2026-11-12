#include <stdio.h>
#include <string.h>
#include "autenticacao.h"
#include "dados.h"
#include "entrada.h"

int conferirSenha(void) {
    char digitada[100];
    printf("Senha de 6 digitos: ");
    lerTexto(digitada, 100);
    if (somenteDigitos(digitada, 6) && strcmp(digitada, senha) == 0) {
        return 1;
    }
    printf("Senha incorreta.\n");
    return 0;
}

int login(void) {
    char cpfDigitado[100], senhaDigitada[100];
    printf("\nCPF (11 digitos, sem pontos ou tracos; 0 para sair): ");
    lerTexto(cpfDigitado, 100);
    if (strcmp(cpfDigitado, "0") == 0) {
        return -1;
    }
    printf("Senha de 6 digitos: ");
    lerTexto(senhaDigitada, 100);
    if (somenteDigitos(cpfDigitado, 11) && somenteDigitos(senhaDigitada, 6) &&
        strcmp(cpfDigitado, cpf) == 0 && strcmp(senhaDigitada, senha) == 0) {
        return 1;
    }
    printf("CPF ou senha incorretos.\n");
    return 0;
}
