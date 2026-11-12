#include <stdio.h>
#include <time.h>
#include "extrato.h"
#include "autenticacao.h"
#include "carteira.h"
#include "dados.h"

// O modo a acrescenta uma linha sem apagar as operacoes anteriores.
void registrarOperacao(char operacao[], char moeda[], double valor,
                       double quantidade, double cotacaoUsada, double taxa) {
    FILE *arquivo = fopen("extrato.txt", "a");
    time_t agora = time(NULL);
    char data[30];
    int resultado, fechamento;
    if (arquivo == NULL) {
        erroArquivo();
    }
    // time obtem o horario; localtime e strftime montam a data legivel.
    strftime(data, sizeof(data), "%d-%m-%Y %H:%M:%S", localtime(&agora));
    resultado = fprintf(arquivo,
        "%s | %s %s | VALOR: %.2f | QTD: %.8f | CT: %.8f | TX: %.2f | "
        "TAXA_R$: %.2f | REAL: %.2f BTC: %.8f ETH: %.8f XRP: %.8f\n",
        data, operacao, moeda, valor, quantidade, cotacaoUsada, taxa,
        valor * taxa, reais, saldo[0], saldo[1], saldo[2]);
    fechamento = fclose(arquivo);
    if (resultado < 0 || fechamento != 0) {
        erroArquivo();
    }
}

void consultarExtrato(void) {
    FILE *arquivo;
    char linha[600];
    int vazio = 1;
    if (!conferirSenha()) {
        return;
    }
    arquivo = fopen("extrato.txt", "r");
    if (arquivo == NULL) {
        erroArquivo();
    }
    mostrarIdentificacao();
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha);
        vazio = 0;
    }
    fclose(arquivo);
    if (vazio) {
        printf("Nenhuma operacao realizada.\n");
    }
}
