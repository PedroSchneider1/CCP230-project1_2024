#ifndef FUNCOES_H
#define FUNCOES_H
#include <time.h>

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



int ExibirMenuVisitante();
void limpaBuffer();
int ExibirMenuCliente();
int cadastro(Usuario *ptrUsuario);

#endif