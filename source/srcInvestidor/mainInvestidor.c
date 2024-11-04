#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
        retorno = exibirMenuVisitante();
        switch (retorno)
        {

        // cadastro
        case 1:
            limpaBuffer();

            size_t tamanhoCPF;
            int isNumeric = 1;
            
            char cpf[255];
            do
            {
                printf("\nDigite seu CPF (11 digitos): ");
                fgets(cpf, sizeof(cpf), stdin);

                tamanhoCPF = strlen(cpf);
                // Verifica o comprimento
                if (tamanhoCPF < 12 || tamanhoCPF > 13)
                {
                    printf("CPF invalido.\n");
                    printf("\t*Tamanho do CPF deve ser de 11 digitos.\n");
                }

                // Verifica se todos os caracteres são dígitos
                isNumeric = 1;
                for (size_t i = 0; i < tamanhoCPF - 1; i++) {
                    if (!isdigit(cpf[i])) {
                        isNumeric = 0;
                        break;
                    }
                }

                if (!isNumeric) {
                    printf("CPF invalido.\n");
                    printf("\t*CPF deve conter apenas numeros.\n");
                    continue;
                }

            } while (tamanhoCPF != 12 || !isNumeric); // Continua até ter 11 caracteres + \n

            if (cpf[tamanhoCPF-1] == '\n') { // Remove o \n do fim da string
                cpf[tamanhoCPF-1] = '\0';
                tamanhoCPF--;
            }

            strcpy(ptrUsuario->cpf, cpf);
            status = verificaCPF(ptrUsuario); // 1 = CPF já cadastrado, 0 = CPF não cadastrado
            
            if (status == 0)
            {
                printf("CPF ja cadastrado.\n\n");
                break;
            }
            else if (status == 2)
            {
                printf("Erro ao abrir o arquivo.\n\n");
                break;
            }
            else
            {
                printf("Digite sua senha: ");
                fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
                status = cadastro(ptrUsuario);
                if (status == -1)
                {
                    printf("Quantidade maxima de clientes atingida.\n\n");
                }
                else
                {
                    printf("Cadastro realizado com sucesso!\n\n");
                }
                break;
            }
            break;

        // login
        case 2:
            limpaBuffer();
            printf("\nDigite seu CPF: ");
            fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);

            if (strlen(ptrUsuario->cpf) == 11) { // Limpa o buffer apenas se o CPF tiver 11 caracteres
                limpaBuffer();
            }
            
            printf("Digite sua senha: ");
            fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
            status = login(ptrUsuario); // 1 = logado, 0 = não logado
            if (status)
            {
                cliente = 1;
                printf("\nLogin realizado com sucesso!\n");
            }
            else
            {
                printf("CPF ou senha invalidos.\n\n");
            }
            break;

        case 3:
            exit(0);
            break;

        default:
            printf("Opção invalida, finalizando o codigo...");
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
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else if (status == 0)
                {
                    printf("\nCPF não cadastrado.\n");
                }
                break;
            case 2:
                status = depositar(ptrUsuario);
                if (status == -1)
                {
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else if(status == 0)
                {
                    printf("\nUsuario nao encontrado.\n");
                }
                else
                {
                    printf("\nDeposito realizado com sucesso!\n");
                }
                break;

            case 3:

                status = sacar(ptrUsuario);
                if (status == 0)
                {
                    printf("\nUsuario nao encontrado.\n");
                }
                else if(status == -1)
                {
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else
                {
                    printf("\nSaque realizado com sucesso!\n");
                }

                break;
            case 4:
                status = comprarCripto(ptrUsuario);
                if (status == 0)
                {
                    printf("Senha incorreta.\n");
                }
                else if(status == -1)
                {
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else
                {
                    printf("\nCompra realizada com sucesso!\n");
                }
                break;
            case 5:
                status = venderCripto(ptrUsuario);

                if (status == 0)
                {
                    printf("Senha incorreta.\n");
                }
                else if(status == -1)
                {
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else if(status == 2)
                {
                    printf("\nSaldo insuficiente para venda.\n");
                }
                else
                {
                    printf("\nVenda realizada com sucesso!\n");
                }
                break;
            case 6:
                status = atualizarCotacao();

                if(status == -1)
                {
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else if(status == 0)
                {
                    printf("\nCriptomoeda nao encontrada.\n");
                }
                else
                {
                    printf("\nCotação atualizada com sucesso!\n");
                }

                break;
            case 7:
                status = consultaExtrato(ptrUsuario);
                if(status == 0)
                {
                    printf("\nExtrato nao encontrado.\n");
                }
                else if(status == -1)
                {
                    printf("\t*Erro ao abrir o arquivo.\n");
                }
                else
                {
                    printf("\nExtrato consultado com sucesso!\n");
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