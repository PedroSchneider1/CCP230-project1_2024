#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


int main(){

    Usuario usuario, *ptrUsuario;
    ptrUsuario = &usuario;

    int retorno = ExibirMenuVisitante();
    //printf("%d", retorno);


    switch(retorno)
    {
        case 1:
            limpaBuffer();
            printf("Digite seu CPF: ");
            fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);

            printf("Digite sua senha: ");
            fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);

            ptrUsuario->saldoBTC = 0.0; 
            ptrUsuario->saldoETH = 0.0;
            ptrUsuario->saldoRIPPLE = 0.0;
            ptrUsuario->saldoReais = 0.0;

            cadastro(ptrUsuario);
            break;
        case 2:

            break;
        case 3:

            break;
        default:
            printf("Opção inválida, finalizando o código...");
            exit(0);
    }

    retorno = ExibirMenuCliente();

    return 0;
}