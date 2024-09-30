# Projeto 1 - Exchange de Criptomoedas
Repositório criado para o projeto "Exchange de criptomoedas" da disciplina "Desenvolvimento de Algoritmos (CCP230)" - 2° Semestre de 2024

## Objetivo
O projeto consiste na criação da sua própria exchange, uma plataforma onde é possível comprar e vender criptomoedas​.

O programa armazena os dados de até 10 usuários, contendo suas informações pessoais (CPF e senha) e seu saldo (reais e criptomoedas).
Além disso, o histórico de transações possui um limite de 100 operações. Todas as informações são armazenadas em arquivos binários.

## Como utilizar o programa
O programa funciona de maneira simples e intuitiva. Ao executar o arquivo, você poderá realizar seu cadastro, entrar com seu login (CPF e senha) ou sair do programa.  
Ao entrar com suas informações, você terá algumas opções de operações para realizar: exibir o saldo em conta, depositar e sacar seu dinheiro, comprar e vender criptomoedas, atualizar a cotação das criptomoedas e consultar o extrato da conta.

O funcionamento detalhado do programa é o seguinte:

### Estruturas
O programa conta com 3 estruturas básicas para armezenar as informações:
- Usuario
  - Armazena informações do usuário, incluindo saldo e dados de login.
- Criptomoedas
  - Contém informações sobre as criptomoedas disponíveis, como nome e cotações.
- Extrato
  - Registra operações financeiras realizadas pelo usuário, incluindo data e valor.

### Funções
``` cpp
    void limpaBuffer(); // Limpa o buffer de entrada.
    int exibirMenuVisitante(); // Exibe o menu para visitantes.
    int exibirMenuCliente(); // Exibe o menu para clientes registrados.
    int cadastro(Usuario *ptrUsuario); // Realiza o cadastro de um novo usuário.
    int verificaCPF(Usuario *ptrUsuario); // Verifica a validade do CPF do usuário.
    int login(Usuario *ptrUsuario); // Realiza o login do usuário.
    int exibirSaldo(Usuario *ptrUsuario); // Exibe o saldo atual do usuário.
    int depositar(Usuario *ptrUsuario); // Permite que o usuário deposite dinheiro.
    int sacar(Usuario *ptrUsuario); // Permite que o usuário saque dinheiro.
    int comprarCripto(Usuario *ptrUsuario); // Permite que o usuário compre criptomoedas.
    int venderCripto(Usuario *ptrUsuario); // Permite que o usuário venda criptomoedas.
    int atualizarCotacao(); // Atualiza as cotações das criptomoedas.
    void logExtrato(const char *tipoOperacao, Usuario *ptrUsuario, float valor, float taxaTransacao, const char *nomeMoeda); // Registra uma operação no extrato do usuário.
    int consultaExtrato(Usuario *ptrUsuario); // Exibe o extrato de operações do usuário.
    int contaExtrato(Usuario *ptrUsuario); // Conta o número de operações registradas no extrato do usuário.
```

#### Funções de sistema
As funções `limpaBuffer(), exibirMenuVisitante() e exibirMenuCliente` são autoindicativas: elas, respectivamente, limpam o buffer de entrada do usuário, exibem o menu incial (visitante) na tela
e exibem o menu de cliente quando logado.

#### Função `cadastro()`

A função cadastro é responsável por registrar um novo usuário em um arquivo binário (clientes.bin).

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém os dados do novo usuário a ser cadastrado.

Funcionamento

    Inicialização:
        Um ponteiro ptrArquivo é declarado para manipular o arquivo.
        Uma variável usuario do tipo Usuario é criada para armazenar os dados lidos do arquivo.
        bytes armazena o tamanho da estrutura Usuario.
        qttClientes é inicializada em 0 para contar quantos clientes já estão cadastrados.

    Abrindo o Arquivo:
        O arquivo clientes.bin é tentado ser aberto em modo leitura e escrita binária (rb+).
        Se o arquivo não existir (ptrArquivo é NULL), ele é criado em modo de escrita binária (wb).

    Contagem de Usuários:
        Um loop lê os dados de usuario do arquivo até que não haja mais dados (fread retorna 1).
        Para cada usuário lido, qttClientes é incrementado.

    Verificação de Limite:
        Se a quantidade de clientes (qttClientes) for igual ou superior a 9, o arquivo é fechado e a função retorna -1, indicando que não é possível cadastrar mais usuários.

    Inicialização de Campos:
        Os saldos em criptomoedas e o saldo em reais do novo usuário (ptrUsuario) são inicializados para 0.
        O campo qttExtrato também é inicializado em 0.

    Gravação no Arquivo:
        Os dados do novo usuário são escritos no arquivo usando fwrite.

    Fechamento do Arquivo:
        O arquivo é fechado após a gravação.

    Retorno:
        A função retorna 0, indicando que o cadastro foi realizado com sucesso.

#### Função `verificaCPF`
A função verificaCPF é responsável por verificar a existência de um usuário no arquivo binário (clientes.bin) com base no CPF fornecido.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém o CPF do usuário a ser verificado.

Funcionamento

    Inicialização:
        Um ponteiro ptrArquivo é declarado para manipular o arquivo.
        bytes armazena o tamanho da estrutura Usuario.
        posicaoArquivo é uma variável para armazenar a posição do registro no arquivo.

    Abrindo o Arquivo:
        O arquivo clientes.bin é tentado ser aberto em modo de leitura binária (rb).
        Se o arquivo não existir (ptrArquivo é NULL), ele é criado em modo de escrita binária (wb). Se a criação falhar, uma mensagem de erro é exibida e a função retorna -1.
        Caso o arquivo seja criado, é fechado, e a função retorna -1, indicando que não há usuários cadastrados.

    Leitura do Arquivo:
        Uma estrutura Usuario chamada usuario é criada para armazenar os dados lidos do arquivo.

    Verificação do CPF:
        Um loop lê os dados de usuario do arquivo até que não haja mais dados (fread retorna 1).
        Para cada usuário lido, a função compara o CPF (strcmp) do usuário armazenado no arquivo com o CPF do usuário fornecido.
        Se os CPFs coincidirem, os dados do usuário encontrado são copiados para a estrutura ptrUsuario.

    Retorno da Posição:
        A função calcula a posição do registro encontrado (posicaoArquivo) e fecha o arquivo.
        Retorna a posição do registro no arquivo.

    Finalização:
        Se nenhum CPF correspondente for encontrado após a leitura de todos os registros, o arquivo é fechado e a função retorna -1, indicando que o CPF não existe no sistema.

#### Função `login`
A função login é responsável por autenticar um usuário com base no CPF e na senha fornecidos.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém o CPF e a senha do usuário a ser autenticado.

Funcionamento

    Inicialização:
        Um ponteiro ptrArquivo é declarado para manipular o arquivo.
        Uma estrutura Usuario chamada usuario é criada para armazenar os dados lidos do arquivo.

    Abrindo o Arquivo:
        O arquivo clientes.bin é tentado ser aberto em modo de leitura binária (rb).
        Se o arquivo não existir (ptrArquivo é NULL), uma mensagem de erro é exibida e a função retorna 0, indicando que não há usuários cadastrados.

    Leitura do Arquivo:
        Um loop lê os dados de usuario do arquivo até que não haja mais dados (fread retorna 1).

    Verificação de Credenciais:
        Para cada usuário lido, a função compara o CPF e a senha (strcmp) do usuário armazenado no arquivo com o CPF e a senha do usuário fornecido.
        Se ambos coincidirem, o arquivo é fechado e a função retorna 1, indicando que a autenticação foi bem-sucedida.

    Finalização:
        Se nenhum par de CPF e senha correspondente for encontrado após a leitura de todos os registros, a função retorna 0, indicando que a autenticação falhou.

#### Função `exibirSaldo`
A função exibirSaldo é responsável por exibir o saldo de um usuário com base no CPF fornecido.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém o CPF do usuário cujo saldo deve ser exibido.

Funcionamento

    Verificação do CPF:
        A função verificaCPF é chamada para encontrar a posição do CPF no arquivo clientes.bin.
        Se posicaoArquivo for maior ou igual a 0, significa que o CPF foi encontrado.

    Abrindo o Arquivo:
        O arquivo clientes.bin é aberto em modo de leitura binária (rb).
        Se a abertura falhar (ptrArquivo é NULL), uma mensagem de erro é exibida e a função retorna 0.

    Posicionamento no Arquivo:
        A função utiliza fseek para mover o ponteiro do arquivo para a posição do registro do usuário encontrado.

    Leitura do Registro:
        Os dados do usuário são lidos do arquivo usando fread, armazenando-os na estrutura usuario.

    Exibição dos Saldo:
        As informações do usuário são exibidas no console, incluindo:
            CPF
            Saldo em reais
            Saldo em Bitcoin
            Saldo em Ethereum
            Saldo em Ripple

    Fechamento do Arquivo:
        O arquivo é fechado após a leitura.

    Retorno:
        A função retorna 1, indicando que a exibição do saldo foi bem-sucedida.

    Tratamento de CPF Não Cadastrado:
        Se posicaoArquivo for menor que 0, uma mensagem informando que o CPF não está cadastrado é exibida e a função retorna 0.

#### Função `depositar`
A função depositar é responsável por permitir que um usuário deposite um valor em sua conta.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém o CPF do usuário que deseja realizar o depósito.

Funcionamento

    Verificação do CPF:
        A função verificaCPF é chamada para encontrar a posição do CPF no arquivo clientes.bin.
        Se posicaoArquivo for maior ou igual a 0, o CPF foi encontrado.

    Abrindo o Arquivo:
        O arquivo clientes.bin é aberto em modo leitura e escrita binária (rb+).
        Se a abertura falhar (ptrArquivo é NULL), uma mensagem de erro é exibida e a função retorna -1.

    Solicitação do Valor do Depósito:
        Um loop é utilizado para solicitar que o usuário insira o valor do depósito.
        O loop continua até que um valor não negativo seja fornecido.

    Posicionamento no Arquivo:
        A função utiliza fseek para mover o ponteiro do arquivo para a posição do registro do usuário encontrado.

    Leitura do Registro:
        Os dados do usuário são lidos do arquivo usando fread, armazenando-os na estrutura usuario.

    Atualização do Saldo:
        O saldo em reais do usuário é atualizado ao adicionar o valor do depósito.

    Sobrescrita do Registro:
        O ponteiro do arquivo é reposicionado para o início do registro do usuário e os dados atualizados são escritos de volta no arquivo usando fwrite.

    Registro do Extrato:
        A função contaExtrato é chamada para verificar a quantidade atual de extratos.
        Se a quantidade de extratos for inferior a 100, a função logExtrato é chamada para registrar a operação de depósito.

    Fechamento do Arquivo:
        O arquivo é fechado após todas as operações.

    Retorno:
        A função retorna 1, indicando que o depósito foi realizado com sucesso.

    Tratamento de CPF Não Cadastrado:
        Se posicaoArquivo for menor que 0, uma mensagem informando que o CPF não está cadastrado é exibida e a função retorna 0.

#### Função `sacar`
A função sacar permite que um usuário retire um valor de sua conta.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém o CPF do usuário que deseja realizar o saque.

Funcionamento

    Verificação do CPF:
        A função verificaCPF é chamada para encontrar a posição do CPF no arquivo clientes.bin.
        Se posicaoArquivo for maior ou igual a 0, significa que o CPF foi encontrado.

    Abrindo o Arquivo:
        O arquivo clientes.bin é aberto em modo leitura e escrita binária (rb+).
        Se a abertura falhar (ptrArquivo é NULL), uma mensagem de erro é exibida e a função retorna -1.

    Posicionamento no Arquivo:
        O ponteiro do arquivo é posicionado para a posição do registro do usuário usando fseek.

    Leitura do Registro:
        Os dados do usuário são lidos do arquivo usando fread, armazenando-os na estrutura usuario.

    Solicitação do Valor do Saque:
        Um loop solicita que o usuário insira o valor do saque.
        O valor só é aceito se não exceder o saldo atual. Se o valor for maior que o saldo, uma mensagem de "Saldo insuficiente" é exibida e o loop continua até que um valor válido seja fornecido.

    Atualização do Saldo:
        O saldo em reais do usuário é atualizado ao subtrair o valor do saque.

    Sobrescrita do Registro:
        O ponteiro do arquivo é reposicionado para o início do registro do usuário e os dados atualizados são escritos de volta no arquivo usando fwrite.

    Registro do Extrato:
        A função contaExtrato é chamada para verificar a quantidade atual de extratos.
        Se a quantidade de extratos for inferior a 100, a função logExtrato é chamada para registrar a operação de saque.

    Fechamento do Arquivo:
        O arquivo é fechado após todas as operações.

    Retorno:
        A função retorna 1, indicando que o saque foi realizado com sucesso.

    Tratamento de CPF Não Cadastrado:
        Se posicaoArquivo for menor que 0, a função retorna 0, indicando que o CPF não está cadastrado.

#### Função `comprarCripto`
A função comprarCripto permite que um usuário compre criptomoedas utilizando seu saldo em reais.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém o CPF e as informações financeiras do usuário que deseja realizar a compra.

Funcionamento

    Verificação do CPF:
        A função verificaCPF é chamada para encontrar a posição do CPF no arquivo clientes.bin.
        Se posicaoArquivo for maior ou igual a 0, significa que o CPF foi encontrado.

    Abrindo o Arquivo:
        O arquivo clientes.bin é aberto em modo leitura e escrita binária (rb+).
        Se a abertura falhar, uma mensagem de erro é exibida e a função retorna -1.

    Leitura do Registro do Usuário:
        O ponteiro do arquivo é posicionado para o registro do usuário usando fseek, e os dados do usuário são lidos.

    Verificação da Senha:
        O usuário é solicitado a inserir sua senha. Se a senha não corresponder à armazenada, a função fecha o arquivo e retorna 0.

    Seleção da Criptomoeda:
        O usuário escolhe entre Bitcoin, Ethereum ou Ripple através de um menu.

    Abertura do Arquivo de Criptomoedas:
        O arquivo criptomoedas.bin é aberto em modo leitura binária (rb).
        Se a abertura falhar, uma mensagem de erro é exibida e a função retorna -1.

    Busca e Exibição da Taxa de Compra:
        A função percorre o arquivo de criptomoedas até encontrar a moeda selecionada, exibindo a taxa de compra correspondente.

    Solicitação do Valor da Compra:
        Um loop solicita que o usuário insira o valor a ser comprado, garantindo que o saldo seja suficiente.
        Se o saldo for insuficiente, uma mensagem de erro é exibida e o loop continua até que um valor válido seja fornecido.

    Cálculo do Valor Final da Compra:
        A taxa de compra é aplicada ao valor fornecido para calcular o valor final que será utilizado para a compra da criptomoeda.

    Atualização do Saldo da Criptomoeda:
        O saldo da criptomoeda correspondente (BTC, ETH ou RIPPLE) do usuário é atualizado com a quantidade adquirida.

    Registro do Extrato:
        A quantidade de extratos é verificada, e a função logExtrato é chamada para registrar a operação de compra, se o limite não for atingido.

    Atualização do Saldo em Reais:
        O saldo em reais do usuário é atualizado, subtraindo o valor da compra.

    Fechamento dos Arquivos:
        Os arquivos são fechados após todas as operações.

    Retorno:
        A função retorna 1, indicando que a compra foi realizada com sucesso.

    Tratamento de CPF Não Cadastrado:
        Se posicaoArquivo for menor que 0, a função informa que o CPF não está cadastrado e retorna -1.

#### Função `venderCripto`
A função venderCripto permite que um usuário venda suas criptomoedas, atualizando seu saldo em reais.

Parâmetros

    Usuario *ptrUsuario: Ponteiro para uma estrutura do tipo Usuario, que contém as informações financeiras e de login do usuário que deseja realizar a venda.

Funcionamento

    Verificação do CPF:
        A função verificaCPF é chamada para localizar o registro do usuário no arquivo clientes.bin.
        Se posicaoArquivo for maior ou igual a 0, o CPF foi encontrado.

    Abertura do Arquivo:
        O arquivo clientes.bin é aberto em modo leitura e escrita binária (rb+).
        Se a abertura falhar, uma mensagem de erro é exibida e a função retorna -1.

    Leitura do Registro do Usuário:
        O ponteiro do arquivo é posicionado no registro do usuário usando fseek, e os dados do usuário são lidos.

    Verificação da Senha:
        O usuário é solicitado a inserir sua senha. Se a senha não corresponder, a função fecha o arquivo e retorna 0.

    Seleção da Criptomoeda para Venda:
        O usuário escolhe entre Bitcoin, Ethereum ou Ripple através de um menu.

    Abertura do Arquivo de Criptomoedas:
        O arquivo criptomoedas.bin é aberto em modo leitura binária (rb).
        Se a abertura falhar, uma mensagem de erro é exibida e a função retorna -1.

    Busca e Exibição da Taxa de Venda:
        A função percorre o arquivo de criptomoedas para encontrar a moeda selecionada, exibindo a taxa de venda correspondente.

    Solicitação do Valor da Venda:
        Um loop solicita que o usuário insira o valor a ser vendido, garantindo que seja um valor positivo.

    Verificação do Saldo de Criptomoedas:
        A função verifica se o usuário possui saldo suficiente da criptomoeda selecionada para realizar a venda.
        Se o saldo for insuficiente, a função fecha os arquivos e retorna 2.

    Cálculo do Valor da Venda em Reais:
        O valor da venda em criptomoedas é convertido para reais usando a cotação atual da criptomoeda.
        A taxa de venda é aplicada para calcular o valor final a ser creditado ao saldo do usuário.

    Atualização do Saldo do Usuário:
        O saldo em reais do usuário é atualizado com o valor final da venda, e a quantidade da criptomoeda vendida é subtraída do saldo correspondente.

    Registro do Extrato:
        A quantidade de extratos é verificada, e a função logExtrato é chamada para registrar a operação de venda, se o limite não for atingido.

    Escrita do Registro Atualizado:
        O ponteiro do arquivo é reposicionado para o registro do usuário e os dados atualizados são escritos de volta.

    Fechamento dos Arquivos:
        Ambos os arquivos são fechados após a conclusão das operações.

    Retorno:
        A função retorna 1, indicando que a venda foi realizada com sucesso.
        Se o CPF não for encontrado, a função retorna 0.

#### Função `atualizarCotacao`
A função atualizarCotacao é responsável por atualizar a cotação de uma criptomoeda específica em um arquivo binário.

Parâmetros

    Nenhum parâmetro é necessário, pois a função trabalha diretamente com o arquivo que contém as criptomoedas.

Funcionamento

    Abertura do Arquivo de Criptomoedas:
        A função tenta abrir criptomoedas.bin em modo leitura e escrita binária (rb+).
        Se a abertura falhar, uma mensagem de erro é exibida e a função retorna -1.

    Seleção da Criptomoeda:
        Um loop é utilizado para solicitar ao usuário que escolha qual criptomoeda deseja atualizar (Bitcoin, Ethereum ou Ripple).
        A entrada do usuário é validada para garantir que a escolha esteja entre 1 e 3.

    Leitura do Registro e Atualização da Cotação:
        A função lê cada registro de criptomoedas até encontrar a correspondente à escolha do usuário.
        Se a criptomoeda for encontrada, a cotação antiga é exibida.

    Geração de Variação Aleatória:
        A função gera um valor aleatório entre -5% e +5% para calcular a nova cotação.
        Essa variação é gerada utilizando a função rand() e srand(time(NULL)) para garantir diferentes resultados a cada execução.

    Cálculo da Nova Cotação:
        A nova cotação é calculada multiplicando a cotação antiga pela variação gerada.
        A nova cotação, a cotação antiga e a porcentagem de variação são exibidas.

    Atualização do Registro:
        O ponteiro do arquivo é posicionado de volta ao início do registro da criptomoeda usando fseek.
        O registro atualizado é sobrescrito no arquivo.

    Fechamento do Arquivo:
        O arquivo é fechado após a atualização ou se a criptomoeda não for encontrada.

    Retorno:
        Se a criptomoeda foi encontrada e atualizada, a função retorna 1.
        Se não for encontrada, a função retorna 0.

#### Funções `logExtrato, consultaExtrato e contaExtrato`
`logExtrato`

    Registra os detalhes de uma transação em um arquivo binário (extrato.bin).
    Parâmetros:
        tipoOperacao: Tipo de operação (por exemplo, "Compra", "Venda").
        ptrUsuario: Ponteiro para a estrutura do usuário.
        valor: Valor da transação.
        taxaTransacao: Percentual da taxa da transação.
        nomeMoeda: Nome da criptomoeda envolvida.
    Funcionalidade:
        Abre o arquivo em modo de acréscimo.
        Armazena o horário atual e os detalhes da transação em uma estrutura Extrato.
        Escreve a estrutura no arquivo e o fecha.
    Tratamento de Erros: Sai do programa se não conseguir abrir o arquivo.

`consultaExtrato`

    Recupera e exibe o histórico de transações do usuário.
    Parâmetros: Ponteiro para a estrutura do usuário.
    Funcionalidade:
        Tenta abrir o arquivo em modo de leitura; cria o arquivo se não existir.
        Lê os registros, imprimindo detalhes das transações que correspondem ao CPF do usuário.
        Converte time_t para uma string de data formatada para exibição.
    Retorno: Retorna 0 se nenhuma transação for encontrada, caso contrário, retorna 1.

`contaExtrato`

    Conta o número de transações para um usuário específico.
    Parâmetros: Ponteiro para a estrutura do usuário.
    Funcionalidade:
        Abre o arquivo em modo de leitura/escrita.
        Itera pelos registros, contando quantos pertencem ao usuário com base no CPF.
    Retorno: Retorna a contagem de transações.

## Compilação e execução
Para executar o programa, é necessário baixar os arquivos fonte e compilar o arquivo executável.  
Para isso, clone o repositório em um diretório local (utilize a forma que desejar, o exemplo abaixo clona a partir do link HTTPS).

```
git clone https://github.com/PedroSchneider1/CCP230-project1_2024.git
```

Em seguida, dirija-se a pasta principal do repositório e utilize o Makefile para compilação.

```
cd .\CCP230-project1_2024\
make
```

Com isso, o arquivo "exchange.exe" será criado na pasta principal do projeto. Para utilizá-lo, apenas abra o executável e faça suas operações!  
> Obs.: O programa funciona completamente através do terminal do seu sistema operacional.

## Autores
Esse é o projeto #1 da disciplina CCP230 (Desenvolvimento de Algoritmos) do curso de Ciência da Computação do Centro Universitário FEI, criado pelos alunos:
- [@Pedro Schneider](https://github.com/PedroSchneider1) (RA 24.124.072-0)
- [@Gabriel Santana Dias](https://github.com/GabrielSantana013) (RA 24.124.071-2)
