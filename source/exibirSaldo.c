#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int exibirSaldo(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    Usuario usuario;
    int bytes = sizeof(Usuario);

    // Abrir o arquivo para leitura
    ptrArquivo = fopen("clientes.bin", "rb");
    if(ptrArquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 2;
    }
    
    while(fread(&usuario, bytes, 1, ptrArquivo) == 1)
    {
        if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0)
        {
            printf("\nCPF: %s\n", ptrUsuario->cpf);
            printf("Saldo em R$: %.2f\n", ptrUsuario->saldoReais);
            printf("Saldo em Bitcoin: %.8lf\n", ptrUsuario->saldoBTC);
            printf("Saldo em Ethereum: %.8lf\n", ptrUsuario->saldoETH);
            printf("Saldo em Ripple: %.8lf\n\n", ptrUsuario->saldoRIPPLE);
            fclose(ptrArquivo);
            return 1;
            break;
        }
    }
    fclose(ptrArquivo);
    return 0;
}