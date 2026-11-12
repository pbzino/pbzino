#ifndef EXCHANGE_H
#define EXCHANGE_H

// Dados compartilhados e arquivos.
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

// Leitura e validacao.
void lerTexto(char texto[], int tamanho);
int somenteDigitos(char texto[], int quantidade);
int lerOpcao(void);
double lerValor(void);

// Autenticacao.
int conferirSenha(void);
int login(void);

// Carteira.
void mostrarIdentificacao(void);
void mostrarSaldo(void);
void depositar(void);
void sacar(void);

// Extrato.
void registrarOperacao(char operacao[], char moeda[], double valor,
                       double quantidade, double cotacaoUsada, double taxa);
void consultarExtrato(void);

// Criptomoedas.
int escolherMoeda(void);
void comprar(void);
void vender(void);
void atualizarCotacoes(void);

#endif
