#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "exchange.h"

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
