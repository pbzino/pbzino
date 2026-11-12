#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "entrada.h"

char nome[100], cpf[12], senha[7];
double reais;
// Os indices 0, 1 e 2 representam Bitcoin, Ethereum e Ripple.
double saldo[3], cotacao[3];
char moedas[3][10] = {"Bitcoin", "Ethereum", "Ripple"};
char siglas[3][4] = {"BTC", "ETH", "XRP"};
double taxaCompra[3] = {0.02, 0.01, 0.01};
double taxaVenda[3] = {0.03, 0.02, 0.01};

// Encerra se nao for possivel acessar os arquivos do projeto.
void erroArquivo(void) {
    printf("Erro nos arquivos. Confira os TXT e a permissao da pasta.\n");
    exit(1);
}

void carregarDados(void) {
    FILE *arquivo;
    int i, lidos;
    arquivo = fopen("carteira.txt", "r");
    if (arquivo == NULL) {
        erroArquivo();
    }
    lidos = fscanf(arquivo, "%99[^\n]\n%11s\n%6s\n%lf\n%lf %lf %lf",
                   nome, cpf, senha, &reais, &saldo[0], &saldo[1], &saldo[2]);
    fclose(arquivo);
    if (lidos != 7 || !somenteDigitos(cpf, 11) ||
        !somenteDigitos(senha, 6) || !(reais >= 0 && reais <= 1e15)) {
        erroArquivo();
    }
    arquivo = fopen("cotacoes.txt", "r");
    if (arquivo == NULL) {
        erroArquivo();
    }
    lidos = fscanf(arquivo, "%lf %lf %lf", &cotacao[0], &cotacao[1], &cotacao[2]);
    fclose(arquivo);
    if (lidos != 3) {
        erroArquivo();
    }
    for (i = 0; i < 3; i++) {
        if (!(saldo[i] >= 0 && saldo[i] <= 1e15) ||
            !(cotacao[i] > 0 && cotacao[i] <= 1e15)) {
            erroArquivo();
        }
    }
    // O extrato vazio acompanha o projeto e nao deve ser apagado.
    arquivo = fopen("extrato.txt", "r");
    if (arquivo == NULL) {
        erroArquivo();
    }
    fclose(arquivo);
}

// O modo w substitui o conteudo antigo pelos dados atualizados.
void salvarCarteira(void) {
    FILE *arquivo = fopen("carteira.txt", "w");
    int resultado, fechamento;
    if (arquivo == NULL) {
        erroArquivo();
    }
    resultado = fprintf(arquivo, "%s\n%s\n%s\n%.17g\n%.17g %.17g %.17g\n",
                        nome, cpf, senha, reais, saldo[0], saldo[1], saldo[2]);
    fechamento = fclose(arquivo);
    if (resultado < 0 || fechamento != 0) {
        erroArquivo();
    }
}

void salvarCotacoes(void) {
    FILE *arquivo = fopen("cotacoes.txt", "w");
    int resultado, fechamento;
    if (arquivo == NULL) {
        erroArquivo();
    }
    resultado = fprintf(arquivo, "%.17g %.17g %.17g\n",
                        cotacao[0], cotacao[1], cotacao[2]);
    fechamento = fclose(arquivo);
    if (resultado < 0 || fechamento != 0) {
        erroArquivo();
    }
}
