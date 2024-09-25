#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int verificaCPF(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    int bytes = sizeof(Usuario);
    long posicaoArquivo;

    // Abrir o arquivo para leitura
    ptrArquivo = fopen("clientes.bin", "rb");
    if (ptrArquivo == NULL)
    {
        // Se o arquivo não existir, ele será criado
        ptrArquivo = fopen("clientes.bin", "wb");
        if (ptrArquivo == NULL)
        {
            perror("Erro ao criar o arquivo");
            return -1;
        }
        //arquivo vazio, retorna -1
        fclose(ptrArquivo);
        return -1;
    }

    Usuario usuario;

    while(fread(&usuario, bytes, 1, ptrArquivo) == 1)
    {
        posicaoArquivo = ftell(ptrArquivo) - bytes;
        if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0)
        {
            //passa os valores do arquivo para a struct
            strcpy(ptrUsuario->cpf, usuario.cpf);
            strcpy(ptrUsuario->senha, usuario.senha);
            ptrUsuario->saldoReais = usuario.saldoReais;
            ptrUsuario->saldoBTC = usuario.saldoBTC;
            ptrUsuario->saldoETH = usuario.saldoETH;
            ptrUsuario->saldoRIPPLE = usuario.saldoRIPPLE;
            
            
            fclose(ptrArquivo);
            return posicaoArquivo;
        }
    }

    fclose(ptrArquivo);
    return -1;
}