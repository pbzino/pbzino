# Exchange de criptomoedas em C

Simulador acadêmico de uma corretora no terminal. É possível consultar saldo e extrato, depositar e sacar reais, comprar e vender BTC, ETH e XRP com taxas e simular variações nas cotações.

## Como rodar

Com o GCC instalado, abra o terminal nesta pasta e execute:

```sh
gcc exchange.c carteira.c criptomoedas.c -o exchange.exe
./exchange.exe
```

Os três arquivos `.c` são compilados juntos para formar o executável. O `main()` continua em `exchange.c`, e cada arquivo `.c` declara as funções e os dados de outros arquivos que utiliza.

| Acesso de demonstração | Valor |
| --- | --- |
| CPF fictício | `67426742677` |
| Senha de teste | `123456` |

Use ponto nos valores decimais. O programa lê e grava os dados na pasta atual.

## Arquivos

| Arquivo | Conteúdo |
| --- | --- |
| [`exchange.c`](exchange.c) | Leitura e validação das entradas, inicialização e menu principal (`main`) |
| [`carteira.c`](carteira.c) | Dados da conta, leitura e gravação dos TXT, login, saldo, depósitos, saques e extrato |
| [`criptomoedas.c`](criptomoedas.c) | Seleção de moeda, compra, venda e atualização de cotações |
| [`carteira.txt`](carteira.txt) | Conta fictícia e saldos iniciais |
| [`cotacoes.txt`](cotacoes.txt) | Cotações iniciais simuladas, em reais, na ordem BTC, ETH e XRP |
| [`extrato.txt`](extrato.txt) | Histórico de operações, inicialmente vazio |
