#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <funcoes.h>

int cadastroCripto(){
    FILE *ptrArquivo;
    Criptomoedas criptomoedas;

    ptrArquivo = fopen("criptomoedas.bin", "ab");

    if (ptrArquivo == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }
    
    printf("Digite o nome da criptomoeda: ");
    fgets(criptomoedas.nomeCripto, 255, stdin);
    criptomoedas.nomeCripto[strcspn(criptomoedas.nomeCripto, "\n")] = 0;

    printf("Digite a cotacao da criptomoeda: ");
    scanf("%f", &criptomoedas.cotacao);

    printf("Digite a taxa de compra da criptomoeda: ");
    scanf("%f", &criptomoedas.txCompra);

    printf("Digite a taxa de venda da criptomoeda: ");
    scanf("%f", &criptomoedas.txVenda);

    fwrite(&criptomoedas, sizeof(Criptomoedas), 1, ptrArquivo);

    fclose(ptrArquivo);

    return 0;
}