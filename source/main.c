#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int main()
{
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
            const float cotacoes[] = {50000.0, 2000.0, 10.0};

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

    int retorno, status, cliente = 0;

    do
    {
        retorno = exibirMenuVisitante(); // Ensure exibirMenuVisitante takes no arguments
        switch (retorno)
        {

        // cadastro
        case 1:
            limpaBuffer();
            printf("Digite seu CPF: ");
            fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);

            status = verificaCPF(ptrUsuario); // 1 = CPF já cadastrado, 0 = CPF não cadastrado
            if (status == 0)
            {
                printf("CPF já cadastrado\n");
                break;
            }
            else if (status == 2)
            {
                printf("Erro ao abrir o arquivo\n");
                break;
            }
            else
            {
                limpaBuffer();
                printf("Digite sua senha: ");
                fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
                cadastro(ptrUsuario);
                break;
            }
            break;

        // login
        case 2:
            limpaBuffer();
            printf("Digite seu CPF: ");
            fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);

            limpaBuffer();
            printf("Digite sua senha: ");
            fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
            status = login(ptrUsuario); // 1 = logado, 0 = não logado
            if (status)
            {
                cliente = 1;
                printf("Login Realizado com Sucesso!\n");
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
            exit(1);
            break;
        }

    } while (!cliente && retorno != 3);

    if (cliente)
    {
        do
        {
            retorno = exibirMenuCliente();
            switch (retorno)
            {
            case 1:
                status = exibirSaldo(ptrUsuario);
                if (status == 2)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else if (status == 0)
                {
                    printf("CPF não cadastrado\n");
                }
                break;
            case 2:
                status = depositar(ptrUsuario);
                if (status == -1)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else if(status == 0)
                {
                    printf("Usuario nao encontrado\n");
                }
                else
                {
                    printf("Depósito realizado com sucesso\n");
                }
                break;

            case 3:

                status = sacar(ptrUsuario);
                if (status == 0)
                {
                    printf("Usuario nao encontrado\n");
                }
                else if(status == -1)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else
                {
                    printf("Saque realizado com sucesso\n");
                }

                break;
            case 4:
                status = comprarCripto(ptrUsuario);
                if (status == 0)
                {
                    printf("Usuario nao encontrado\n");
                }
                else if(status == -1)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else
                {
                    printf("Compra realizada com sucesso\n");
                }
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                exit(0);
            }
            limpaBuffer();

        } while (retorno != 7);
    }

    return 0;
}