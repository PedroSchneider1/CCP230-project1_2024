#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoes.h>

int excluirInvestidor(Usuario *ptrUsuario){
    FILE *ptrArquivo;
    size_t tamanhoCPF;
    size_t bytes = sizeof(Usuario);
    
    ptrArquivo = fopen("clientes.bin", "rb+");
    if (ptrArquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    printf("Digite o CPF do investidor que deseja excluir: ");
    fgets(ptrUsuario->cpf, sizeof(ptrUsuario->cpf), stdin);
    tamanhoCPF = strlen(ptrUsuario->cpf);
    if (ptrUsuario->cpf[tamanhoCPF - 1] == '\n') {
        ptrUsuario->cpf[tamanhoCPF - 1] = '\0';
    }

    long posicaoArquivo = verificaCPF(ptrUsuario);
    if (posicaoArquivo < 0) { // Ajuste para tratar o caso "não encontrado"
        printf("CPF nao encontrado.\n");
        fclose(ptrArquivo);
        return 1;
    }

    fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
    ptrUsuario->cpf[0] = '*';
    if (fwrite(ptrUsuario, bytes, 1, ptrArquivo)) {
        printf("Investidor excluido com sucesso!\n\n");
    }
    fclose(ptrArquivo);
    return 0;

}