#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int venderCripto(Usuario *ptrUsuario)
{
    FILE *ptrArquivo, *ptrArquivoCripto;
    Usuario usuario;
    Criptomoedas criptomoedas;

    int bytes = sizeof(Usuario);
    int bytesCripto = sizeof(Criptomoedas);
    float valorVenda = 0.0;
    int menu;
    long posicaoArquivo;
    char senha[255];

    posicaoArquivo = verificaCPF(ptrUsuario);

    // Verifica se o CPF foi encontrado
    if (posicaoArquivo >= 0)
    {
        ptrArquivo = fopen("clientes.bin", "rb+");
        if (ptrArquivo == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return -1;
        }

        // Posiciona o ponteiro no registro do usuário e lê o registro
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
        fread(&usuario, bytes, 1, ptrArquivo);

        // Verifica a senha do usuário
        limpaBuffer();
        printf("Digite sua senha: ");
        fgets(senha, sizeof(senha), stdin);

        if (strcmp(senha, usuario.senha) != 0)
        {
            fclose(ptrArquivo);
            return 0;
        }

        // Seleciona a criptomoeda para venda
        do
        {
            printf("Escolha sua criptomoeda: \n");
            printf("1 - Bitcoin\n");
            printf("2 - Ethereum\n");
            printf("3 - Ripple\n");
            scanf("%d", &menu);

        } while (menu < 1 || menu > 3);

        // Abre o arquivo de criptomoedas
        ptrArquivoCripto = fopen("criptomoedas.bin", "rb");
        if (ptrArquivoCripto == NULL)
        {
            perror("Erro ao abrir o arquivo de criptomoedas");
            fclose(ptrArquivo);
            return -1;
        }

        int foundCripto = 0;
        while (fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto) == 1)
        {
            if ((menu == 1 && strcmp(criptomoedas.nomeCripto, "Bitcoin") == 0) ||
                (menu == 2 && strcmp(criptomoedas.nomeCripto, "Ethereum") == 0) ||
                (menu == 3 && strcmp(criptomoedas.nomeCripto, "Ripple") == 0))
            {
                foundCripto = 1;

                // Exibe a taxa de venda
                printf("O valor de taxa de venda é de %.2f%% para a moeda %s\n", criptomoedas.txVenda, criptomoedas.nomeCripto);
                break;
            }
        }

        if (!foundCripto)
        {
            printf("Criptomoeda não encontrada\n");
            fclose(ptrArquivo);
            fclose(ptrArquivoCripto);
            return -1;
        }

        // Solicita o valor da venda
        do
        {
            printf("Digite o valor da venda: ");
            scanf("%f", &valorVenda);
            if (valorVenda <= 0)
            {
                printf("Valor de venda inválido.\n");
            }
        } while (valorVenda <= 0);

        // Verifica se o saldo da criptomoeda é suficiente para realizar a venda
        if ((menu == 1 && valorVenda > usuario.saldoBTC) ||
            (menu == 2 && valorVenda > usuario.saldoETH) ||
            (menu == 3 && valorVenda > usuario.saldoRIPPLE))
        {
            printf("Saldo insuficiente para venda.\n");
            fclose(ptrArquivo);
            fclose(ptrArquivoCripto);
            return 2;
        }

        // Aplica a taxa de venda e calcula o valor final
        float taxa = criptomoedas.txVenda / 100.0;
        float valorFinalVenda = valorVenda * criptomoedas.cotacao * (1 - taxa);

        // Atualiza o saldo do usuário
        if (menu == 1)
        {
            usuario.saldoReais += valorFinalVenda;
            usuario.saldoBTC -= valorVenda;
        }
        else if (menu == 2)
        {
            usuario.saldoReais += valorFinalVenda;
            usuario.saldoETH -= valorVenda;
        }
        else if (menu == 3)
        {
            usuario.saldoReais += valorFinalVenda;
            usuario.saldoRIPPLE -= valorVenda;
        }

        // Posiciona novamente no início do registro
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);

        // Sobrescreve o registro
        fwrite(&usuario, bytes, 1, ptrArquivo);

        // Fecha os arquivos abertos
        fclose(ptrArquivo);
        fclose(ptrArquivoCripto);

        return 1; // Sucesso
    }
    else
    {
        return 0;
    }
}