#include "funcoes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int venderCripto(Usuario *ptrUsuario) {
  FILE *ptrArquivoAtivos, *ptrArquivoCripto, *ptrArquivoUsuarios;
  Ativos ativo;
  Criptomoedas criptomoeda;
  Usuario usuarioTemp;

  const char *tipoOperacao = "Venda";
  float valorVenda = 0.0;
  int foundCripto = 0, foundUsuario = 0, menu, indice = 1;
  long posicaoAtivo, posicaoUsuario;

  // Verifica o CPF e a senha do usuário
  if (verificaCPF(ptrUsuario) < 0) {
    printf("CPF não encontrado.\n");
    return 0;
  }

  limpaBuffer();
  char senha[255];
  printf("Digite sua senha: ");
  fgets(senha, sizeof(senha), stdin);
  if (strcmp(senha, ptrUsuario->senha) != 0) {
    printf("Senha incorreta.\n");
    return 0;
  }

  // Exibe os ativos do usuário
  ptrArquivoAtivos = fopen("ativos.bin", "rb+");
  if (ptrArquivoAtivos == NULL) {
    perror("Erro ao abrir o arquivo de ativos.");
    return -1;
  }

  printf("\nEscolha o ativo que deseja vender:\n");
  rewind(ptrArquivoAtivos);

    // Lista os ativos disponíveis
    while (fread(&ativo, sizeof(Ativos), 1, ptrArquivoAtivos) == 1) {
        if (strcmp(ativo.CPF, ptrUsuario->cpf) == 0 && strcmp(ativo.nomeMoeda, "*") != 0) {
            printf("%d - %s: %.8f\n", indice, ativo.nomeMoeda, ativo.saldoCripto);
            indice++;
        }
    }

    if (indice == 1) { // Não foram encontrados ativos para o CPF
        printf("Você não possui ativos disponíveis para venda.\n");
        fclose(ptrArquivoAtivos);
        return 0;
    }

    // Solicita a escolha do ativo
    do {
        printf("Digite o número do ativo que deseja vender: ");
        scanf("%d", &menu);
        limpaBuffer();
    } while (menu < 1 || menu >= indice);

    rewind(ptrArquivoAtivos);

    int contador = 1; // Índice usado para comparar com a escolha do usuário
    while (fread(&ativo, sizeof(Ativos), 1, ptrArquivoAtivos) == 1) {
        if (strcmp(ativo.CPF, ptrUsuario->cpf) == 0 && strcmp(ativo.nomeMoeda, "*") != 0) {
            if (contador == menu) {
                break; // Ativo encontrado
            }
            contador++;
        }
    }

    // Captura a posição do ativo no arquivo
    posicaoAtivo = ftell(ptrArquivoAtivos) - sizeof(Ativos);
    printf("\nVocê selecionou o ativo: %s com saldo de %.8f.\n",
           ativo.nomeMoeda, ativo.saldoCripto);

  ptrArquivoCripto = fopen("criptomoedas.bin", "rb");
  if (ptrArquivoCripto == NULL) {
    perror("Erro ao abrir o arquivo de criptomoedas.");
    fclose(ptrArquivoAtivos);
    return -1;
  }

  while (fread(&criptomoeda, sizeof(Criptomoedas), 1, ptrArquivoCripto) == 1) {
    if (strcmp(criptomoeda.nomeCripto, ativo.nomeMoeda) == 0) {
      printf("\nTaxa de venda: %.2f%%\nCotação: %.2f\n", criptomoeda.txVenda,
             criptomoeda.cotacao);
      foundCripto = 1;
      break;
    }
  }

  fclose(ptrArquivoCripto);
  if (!foundCripto) {
    printf("Informações da criptomoeda não encontradas.\n");
    fclose(ptrArquivoAtivos);
    return 0;
  }

    // Solicita o valor da venda
    do {
        printf("Digite o valor da venda: ");
        scanf("%f", &valorVenda);

        // O 1e-6 evita erro na comparação por causa do float
        if (valorVenda <= 0 || valorVenda > ativo.saldoCripto + 1e-6) {
            printf("Valor inválido. Verifique seu saldo.\n");
        }
    } while (valorVenda <= 0 || valorVenda > ativo.saldoCripto + 1e-6);


  // Calcula o valor final da venda
  float valorVendaReais = valorVenda * criptomoeda.cotacao;
  float valorFinalVenda =
      valorVendaReais - (valorVendaReais * (criptomoeda.txVenda / 100));

  // Atualiza o saldo do ativo e do usuário
  ativo.saldoCripto -= valorVenda;
  ptrUsuario->saldoReais += valorFinalVenda;

  // Atualiza ou remove o ativo no arquivo
  char nomeMoeda[50];
  strcpy(nomeMoeda, ativo.nomeMoeda);
  
  fseek(ptrArquivoAtivos, posicaoAtivo, SEEK_SET);
  if (ativo.saldoCripto <= 0) {
    strcpy(ativo.nomeMoeda, "*"); // Marca como removido
  }
  
  fwrite(&ativo, sizeof(Ativos), 1, ptrArquivoAtivos);
  fclose(ptrArquivoAtivos);

  // Atualiza o saldo do usuário no arquivo de usuários
  ptrArquivoUsuarios = fopen("clientes.bin", "rb+");
  if (ptrArquivoUsuarios == NULL) {
    perror("Erro ao abrir o arquivo de usuários.");
    return -1;
  }

  while (fread(&usuarioTemp, sizeof(Usuario), 1, ptrArquivoUsuarios) == 1) {
    if (strcmp(usuarioTemp.cpf, ptrUsuario->cpf) == 0) {
      foundUsuario = 1;
      posicaoUsuario = ftell(ptrArquivoUsuarios) - sizeof(Usuario);
      break;
    }
  }

  if (foundUsuario) {
    fseek(ptrArquivoUsuarios, posicaoUsuario, SEEK_SET);
    fwrite(ptrUsuario, sizeof(Usuario), 1, ptrArquivoUsuarios);
  } else {
    printf("Usuário não encontrado no arquivo de usuários.\n");
  }

  fclose(ptrArquivoUsuarios);

  // Grava no extrato
  logExtrato(tipoOperacao, ptrUsuario, valorFinalVenda, criptomoeda.txVenda,
             nomeMoeda);
  ptrUsuario->qttExtrato++;

  printf("Venda realizada com sucesso! Valor recebido: R$%.2f\n",
         valorFinalVenda);

  return 1;
}
