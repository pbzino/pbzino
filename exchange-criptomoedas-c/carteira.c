#include <stdio.h>
#include "carteira.h"
#include "dados.h"
#include "entrada.h"
#include "extrato.h"

void mostrarIdentificacao(void) {
    printf("\nNome: %s\n", nome);
    printf("CPF: %.3s.%.3s.%.3s-%.2s\n", cpf, cpf + 3, cpf + 6, cpf + 9);
}

void mostrarSaldo(void) {
    int i;
    mostrarIdentificacao();
    printf("Reais: R$ %.2f\n", reais);
    for (i = 0; i < 3; i++) {
        printf("%s: %.8f\n", moedas[i], saldo[i]);
    }
}

void depositar(void) {
    double valor;
    printf("Valor do deposito em reais: ");
    valor = lerValor();
    if (valor <= 0 || reais + valor > 1e15) {
        printf("Valor invalido.\n");
        return;
    }
    reais = reais + valor;
    salvarCarteira();
    registrarOperacao("DEPOSITO", "REAL", valor, valor, 0, 0);
    printf("Deposito realizado.\n");
    mostrarSaldo();
}

void sacar(void) {
    double valor;
    printf("Valor do saque em reais: ");
    valor = lerValor();
    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    if (valor > reais) {
        printf("Saldo insuficiente.\n");
        return;
    }
    reais = reais - valor;
    salvarCarteira();
    registrarOperacao("SAQUE", "REAL", valor, valor, 0, 0);
    printf("Saque realizado.\n");
    mostrarSaldo();
}
