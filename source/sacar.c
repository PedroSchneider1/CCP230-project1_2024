#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int sacar(Usuario *ptrUsuario)
{
    FILE *ptrArquivo;
    Usuario usuario;
    float valorSaque = 0.0;
    long posicaoArquivo;
    int bytes = sizeof(Usuario);
    const char *tipoOperacao = "Saque";

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

        // posiciona o ponteiro no registro do usuário
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
        // lê o registro do usuário
        fread(&usuario, bytes, 1, ptrArquivo);

        do
        {
            printf("Digite o valor do saque: ");
            scanf("%f", &valorSaque);
            if (valorSaque > usuario.saldoReais)
            {
                printf("Saldo insuficiente\n");
                //volta pro loop
                valorSaque = -1;
            }
        } while (valorSaque < 0);

        // atualiza o saldo do usuário

        usuario.saldoReais -= valorSaque;

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
            logExtrato(tipoOperacao, ptrUsuario, valorSaque, 0, "Real");
        }
        fclose(ptrArquivo);
        return 1; // sucesso ao exibir o saldo

    }
    return 0;
}