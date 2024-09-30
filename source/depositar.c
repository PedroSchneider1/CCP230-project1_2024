#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int depositar(Usuario *ptrUsuario)
{
    FILE *ptrArquivo;
    Usuario usuario;
    int bytes = sizeof(Usuario);
    float deposito = 0.0;
    long posicaoArquivo;
    const char *tipoOperacao = "Deposito";

    posicaoArquivo = verificaCPF(ptrUsuario);

    // se for 0, não encontrou o CPF
    if (posicaoArquivo >= 0)
    {
        ptrArquivo = fopen("clientes.bin", "rb+");
        if (ptrArquivo == NULL)
        {
            perror("Erro ao abrir o arquivo.");
            return -1;
        }

        // solicita o valor do depósito
        do
        {
            printf("Digite o valor do deposito: ");
            scanf("%f", &deposito);
        } while (deposito < 0);

        // posiciona o ponteiro no registro do usuário
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);

        // lê o registro do usuário
        if (fread(&usuario, bytes, 1, ptrArquivo) != 1)
        {
            perror("Erro ao ler o arquivo.\n");
            return -1;
        }

        // atualiza o saldo do usuário
        usuario.saldoReais += deposito;

        // posiciona novamente no inicio do registro
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);

        // sobrescreve o registro
        fwrite(&usuario, bytes, 1, ptrArquivo);

        usuario.qttExtrato = contaExtrato(ptrUsuario);
        if (usuario.qttExtrato >= 99)
        {
            printf("Limite de extratos (100) atingido!\n");
        }
        else
        {
            logExtrato(tipoOperacao, ptrUsuario, deposito, 0, "Real");
        }

        fclose(ptrArquivo);
        return 1; // sucesso ao exibir o saldo
    }
    else
    {
        printf("CPF nao cadastrado.\n");
        return 0;
    }

    return 0;
}