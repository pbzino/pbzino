#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Dados e funcoes definidos nos outros arquivos do projeto.
extern char nome[100];
void carregarDados(void);
int login(void);
int conferirSenha(void);
void mostrarSaldo(void);
void consultarExtrato(void);
void depositar(void);
void sacar(void);
void comprar(void);
void vender(void);
void atualizarCotacoes(void);

// Leitura das entradas do terminal.
void lerTexto(char texto[], int tamanho) {
    int caractere;
    if (fgets(texto, tamanho, stdin) == NULL) {
        exit(0);
    }
    if (strchr(texto, '\n') == NULL) {
        while ((caractere = getchar()) != '\n' && caractere != EOF) {
        }
    }
    texto[strcspn(texto, "\n")] = '\0';
}

int lerOpcao(void) {
    char texto[100];
    int opcao = -1;
    lerTexto(texto, 100);
    sscanf(texto, "%d", &opcao);
    return opcao;
}

double lerValor(void) {
    char texto[100];
    double valor = -1;
    lerTexto(texto, 100);
    sscanf(texto, "%lf", &valor);
    return valor;
}

// Inicializacao e menu principal.
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
