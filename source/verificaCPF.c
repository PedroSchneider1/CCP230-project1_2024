#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int verificaCPF(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    int bytes = sizeof(Usuario);

    // Abrir o arquivo para leitura
    ptrArquivo = fopen("clientes.bin", "rb");
    if (ptrArquivo == NULL) {
        perror("Erro ao abrir o arquivo para leitura");
        return 1;
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