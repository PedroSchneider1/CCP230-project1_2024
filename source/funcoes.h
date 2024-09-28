#ifndef FUNCOES_H
#define FUNCOES_H
#include <time.h>

typedef struct
{
    int qttExtrato;
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

    char CPF[12];
    char tipoOperacao[255];
    time_t data;
    float valor;
    float taxaTransacao;
}Extrato;

void limpaBuffer();
int exibirMenuVisitante();
int exibirMenuCliente();
int cadastro(Usuario *ptrUsuario);
int verificaCPF(Usuario *ptrUsuario);
int login(Usuario *ptrUsuario);
int exibirSaldo(Usuario *ptrUsuario);
int depositar(Usuario *ptrUsuario);
int sacar(Usuario *ptrUsuario);
int comprarCripto(Usuario *ptrUsuario);
int venderCripto(Usuario *ptrUsuario);
int atualizarCotacao();
void logExtrato(const char *tipoOperacao, Usuario *ptrUsuario, float valor, float taxaTransacao, const char *nomeCripto);
int consultaExtrato(Usuario *ptrUsuario);

#endif