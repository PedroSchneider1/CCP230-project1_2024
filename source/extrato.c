#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

void logExtrato(const char *tipoOperacao, Usuario *ptrUsuario, float valor, float taxaTransacao, const char *nomeMoeda)
{
    FILE *ptrArquivoExtrato;
    time_t data;

    ptrArquivoExtrato = fopen("extrato.bin", "ab");

    if (ptrArquivoExtrato == NULL)
    {
        printf("Erro ao abrir o arquivo de extrato.\n");
        exit(1);
    }
    else
    {
        Extrato extrato;
        //pega a data local
        time(&data);
        extrato.data = data; //armazenando como time_t  (tem que mudar dps)
        strcpy(extrato.CPF, ptrUsuario->cpf);
        strcpy(extrato.tipoOperacao, tipoOperacao);
        extrato.valor = valor;
        extrato.taxaTransacao = taxaTransacao;
        strcpy(extrato.nomeMoeda, nomeMoeda);

        fwrite(&extrato, sizeof(Extrato), 1, ptrArquivoExtrato);
        fclose(ptrArquivoExtrato);
    }
}

int consultaExtrato(Usuario *ptrUsuario)
{

    FILE *ptrArquivoExtrato;
    Extrato extrato;

    ptrArquivoExtrato = fopen("extrato.bin", "rb");

    if (ptrArquivoExtrato == NULL)
    {
        ptrArquivoExtrato = fopen("extrato.bin", "wb");
    }
    else
    {
        int foundExtrato = 0;
        while (fread(&extrato, sizeof(Extrato), 1, ptrArquivoExtrato))
        {
            if (strcmp(extrato.CPF, ptrUsuario->cpf) == 0)
            {
                printf("CPF: %s\n", extrato.CPF);
                printf("Tipo de operacao: %s\n", extrato.tipoOperacao);

                char dataFormatada[20];
                //converte a data para string
                //tm é uma struct que armazena a data e hora, localtime converte o time_t para tm
                struct tm *tm_info = localtime(&extrato.data);
                //strftime converte a struct tm para string
                strftime(dataFormatada, sizeof(dataFormatada), "%d-%m-%Y %H:%M:%S", tm_info);
                printf("Data: %s\n", dataFormatada);
                printf("Valor: R$%.2f\n", extrato.valor);
                printf("Moeda negociada: %s\n", extrato.nomeMoeda);
                printf("Taxa da transacao: %.2f%%\n\n", extrato.taxaTransacao);
                foundExtrato = 1;
            }
        }

        if (foundExtrato == 0)
        {
            fclose(ptrArquivoExtrato);
            return 0;
        }

        fclose(ptrArquivoExtrato);
    }
    return 1;
}

int contaExtrato(Usuario *ptrUsuario){

    FILE *ptrArquivoExtrato;
    Extrato extrato;
    int qtdExtrato = 0;
    ptrArquivoExtrato = fopen("extrato.bin", "rb");

    while(fread(&extrato, sizeof(Extrato), 1, ptrArquivoExtrato) == 1){
        if(strcmp(extrato.CPF, ptrUsuario->cpf) == 0){
            qtdExtrato++;
        }
    }

    fclose(ptrArquivoExtrato);
    return qtdExtrato;

}