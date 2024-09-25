#ifndef FUNCOES_H
#define FUNCOES_H
#include <time.h>

typedef struct
{
    char cpf[12];
    char senha[255];
    float saldoReais;
    double saldoBTC;
    double saldoETH;
    double saldoRIPPLE;

}Usuario;

typedef struct{

    char nomeCripto[255];
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

void limpaBuffer();
int exibirMenuVisitante();
int exibirMenuCliente();
int cadastro(Usuario *ptrUsuario);
int verificaCPF(Usuario *ptrUsuario);
int login(Usuario *ptrUsuario);
int exibirSaldo(Usuario *ptrUsuario);
int depositar(Usuario *ptrUsuario);
int sacar(Usuario *ptrUsuario);

#endif