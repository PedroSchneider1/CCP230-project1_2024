#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int verificaCPF(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    int bytes = sizeof(Usuario);

    // Abrir o arquivo para leitura
    ptrArquivo = fopen("clientes.bin", "rb");
    if (ptrArquivo == NULL)
    {
        // Se o arquivo não existir, ele será criado
        ptrArquivo = fopen("clientes.bin", "wb");
        if (ptrArquivo == NULL)
        {
            perror("Erro ao criar o arquivo");
            return 2;
        }
    }

    Usuario usuario;

    while(fread(&usuario, bytes, 1, ptrArquivo) == 1)
    {
        if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0)
        {
            fclose(ptrArquivo);
            return 1;
        }
    }

    fclose(ptrArquivo);
    return 0;
}