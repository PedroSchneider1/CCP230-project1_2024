#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoes.h>

int cadastroCripto(){
    FILE *ptrArquivo;
    Criptomoedas criptomoedas, registradas;

    ptrArquivo = fopen("criptomoedas.bin", "rb+");

    if (ptrArquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    printf("Digite o nome da criptomoeda: ");
    fgets(criptomoedas.nomeCripto, 255, stdin);
    criptomoedas.nomeCripto[strcspn(criptomoedas.nomeCripto, "\n")] = 0;

    while (fread(&registradas, sizeof(Criptomoedas), 1, ptrArquivo))
    {
        if (strcmp(criptomoedas.nomeCripto, registradas.nomeCripto) == 0)
        {
            printf("Criptomoeda ja cadastrada, cadastre uma moeda com nome diferente.\n");
            return 1;
        }
    }

    printf("Digite a cotacao da criptomoeda: ");
    scanf("%f", &criptomoedas.cotacao);

    printf("Digite a taxa de compra da criptomoeda: ");
    scanf("%f", &criptomoedas.txCompra);

    printf("Digite a taxa de venda da criptomoeda: ");
    scanf("%f", &criptomoedas.txVenda);

    printf("\nConfirme os dados:\n");
    printf("\tNome: %s\n", criptomoedas.nomeCripto);
    printf("\tCotacao: %f\n", criptomoedas.cotacao);
    printf("\tTaxa de Compra: %f\n", criptomoedas.txCompra);
    printf("\tTaxa de Venda: %f\n", criptomoedas.txVenda);
    printf("Deseja confirmar o cadastro? (s/n): ");
    limpaBuffer();
    char confirmacao = getchar();
    if (confirmacao != 's' && confirmacao != 'S')
    {
        printf("Cadastro cancelado.\n\n");
        return 0;
    }

    fwrite(&criptomoedas, sizeof(Criptomoedas), 1, ptrArquivo);
    printf("Criptomoeda cadastrada com sucesso!\n\n");

    fclose(ptrArquivo);

    return 0;
}