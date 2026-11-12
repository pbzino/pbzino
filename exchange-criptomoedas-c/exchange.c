#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char nome[100], cpf[12], senha[7];
double reais;
// Os indices 0, 1 e 2 representam Bitcoin, Ethereum e Ripple.
double saldo[3], cotacao[3];
char moedas[3][10] = {"Bitcoin", "Ethereum", "Ripple"};
char siglas[3][4] = {"BTC", "ETH", "XRP"};
double taxaCompra[3] = {0.02, 0.01, 0.01};
double taxaVenda[3] = {0.03, 0.02, 0.01};

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

int main(void) {
    int acesso, opcao = 0;
    carregarDados();
    srand((unsigned int) time(NULL));
    printf("EXCHANGE DE CRIPTOMOEDAS\nUse ponto nos valores decimais.\n");
    do {
        acesso = login();
    } while (acesso == 0);
    if (acesso == -1) {
        return 0;
    }
    printf("Bem-vindo, %s!\n", nome);
    while (opcao != 8) {
        printf("\n1. Consultar saldo\n2. Consultar extrato\n3. Depositar\n");
        printf("4. Sacar\n5. Comprar criptomoedas\n6. Vender criptomoedas\n");
        printf("7. Atualizar cotacao\n8. Sair\nOpcao: ");
        opcao = lerOpcao();
        switch (opcao) {
            case 1:
                if (conferirSenha()) {
                    mostrarSaldo();
                }
                break;
            case 2: consultarExtrato(); break;
            case 3: depositar(); break;
            case 4: sacar(); break;
            case 5: comprar(); break;
            case 6: vender(); break;
            case 7: atualizarCotacoes(); break;
            case 8: printf("Programa encerrado.\n"); break;
            default: printf("Opcao invalida.\n");
        }
    }
    return 0;
}
