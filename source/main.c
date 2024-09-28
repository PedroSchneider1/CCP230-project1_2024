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

    int retorno, status, cliente = 0;

    do
    {
        retorno = exibirMenuVisitante(); // Ensure exibirMenuVisitante takes no arguments
        switch (retorno)
        {

        // cadastro
        case 1:
            limpaBuffer();
            int tamanhoCPF;
            do
            {
                
                printf("Digite seu CPF (11 digitos): ");
                fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);
                printf("%s\n", ptrUsuario->cpf);
                tamanhoCPF = strlen(ptrUsuario->cpf);
                printf("%d\n", tamanhoCPF);
                // Verifica o comprimento
                if (tamanhoCPF!= 12)
                {
                    printf("CPF invalido.\n");
                }
            } while (tamanhoCPF != 12); // Continua até ter 11 caracteres + \n

            status = verificaCPF(ptrUsuario); // 1 = CPF já cadastrado, 0 = CPF não cadastrado
            if (status == 0)
            {
                printf("CPF ja cadastrado\n");
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
                status = cadastro(ptrUsuario);
                if (status == -1)
                {
                    printf("Quantidade maxima de clientes atingida\n");
                }
                else
                {
                    printf("Cadastro realizado com sucesso\n");
                }
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
                    printf("Deposito realizado com sucesso\n");
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
                status = venderCripto(ptrUsuario);

                if (status == 0)
                {
                    printf("Usuario nao encontrado\n");
                }
                else if(status == -1)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else if(status == 2)
                {
                    printf("Saldo insuficiente para venda\n");
                }
                else
                {
                    printf("Venda realizada com sucesso\n");
                }
                break;
            case 6:
                status = atualizarCotacao();

                if(status == -1)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else if(status == 0)
                {
                    printf("Criptomoeda nao encontrada\n");
                }
                else
                {
                    printf("Cotação atualizada com sucesso\n");
                }

                break;
            case 7:
                status = consultaExtrato(ptrUsuario);
                if(status == 0)
                {
                    printf("Extrato nao encontrado\n");
                }
                else if(status == -1)
                {
                    printf("Erro ao abrir o arquivo\n");
                }
                else
                {
                    printf("Extrato consultado com sucesso\n");
                }
                break;
            case 8:
                exit(0);
            }
            limpaBuffer();

        } while (retorno != 8);
    }

    return 0;
}