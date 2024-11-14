#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int comprarCripto(Usuario *ptrUsuario)
{
    FILE *ptrArquivo, *ptrArquivoCripto, *ptrArquivoAtivos;
    Usuario usuario;
    Criptomoedas criptomoedas;
    Ativos ativo;

    const char *tipoOperacao = "Compra";

    int bytes = sizeof(Usuario);
    int bytesCripto = sizeof(Criptomoedas);
    int bytesAtivos = sizeof(Ativos);
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
        while (fread(&criptomoedas, bytesCripto, 1, ptrArquivoCripto))
        {
            printf("%d - %s\n", indice, criptomoedas.nomeCripto);
            indice++;
        }

        // Solicita a escolha da criptomoeda
        do
        {
            printf("Digite o numero da criptomoeda: ");
            scanf("%d", &menu);
        } while (menu < 1 || menu >= indice);

        // Procure e exibe a taxa da criptomoeda escolhida
        fseek(ptrArquivoCripto, 0, SEEK_SET);
        for (int i = 0; i < menu; i++)
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

        ptrArquivoAtivos = fopen("ativos.bin", "rb+");
        if (ptrArquivoAtivos == NULL)
        {
            ptrArquivoAtivos = fopen("ativos.bin", "ab+");
            if (ptrArquivoAtivos == NULL)
            {
                perror("Erro ao abrir o arquivo.");
                return -1;
            }
        }

        // Inicializa a posição e o indicador de existência do ativo
        long posicaoArquivoAtivos = 0;
        int encontrado = 0;

        // Procura o ativo correspondente do usuário no arquivo de ativos
        while (fread(&ativo, bytesAtivos, 1, ptrArquivoAtivos))
        {
            if (strcmp(ativo.CPF, usuario.cpf) == 0 && strcmp(ativo.nomeMoeda, criptomoedas.nomeCripto) == 0)
            {
                posicaoArquivoAtivos = ftell(ptrArquivoAtivos) - bytesAtivos;
                printf("Saldo anterior: %.2f\n", ativo.saldoCripto); // Para debug
                encontrado = 1;
                break;
            }
        }

        // Se o ativo não foi encontrado, inicializa um novo ativo para o usuário
        if (!encontrado)
        {
            strcpy(ativo.CPF, usuario.cpf);
            strcpy(ativo.nomeMoeda, criptomoedas.nomeCripto);
            ativo.saldoCripto = 0;
        }

        ativo.saldoCripto += valorFinalCompra / criptomoedas.cotacao;

        if (encontrado)
        {
            // Atualiza o ativo na posição onde foi encontrado
            fseek(ptrArquivoAtivos, posicaoArquivoAtivos, SEEK_SET);
        }
        else
        {
            // Posiciona o ponteiro no final do arquivo para adicionar o novo ativo
            fseek(ptrArquivoAtivos, 0, SEEK_END);
        }

        fwrite(&ativo, bytesAtivos, 1, ptrArquivoAtivos);
        fclose(ptrArquivoAtivos);

        usuario.qttExtrato = contaExtrato(ptrUsuario);

        if (usuario.qttExtrato >= 99)
        {
            printf("Limite de extratos (100) atingido!\n");
        }
        else
        {
            logExtrato(tipoOperacao, ptrUsuario, valorCompra, (taxa * 100), ativo.nomeMoeda);
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
