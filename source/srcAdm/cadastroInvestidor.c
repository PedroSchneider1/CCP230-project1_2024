#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <funcoes.h>

int cadastroInvestidor(Usuario *ptrUsuario){
    FILE *ptrArquivo;
    size_t tamanhoCPF;
    int isNumeric = 1;
    int status = 0;

    char cpf[255];
    do
    {
        printf("\nDigite seu CPF (11 digitos): ");
        fgets(cpf, sizeof(cpf), stdin);

        tamanhoCPF = strlen(cpf);
        // Verifica o comprimento
        if (tamanhoCPF < 12 || tamanhoCPF > 13)
        {
            printf("CPF invalido.\n");
            printf("\t*Tamanho do CPF deve ser de 11 digitos.\n");
        }

        // Verifica se todos os caracteres são dígitos
        isNumeric = 1;
        for (size_t i = 0; i < tamanhoCPF - 1; i++) {
            if (!isdigit(cpf[i])) {
                isNumeric = 0;
                break;
            }
        }

        if (!isNumeric) {
            printf("CPF invalido.\n");
            printf("\t*CPF deve conter apenas numeros.\n");
            continue;
        }

    } while (tamanhoCPF != 12 || !isNumeric); // Continua até ter 11 caracteres + \n

    if (cpf[tamanhoCPF-1] == '\n') { // Remove o \n do fim da string
        cpf[tamanhoCPF-1] = '\0';
        tamanhoCPF--;
    }

    strcpy(ptrUsuario->cpf, cpf);
    status = verificaCPF(ptrUsuario); // 1 = CPF já cadastrado, 0 = CPF não cadastrado

    if (status == 0)
    {
        printf("CPF ja cadastrado.\n\n");
        return 1;
    }
    else if (status == 2)
    {
        printf("Erro ao abrir o arquivo.\n\n");
        return 1;
    }
    else
    {
        printf("Digite sua senha: ");
        fgets(ptrUsuario->senha, sizeof(ptrUsuario->senha), stdin);
        status = cadastro(ptrUsuario);
        if (status == -1)
        {
            printf("Quantidade maxima de clientes atingida.\n\n");
            return 1;
        }
        else
        {
          ptrArquivo = fopen("clientes.bin", "rb+");
          fwrite(ptrUsuario, sizeof(Usuario), 1, ptrArquivo);
          printf("Cadastro realizado com sucesso!\n\n");
          return 0;
        }
    }
}