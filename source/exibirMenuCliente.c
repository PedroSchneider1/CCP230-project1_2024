#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int exibirMenuCliente(){

    int menu;
    while(1)
    {
        printf("Login Realizado com Sucesso!\n");
        //Consultar extrato de operações da carteira de investimentos​: salvar em arquivo texto os dados 
        //do usuário e todas as informações de transações (data, valores e taxas)
        printf("1 - Exibir Saldo\n"); 
        //Depositar reais na carteira de investimento​: usuário deve informar apenas os valores
        printf("2 - Depositar\n");
        //Sacar reais da carteira de investimento​: usuário deve informar o valor do saque e a senha deve ser validada antes de realizar o saque
        printf("3 - Sacar\n");
        //Comprar criptomoedas: usuário deve informar valor da compra e senha para validação. caso os dados estiverem
        //corretos e a compra for possível, exibir as informações da compra (incluindo a taxa cobrada) e pedir a confirmação do usuário
        printf("4 - Comprar Criptomoedas\n");
        //Vender criptomoedas: caso os dados estiverem corretos, exibir as informações da venda (incluindo a taxa cobrada) e pedir a confirmação do usuário
        printf("5 - Vender Criptomoedas\n");
        //Atualizar cotação das criptomoedas: usar valores aleatórios pra gerar mudanças de no máximo 5% e mínimo -5% do valor atual
        printf("6 - Atualizar Cotacoes\n");

        printf("7 - Sair\n");

        scanf("%d", &menu);
        switch(menu)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                exit(0);    
        }
        limpaBuffer();   
    }
}