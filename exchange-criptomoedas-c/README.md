# Exchange de criptomoedas em C

Simulador acadêmico de uma corretora no terminal. É possível consultar saldo e extrato, depositar e sacar reais, comprar e vender BTC, ETH e XRP com taxas e simular variações nas cotações.

## Como rodar

Com o GCC instalado, abra o terminal nesta pasta e execute:

```sh
gcc -std=c11 -Wall -Wextra -pedantic exchange.c entrada.c dados.c autenticacao.c carteira.c extrato.c criptomoedas.c -o exchange.exe
```

Execute na mesma pasta dos arquivos TXT:

```sh
./exchange.exe
```

Os arquivos `.h` declaram as funções e os dados compartilhados. Cada `.c` inclui os cabeçalhos de que precisa; o GCC compila e liga todos os módulos no executável `exchange.exe`.

| Acesso de demonstração | Valor |
| --- | --- |
| CPF fictício | `67426742677` |
| Senha de teste | `123456` |

Use ponto nos valores decimais. O programa lê e grava os dados na pasta atual.

## Arquivos

| Arquivo | Conteúdo |
| --- | --- |
| [`exchange.c`](exchange.c) | Ponto de entrada (`main`), inicialização e menu |
| [`entrada.c`](entrada.c) / [`entrada.h`](entrada.h) | Leitura e validação das entradas |
| [`dados.c`](dados.c) / [`dados.h`](dados.h) | Dados compartilhados e leitura/gravação da carteira e cotações |
| [`autenticacao.c`](autenticacao.c) / [`autenticacao.h`](autenticacao.h) | Login e conferência de senha |
| [`carteira.c`](carteira.c) / [`carteira.h`](carteira.h) | Identificação, saldo, depósitos e saques |
| [`extrato.c`](extrato.c) / [`extrato.h`](extrato.h) | Registro e consulta das operações |
| [`criptomoedas.c`](criptomoedas.c) / [`criptomoedas.h`](criptomoedas.h) | Seleção de moeda, compra, venda e atualização de cotações |
| [`carteira.txt`](carteira.txt) | Conta fictícia e saldos iniciais |
| [`cotacoes.txt`](cotacoes.txt) | Cotações iniciais simuladas, em reais, na ordem BTC, ETH e XRP |
| [`extrato.txt`](extrato.txt) | Histórico de operações, inicialmente vazio |
