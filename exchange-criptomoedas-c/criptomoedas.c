#include <stdio.h>
#include <stdlib.h>

#include "exchange.h"

int escolherMoeda(void) {
    int i, opcao;
    for (i = 0; i < 3; i++) {
        printf("%d. %s - R$ %.8f | Compra: %.0f%% | Venda: %.0f%%\n",
               i + 1, moedas[i], cotacao[i], taxaCompra[i] * 100, taxaVenda[i] * 100);
    }
    printf("Escolha a moeda: ");
    opcao = lerOpcao();
    if (opcao < 1 || opcao > 3) {
        printf("Moeda invalida.\n");
        return -1;
    }
    return opcao - 1;
}

void comprar(void) {
    int moeda;
    double valor, total, quantidade;
    if (!conferirSenha()) {
        return;
    }
    moeda = escolherMoeda();
    if (moeda == -1) {
        return;
    }
    printf("Valor em reais para comprar (a taxa sera somada): ");
    valor = lerValor();
    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    // Exemplo: R$ 100 de Bitcoin custam R$ 102, incluindo a taxa de 2%.
    total = valor + valor * taxaCompra[moeda];
    quantidade = valor / cotacao[moeda];
    if (total > reais) {
        printf("Saldo insuficiente para a compra e a taxa.\n");
        return;
    }
    if (saldo[moeda] + quantidade > 1e15) {
        printf("Quantidade acima do limite.\n");
        return;
    }
    reais = reais - total;
    saldo[moeda] = saldo[moeda] + quantidade;
    salvarCarteira();
    registrarOperacao("COMPRA", siglas[moeda], valor, quantidade,
                      cotacao[moeda], taxaCompra[moeda]);
    printf("Compra realizada. Total pago: R$ %.2f\n", total);
    mostrarSaldo();
}

void vender(void) {
    int moeda;
    double quantidade, valor, recebido;
    if (!conferirSenha()) {
        return;
    }
    moeda = escolherMoeda();
    if (moeda == -1) {
        return;
    }
    printf("Saldo disponivel: %.17g %s\n", saldo[moeda], siglas[moeda]);
    printf("Quantidade de criptomoeda para vender: ");
    quantidade = lerValor();
    if (quantidade <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    if (quantidade > saldo[moeda]) {
        printf("Saldo de criptomoeda insuficiente.\n");
        return;
    }
    // Na venda, a taxa e descontada do valor convertido para reais.
    valor = quantidade * cotacao[moeda];
    recebido = valor - valor * taxaVenda[moeda];
    if (reais + recebido > 1e15) {
        printf("Valor acima do limite.\n");
        return;
    }
    saldo[moeda] = saldo[moeda] - quantidade;
    reais = reais + recebido;
    salvarCarteira();
    registrarOperacao("VENDA", siglas[moeda], valor, quantidade,
                      cotacao[moeda], taxaVenda[moeda]);
    printf("Venda realizada. Valor recebido: R$ %.2f\n", recebido);
    mostrarSaldo();
}

void atualizarCotacoes(void) {
    int i;
    double variacao, novas[3];
    for (i = 0; i < 3; i++) {
        // rand() % 11 sorteia de 0 a 10; subtrair 5 gera de -5 a 5.
        variacao = (rand() % 11 - 5) / 100.0;
        novas[i] = cotacao[i] * (1 + variacao);
        if (!(novas[i] > 0 && novas[i] <= 1e15)) {
            printf("Cotacao fora do limite. Atualizacao cancelada.\n");
            return;
        }
    }
    for (i = 0; i < 3; i++) {
        cotacao[i] = novas[i];
    }
    salvarCotacoes();
    printf("Cotacoes atualizadas:\n");
    for (i = 0; i < 3; i++) {
        printf("%s: R$ %.8f\n", moedas[i], cotacao[i]);
    }
}
