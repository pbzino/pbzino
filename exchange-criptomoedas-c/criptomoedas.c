#include <stdio.h>
#include <stdlib.h>

// Dados compartilhados definidos em carteira.c.
extern double reais;
extern double saldo[3], cotacao[3];
extern char moedas[3][10];
extern char siglas[3][4];
extern double taxaCompra[3], taxaVenda[3];

// Funcoes definidas em exchange.c e carteira.c.
int lerOpcao(void);
double lerValor(void);
int conferirSenha(void);
void salvarCarteira(void);
void salvarCotacoes(void);
void mostrarSaldo(void);
void registrarOperacao(char operacao[], char moeda[], double valor,
                       double quantidade, double cotacaoUsada, double taxa);

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
    double variacao;
    for (i = 0; i < 3; i++) {
        // rand() % 11 sorteia de 0 a 10; subtrair 5 gera de -5 a 5.
        variacao = (rand() % 11 - 5) / 100.0;
        cotacao[i] = cotacao[i] * (1 + variacao);
    }
    salvarCotacoes();
    printf("Cotacoes atualizadas:\n");
    for (i = 0; i < 3; i++) {
        printf("%s: R$ %.8f\n", moedas[i], cotacao[i]);
    }
}
