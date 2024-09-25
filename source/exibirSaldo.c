#include <stdio.h>
#include <string.h>
#include "funcoes.h"

int exibirSaldo(Usuario *ptrUsuario){

    FILE *ptrArquivo;
    Usuario usuario;
    long posicaoArquivo;

    //verifica a posição do CPF no arquivo
    posicaoArquivo = verificaCPF(ptrUsuario);

    //se for 0, não encontrou o CPF
    if (posicaoArquivo >= 0)
    {
        ptrArquivo = fopen("clientes.bin", "rb");
        if (ptrArquivo == NULL)
        {
            perror("Erro ao abrir o arquivo");
            return 0;
        }

        //posiciona o ponteiro no registro do usuário
        fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
        //lê o registro do usuário
        fread(&usuario, sizeof(Usuario), 1, ptrArquivo);

        //exibe os dados do usuário
        printf("CPF: %s\n", usuario.cpf);
        printf("Saldo em Reais: %.2f\n", usuario.saldoReais);
        printf("Saldo em Bitcoin: %.8lf\n", usuario.saldoBTC);
        printf("Saldo em Ethereum: %.8lf\n", usuario.saldoETH);
        printf("Saldo em Ripple: %.8lf\n", usuario.saldoRIPPLE);

        fclose(ptrArquivo);
        return 1; //sucesso ao exibir o saldo
    }
    else
    {
        printf("CPF não cadastrado\n");
        return 0;
    }
}