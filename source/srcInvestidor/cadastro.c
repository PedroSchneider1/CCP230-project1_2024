#include <stdio.h>
#include "funcoes.h"

int cadastro(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    Usuario usuario;
    int bytes = sizeof(Usuario);
    int qttClientes = 0;

    ptrArquivo = fopen("clientes.bin", "rb+");

    if(ptrArquivo == NULL)
    {
        ptrArquivo = fopen("clientes.bin", "wb");
    }

    while(fread(&usuario, bytes, 1, ptrArquivo) == 1)
    {
        qttClientes++;
    }

    if(qttClientes >=9)
    {
        fclose(ptrArquivo);
        return -1;
    }

    ptrUsuario->saldoBTC = 0.0; 
    ptrUsuario->saldoETH = 0.0;
    ptrUsuario->saldoRIPPLE = 0.0;
    ptrUsuario->saldoReais = 0.0;
    ptrUsuario->qttExtrato = 0;

    fwrite(ptrUsuario, bytes, 1, ptrArquivo);
    fclose(ptrArquivo);

    return 0;
}