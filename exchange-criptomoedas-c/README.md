# Exchange de criptomoedas em C

Simulador acadêmico de uma corretora no terminal. É possível consultar saldo e extrato, depositar e sacar reais, comprar e vender BTC, ETH e XRP com taxas e simular variações nas cotações.

## Como rodar

Com o GCC instalado, abra o terminal nesta pasta e execute:

```sh
gcc exchange.c -o exchange.exe
```


| Acesso de demonstração | Valor |
| --- | --- |
| CPF fictício | `00000000000` |
| Senha de teste | `123456` |

Use ponto nos valores decimais. O programa lê e grava os dados na pasta atual.

## Arquivos

| Arquivo | Conteúdo |
| --- | --- |
| [`exchange.c`](exchange.c) | Código do simulador |
| [`carteira.txt`](carteira.txt) | Conta fictícia e saldos iniciais |
| [`cotacoes.txt`](cotacoes.txt) | Cotações iniciais simuladas, em reais, na ordem BTC, ETH e XRP |
| [`extrato.txt`](extrato.txt) | Histórico de operações, inicialmente vazio |
