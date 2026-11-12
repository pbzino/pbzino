#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "autenticacao.h"
#include "carteira.h"
#include "criptomoedas.h"
#include "dados.h"
#include "entrada.h"
#include "extrato.h"

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
