#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main()
{
    FILE *ptrArquivo;

    ptrArquivo = fopen("criptomoedas.bin", "rb");
    if (ptrArquivo == NULL) //só cria se não existir
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
            for (int i = 0; i < 3; i++)
            {
                Criptomoedas criptomoedas;
                strcpy(criptomoedas.nomeCripto, nomesCriptos[i]);
                criptomoedas.cotacao = 0.0;
                criptomoedas.txCompra = taxasCompra[i];
                criptomoedas.txVenda = taxasVenda[i];
                fwrite(&criptomoedas, sizeof(Criptomoedas), 1, ptrArquivo);
            }
        }
    }
    fclose(ptrArquivo);

    Usuario usuario, *ptrUsuario;
    ptrUsuario = &usuario;

    int retorno, status;

    do
    {
        retorno = exibirMenuVisitante();
        switch (retorno)
        {
        case 1:
            limpaBuffer();
            printf("Digite seu CPF: ");
            fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);

            limpaBuffer();
            printf("Digite sua senha: ");
            fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
            status = cadastro(ptrUsuario);
            status == 1 ? printf("CPF já cadastrado\n") : printf("Cadastro realizado com sucesso\n");
            break;
        case 2:
            limpaBuffer();
            printf("Digite seu CPF: ");
            fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);

            limpaBuffer();
            printf("Digite sua senha: ");
            fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
            status = login(ptrUsuario); // 1 = logado, 0 = não logado
            if(status)
            {
                exibirMenuCliente();
            }
            else
            {
                printf("CPF ou senha inválidos\n");
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Opção inválida, finalizando o código...");
            break;
        }

    } while (retorno != 3 || retorno != 7);

    return 0;
}