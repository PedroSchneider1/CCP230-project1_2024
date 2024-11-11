#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int comprarCripto(Usuario *ptrUsuario)
{
    FILE *ptrArquivo, *ptrArquivoCripto;
    Usuario usuario;
    Criptomoedas criptomoedas;

    const char *tipoOperacao = "Compra";

    int bytes = sizeof(Usuario);
    int bytesCripto = sizeof(Criptomoedas);
    float valorCompra = 0.0;
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
            perror("Erro ao abrir o arquivo.");
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

        // Seleciona a criptomoeda para compra
        ptrArquivoCripto = fopen("criptomoedas.bin", "r+");
        int indice = 1;
        
        printf("Escolha sua criptomoeda: \n");
        while(fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto))
        {
            printf("%d - %s\n", indice, criptomoedas.nomeCripto);
            indice++;
        }

        // Solicita a escolha da criptomoeda
        do
        {
            scanf("%d", &menu);
            printf("Escolha invalida, tente novamente");
        } while (menu < 1 || menu >= indice);

        // Procure e exibe a taxa da criptomoeda escolhida
        fseek(ptrArquivoCripto, 0, SEEK_SET);
        for(int i = 0; i < menu; i++)
        {
            fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto);
        }

        printf("\nO valor de taxa de compra e de %.2f%% para a moeda %s\n", criptomoedas.txCompra, criptomoedas.nomeCripto);
        exibirSaldo(ptrUsuario);

        // Solicita o valor da compra
        do
        {
            printf("Digite o valor da compra: ");
            scanf("%f", &valorCompra);
            if (valorCompra > usuario.saldoReais)
            {
                printf("Saldo insuficiente.\n");
                valorCompra = -1;
            }
        } while (valorCompra < 0);

        // Aplica a taxa de compra
        float taxa = criptomoedas.txCompra / 100.0;
        float valorFinalCompra = valorCompra - (valorCompra * taxa);

        // Atualiza o saldo da criptomoeda correspondente
        if (menu == 1)
        {
            usuario.saldoBTC += valorFinalCompra / criptomoedas.cotacao;
            usuario.qttExtrato++;
        }
        else if (menu == 2)
        {
            usuario.saldoETH += valorFinalCompra / criptomoedas.cotacao;
        }
        else if (menu == 3)
        {
            usuario.saldoRIPPLE += valorFinalCompra / criptomoedas.cotacao;
        }

        usuario.qttExtrato = contaExtrato(ptrUsuario);

        if (usuario.qttExtrato >= 99)
        {
            printf("Limite de extratos (100) atingido!\n");
        }
        else
        {
            if (menu == 1)
            {
                strcpy(criptomoedas.nomeCripto, "Bitcoin");
            }
            else if (menu == 2)
            {
                strcpy(criptomoedas.nomeCripto, "Ethereum");
            }
            else if (menu == 3)
            {
                strcpy(criptomoedas.nomeCripto, "Ripple");
            }

            logExtrato(tipoOperacao, ptrUsuario, valorCompra, (taxa * 100), criptomoedas.nomeCripto);
        }

        // Atualiza o saldo em reais
        usuario.saldoReais -= valorCompra;

        fclose(ptrArquivoCripto);

        // Posiciona o ponteiro no registro do usuário e sobrescreve o registro
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
        fwrite(&usuario, bytes, 1, ptrArquivo);
        fclose(ptrArquivo);

        return 1; // Sucesso
    }
    else
    {
        printf("CPF nao cadastrado.\n");
    }

    return -1;
}
