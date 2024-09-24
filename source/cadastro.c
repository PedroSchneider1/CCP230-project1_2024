#include <stdio.h>
#include "funcoes.h"

int cadastro(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    int bytes = sizeof(Usuario);

    ptrArquivo = fopen("clientes.bin", "ab");

    if(ptrArquivo == NULL)
    {
        ptrArquivo = fopen("clientes.bin", "wb");
    }

    ptrUsuario->saldoBTC = 0.0; 
    ptrUsuario->saldoETH = 0.0;
    ptrUsuario->saldoRIPPLE = 0.0;
    ptrUsuario->saldoReais = 0.0;

    if(verificaCPF(ptrUsuario))
    {
        fclose(ptrArquivo);
        return 1;
    }

    fwrite(ptrUsuario, bytes, 1, ptrArquivo);
    fclose(ptrArquivo);

    return 0;
}