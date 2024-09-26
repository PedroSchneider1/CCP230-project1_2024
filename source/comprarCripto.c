#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int comprarCripto(Usuario *ptrUsuario)
{
    FILE *ptrArquivo, *ptrArquivoCripto;
    Usuario usuario;
    Criptomoedas criptomoedas;

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
            printf("Senha incorreta\n");
            return -1;
        }

        // Seleciona a criptomoeda para compra
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

        // Solicita o valor da compra
        do
        {
            printf("Digite o valor da compra: ");
            scanf("%f", &valorCompra);
            if (valorCompra > usuario.saldoReais)
            {
                printf("Saldo insuficiente\n");
                valorCompra = -1;
            }
        } while (valorCompra < 0);

        // Processa a compra de acordo com a criptomoeda escolhida
        int foundCripto = 0;
        while (fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto) == 1)
        {
            if ((menu == 1 && strcmp(criptomoedas.nomeCripto, "Bitcoin") == 0) ||
                (menu == 2 && strcmp(criptomoedas.nomeCripto, "Ethereum") == 0) ||
                (menu == 3 && strcmp(criptomoedas.nomeCripto, "Ripple") == 0))
            {

                // Atualiza o saldo da criptomoeda correspondente
                if (menu == 1)
                    usuario.saldoBTC += valorCompra / criptomoedas.cotacao;
                else if (menu == 2)
                    usuario.saldoETH += valorCompra / criptomoedas.cotacao;
                else if (menu == 3)
                    usuario.saldoRIPPLE += valorCompra / criptomoedas.cotacao;

                // Atualiza o saldo em reais
                usuario.saldoReais -= valorCompra;
                foundCripto = 1;
                break;
            }
        }

        fclose(ptrArquivoCripto);

        if (foundCripto)
        {
            // Posiciona o ponteiro no registro do usuário e sobrescreve o registro
            fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
            fwrite(&usuario, bytes, 1, ptrArquivo);
            fclose(ptrArquivo);
            return 1; // Sucesso
        }
        else
        {
            printf("Criptomoeda não encontrada.\n");
        }

        fclose(ptrArquivo);
    }
    else
    {
        printf("CPF não cadastrado\n");
    }

    return -1;
}
