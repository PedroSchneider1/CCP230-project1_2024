#include <stdio.h>
#include <funcoes.h>

int main(){
    int retorno;

    do{
        retorno = exibirMenuADM();

        switch (retorno)
        {
        case 1:
            // cadastro();
            break;
        case 2:
            // excluirInvestidor();
            break;
        case 3:
            // cadastroCripto();
            break;
        case 4:
            // excluirCripto();
            break;
        case 5:
            // consultaSaldo();
            break;
        case 6:
            // consultaExtrato();
            break;
        case 7:
            // atualizarCotacao();
            break;
        case 8:
            printf("Saindo...\n");
            break;
        default:
            break;
        }
    }while (retorno != 8); 
    

    return 0;
}