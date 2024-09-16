#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char cpf[12];
    char senha[255];
    float saldoRs;
    double saldoBTC;
    double saldoETH;
    double saldoRIPPLE;

}Usuario;

typedef struct{

    double BTC;
    float txCompraBTC;
    float txVendaBTC;
    double ETH;
    float txCompraETH;
    float txVendaEth;
    double RIPPLE;
    float txCompraRIPPLE;
    float txVendaRIPPLE;

}Criptomoedas;


int main(){



    return 0;
}