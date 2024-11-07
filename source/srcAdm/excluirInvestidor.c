#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoes.h>

int excluirInvestidor(Usuario *ptrUsuario){
    FILE *ptrArquivo;
    size_t bytes = sizeof(Usuario);
    
    ptrArquivo = fopen("clientes.bin", "rb+");
    if (ptrArquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    printf("Digite o CPF do investidor que deseja excluir: ");
    fgets(ptrUsuario->cpf, 12, stdin);
    ptrUsuario->cpf[strcspn(ptrUsuario->cpf, "\n")] = 0;

    long posicaoArquivo = verificaCPF(ptrUsuario);
    if (posicaoArquivo != 0)
    {
        printf("CPF não encontrado.\n");
        fclose(ptrArquivo);
        return 1;
    }

    fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
    fread(ptrUsuario, bytes, 1, ptrArquivo);
    fseek(ptrArquivo, posicaoArquivo, SEEK_SET);
    ptrUsuario->cpf[0] = '*';
    if(fwrite(ptrUsuario, bytes, 1, ptrArquivo))
        printf("Investidor excluido com sucesso!\n\n");
    fclose(ptrArquivo);
    return 0;
}