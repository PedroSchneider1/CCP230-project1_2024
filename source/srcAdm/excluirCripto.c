#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

int excluirCripto() {

    FILE *ptrArquivo;
    size_t bytes = sizeof(Criptomoedas);
    ptrArquivo = fopen("criptomoedas.bin", "rb+");

    if(ptrArquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    Criptomoedas criptomoeda;
    int i = 1;
    int menu;
    int ativoEncontrado = 0;

    
    printf("Criptomoedas:\n");
    while(fread(&criptomoeda, bytes, 1, ptrArquivo) == 1) {
        if(criptomoeda.nomeCripto[0] != '*') { // Ignora criptomoedas excluídas
            printf("%d - %s\n", i, criptomoeda.nomeCripto);
            i++;
            ativoEncontrado = 1;
        }
    }

    if (!ativoEncontrado) {
        printf("Nenhuma criptomoeda disponível para exclusão.\n");
        fclose(ptrArquivo);
        return 1;
    }
    do {
        printf("\nDigite o número do ativo que deseja excluir: ");
        scanf("%d", &menu);
        limpaBuffer();
    } while (menu < 1 || menu >= i);

    // Reabre o arquivo para edição
    fseek(ptrArquivo, 0, SEEK_SET);

    // Encontra e exclui a criptomoeda
    i = 1; // Reinicia o contador para encontrar o índice correto
    while(fread(&criptomoeda, bytes, 1, ptrArquivo) == 1) {
        if (i == menu && criptomoeda.nomeCripto[0] != '*') {
            printf("Você selecionou a criptomoeda: %s\n", criptomoeda.nomeCripto);
            strcpy(criptomoeda.nomeCripto, "*"); // Marca a moeda como excluída

            fseek(ptrArquivo, -bytes, SEEK_CUR); // Move o ponteiro para a posição correta
            if (fwrite(&criptomoeda, bytes, 1, ptrArquivo) == 1) {
                printf("Criptomoeda excluída com sucesso!\n");
            } else {
                printf("Erro ao excluir a criptomoeda.\n");
            }
            break;
        }
        i++;
    }

    fclose(ptrArquivo);
    return 0;
}
