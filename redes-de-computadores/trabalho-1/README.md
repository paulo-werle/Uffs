# Programação Socket e Roteamento
Desenvolvido por **Paulo E. R. Werle** 👋

## 🔭 Estrutura
O programa é composto pelos seguintes arquivos/diretórios:
- `config`          - Arquivos de topologia e informações sobre o roteador
- `dataStructure.c` - Estrutura de armazenamento de dados
- `importers.h`     - Importação das funções e configurações
- `includes`        - Funcões auxiliares para determinadas operações
- `main.c`          - Execução principal
- `threads`         - Threads para execução de tarefas

## ⚙️ Configuração
Alguns dos parametros que se pode regular na execução do programa se encontra em `importers.h` e em `config`, podemos alterar as seguintes informações:

### Configurações de execução
    // Define o tamanho da mensagem
    #define MESSAGE_SIZE 100

    // Define o valor do infinito
    #define INFINITE 100

    // Define tempos de conexão
    #define DISCONECT_TIME 45
    #define SIGNAL_TIME 15

    // Define os tipos de pacote
    #define CONTROL_TYPE 1
    #define DATA_TYPE 0

### Configurações da topologia da rede
Para a configuração da topologia e endereços de cada roteador, vamos possuir dois arquivos:
- `config/enlaces.config` - Responsavel pela configuração de enlaces de roteador para roteador e seu respectivo custo.
- `config/roteador.config` - Responsavel pela configuração das informações do roteador como identificador, ip, e porta.

## ⚡ Execução
Para compilar o programa, podemos utilizar o compilador gcc com o seguinte comando

    gcc main.c includes/* threads/* -o router

Em seguida conseguimos executar ele com o seguinte comando

    ./router <router_id>

## 🤔 Funcionamento
Ao executar o programa vamos ter acesso as seguintes opções:

    1 - Enviar mensagem
    2 - Exibir mensagens de dados recebidas
    3 - Exibir mensagens de controle recebidas
    4 - Exibir vetor distancia
    0 - Finalizar

Cada opção terá uma execução diferente, para a sua respectiva funcionalidade.
