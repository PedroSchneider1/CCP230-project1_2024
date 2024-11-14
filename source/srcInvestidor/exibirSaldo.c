#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int exibirSaldo(Usuario *ptrUsuario){

    FILE *ptrArquivoAtivos,*ptrArquivoClientes;
    Ativos ativo;
    Usuario usuario;
    size_t bytesAtivos = sizeof(Ativos), bytesClientes = sizeof(Usuario);

    
    ptrArquivoClientes = fopen("clientes.bin", "rb+");
    ptrArquivoAtivos = fopen("ativos.bin", "rb+");

    if(ptrArquivoClientes == NULL) 
    {
        printf("\t*Erro ao abrir o arquivo.\n");
        fclose(ptrArquivoClientes);
        return 2;
    }
    else
    {
        while(fread(&usuario, bytesClientes, 1, ptrArquivoClientes))
        {
            if(strcmp(usuario.cpf, ptrUsuario->cpf) == 0)
            {
                printf("Saldo em reais: %.2f\n", usuario.saldoReais);
            }
        }
    }
    if(ptrArquivoAtivos == NULL) 
    {
        printf("O usuário ainda não comprou criptomoedas.\n");
        return 0;    
    }
    else
    {
        while(fread(&ativo, bytesAtivos, 1, ptrArquivoAtivos))
        {
            
            if(strcmp(ativo.CPF, ptrUsuario->cpf) == 0 && strcmp(ativo.nomeMoeda, "Real") == 0)
            {
                printf("Saldo de %s: %.2f\n", ativo.nomeMoeda, ativo.saldoCripto);
            }
            else if(strcmp(ativo.CPF, ptrUsuario->cpf) == 0)
            {
                printf("Saldo de %s: %.8f\n", ativo.nomeMoeda, ativo.saldoCripto);
            }
        }
    }

    fclose(ptrArquivoClientes);
    fclose(ptrArquivoAtivos);
    return 1;
}