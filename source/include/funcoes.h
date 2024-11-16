#ifndef FUNCOES_H
#define FUNCOES_H
#include <time.h>

typedef struct
{
    int qttExtrato;
    char cpf[12];
    char senha[255];
    float saldoReais;

}Usuario;

typedef struct{

    char nomeCripto[255];
    float cotacao;
    float txVenda;
    float txCompra;

}Criptomoedas;

typedef struct{

    char nomeMoeda[255];
    char CPF[12];
    char tipoOperacao[255];
    time_t data;
    float valor;
    float taxaTransacao;
}Extrato;

typedef struct{

    char CPF[12];
    char nomeMoeda[255];
    float saldoCripto;

}Ativos;


//Funcoes Padrão
void limpaBuffer();
int atualizarCotacao();


//Funções de Investidor:

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
void logExtrato(const char *tipoOperacao, Usuario *ptrUsuario, float valor, float taxaTransacao, char *nomeMoeda);
int consultaExtrato(Usuario *ptrUsuario);
int contaExtrato(Usuario *ptrUsuario);


//============================================================================================================================//

//Funções de ADM:

int exibirMenuADM();
int cadastroInvestidor(Usuario *ptrUsuario);
int excluirInvestidor(Usuario *ptrUsuario);
int cadastroCripto();
int excluirCripto();

#endif