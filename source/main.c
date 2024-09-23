#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

typedef struct
{
    char cpf[11];
    char senha[255];
    float saldoReais;
    double saldoBTC;
    double saldoETH;
    double saldoRIPPLE;

}Usuario;

typedef struct{

    float cotacao;
    float txVenda;
    float txCompra;

}Criptomoedas;

typedef struct{

    int qttExtratos;
    float saldoReais;
    double saldoBTC;
    double saldoETH;
    double saldoRIPPLE;
    time_t Data;

}Extratos;


int main(){

    int retorno = ExibirMenuVisitante();
    printf("%d", retorno);

    return 0;
}