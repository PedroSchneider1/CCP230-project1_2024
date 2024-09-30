#include <stdio.h>
#include "funcoes.h"
#include <string.h>

int login(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    Usuario usuario;
    
    ptrArquivo = fopen("clientes.bin", "rb");
    if (ptrArquivo == NULL) {
        perror("Nao ha usuarios cadastrados.");
        return 0;
    }

    while(fread(&usuario, sizeof(Usuario), 1, ptrArquivo) == 1)
    {
        if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0 && strcmp(usuario.senha, ptrUsuario->senha) == 0)
        {
            fclose(ptrArquivo);
            return 1;
        }
    }

    return 0;

}
