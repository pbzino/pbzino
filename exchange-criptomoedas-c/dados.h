#ifndef DADOS_H
#define DADOS_H

extern char nome[100], cpf[12], senha[7];
extern double reais;
// Os indices 0, 1 e 2 representam Bitcoin, Ethereum e Ripple.
extern double saldo[3], cotacao[3];
extern char moedas[3][10];
extern char siglas[3][4];
extern double taxaCompra[3];
extern double taxaVenda[3];

void erroArquivo(void);
void carregarDados(void);
void salvarCarteira(void);
void salvarCotacoes(void);

#endif
