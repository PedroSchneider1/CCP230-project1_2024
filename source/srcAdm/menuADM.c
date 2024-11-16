/*Efetuar login​ usando CPF e senha: o menu principal deve aparecer apenas se estas informações estiverem corretas;
Cadastro de novo investidor: o usuário deve informar nome, CPF e senha do novo investidor;
Excluir investidor: o usuário deve informar o CPF do investidor. O programa deve exibir os dados encontrados para o CPF e pedir a confirmação para realizar a exclusão;
Cadastro de criptomoeda: devem ser informados nome, cotação inicial, taxa de compra e taxa de venda;
Excluir criptomoeda: usuário deve informar o nome da criptomoeda. O programa deve exibir os dados da moeda e pedir a confirmação da exclusão;
Consultar saldo de um investidor: deve ser informado o CPF do investidor e o saldo deve ser exibido na tela
Consultar extrado de um investidor: usuário informa o CPF do investidor e o extrado é exibido na tela
Atualizar cotação de criptomoedas: a função de atualização deve usar a mesma função do programa do investidor.*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int exibirMenuADM() {
    int menu;
    do {
        printf("Bem-vindo, administrador!\n");
        printf("Como deseja prosseguir?\n");
        printf("1 - Cadastrar investidor\n");
        printf("2 - Excluir investidor\n");
        printf("3 - Cadastrar criptomoedas\n");
        printf("4 - Excluir criptomoedas\n");
        printf("5 - Consultar saldo de um investidor\n");
        printf("6 - Consultar extrato de um investidor\n");
        printf("7 - Atualizar cotacao de criptomoedas\n");
        printf("8 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &menu) != 1 || menu < 1 || menu > 8) {
            // Limpa o buffer caso o scanf não tenha sido bem sucedido
            while (getchar() != '\n');
            printf("Opção inválida. Tente novamente.\n\n");
            continue;
        }
        
    } while (menu < 1 || menu > 8);
    
    return menu;
}