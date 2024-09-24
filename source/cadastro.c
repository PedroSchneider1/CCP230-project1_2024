#include <stdio.h>
#include "funcoes.h"

int cadastro(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    char linha[255];
    int bytes = sizeof(Usuario);

    ptrArquivo = fopen("clientes.bin", "ab");

    if(ptrArquivo == NULL)
    {
        ptrArquivo = fopen("clientes.bin", "wb");
    }

    fwrite(ptrUsuario, bytes, 1, ptrArquivo);
    fclose(ptrArquivo);

    // Abrir o arquivo para leitura
    ptrArquivo = fopen("clientes.bin", "rb");
    if (ptrArquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return 1;
    }

    while(fread(ptrUsuario, bytes, 1, ptrArquivo) == 1)
    {
        printf("CPF do cliente: %s", ptrUsuario->cpf);
        printf("Senha do cliente: %s", ptrUsuario->senha);
        printf("Saldo BTC: %.2f\n", ptrUsuario->saldoBTC);
        printf("Saldo ETH: %.2f\n", ptrUsuario->saldoETH);
        printf("Saldo RIPPLE: %.2f\n", ptrUsuario->saldoRIPPLE);
        printf("Saldo em Reais: %.2f\n", ptrUsuario->saldoReais);
    }

    fclose(ptrArquivo);
}