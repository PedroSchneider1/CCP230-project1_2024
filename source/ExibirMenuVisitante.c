#include <stdio.h>
#include "funcoes.h"

int ExibirMenuVisitante(){

    int menu;
    while(1)
    {
        printf("Exchange de Criptomoedas\n");
        printf("1 - Realizar Cadastro\n");
        printf("2 - Realizar Login\n");
        printf("3 - Sair\n");
        scanf("%d", &menu);
        if(menu > 0 && menu < 4)
        {
            return menu;
        }
        else
        {
            printf("Opcao Invalida. Tente novamente\n\n");
            limpaBuffer();
        }   
    }
}