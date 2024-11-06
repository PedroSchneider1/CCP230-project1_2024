#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoes.h>

int main(){

    // cria criptos ao iniciar modulo de adm
    FILE *ptrArquivo;

    ptrArquivo = fopen("criptomoedas.bin", "rb");
    if (ptrArquivo == NULL) // só cria se não existir
    {
        ptrArquivo = fopen("criptomoedas.bin", "wb");
        if (ptrArquivo == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
        else
        {
            const char *nomesCriptos[] = {"Bitcoin", "Ethereum", "Ripple"};
            const float taxasCompra[] = {2.0, 1.0, 1.0};
            const float taxasVenda[] = {3.0, 2.0, 1.0};
            const float cotacoes[] = {50000, 20000, 10};

            for (int i = 0; i < 3; i++)
            {
                Criptomoedas criptomoedas;
                strcpy(criptomoedas.nomeCripto, nomesCriptos[i]);
                criptomoedas.cotacao = cotacoes[i];
                criptomoedas.txCompra = taxasCompra[i];
                criptomoedas.txVenda = taxasVenda[i];
                fwrite(&criptomoedas, sizeof(Criptomoedas), 1, ptrArquivo);
            }
        }
    }
    fclose(ptrArquivo);

    Usuario usuario, *ptrUsuario;
    ptrUsuario = &usuario;
    int retorno, status = 0;

    do{
        retorno = exibirMenuADM();

        switch (retorno)
        {
        case 1:
            limpaBuffer();
            status = cadastroInvestidor(ptrUsuario);
            if(!status){
                printf("Algum erro ocorreu durante a operacao. Por favor, tente novamente.\n");
            }
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