# Programação Socket e Roteamento
Desenvolvido por **Paulo E. R. Werle** 👋

## 🔭 Estrutura
O programa é composto pelos seguintes arquivos/diretórios:
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

## ⚡ Execução
Para compilar o programa, podemos utilizar o compilador gcc com o seguinte comando

    gcc main.c includes/* threads/* -o router

Em seguida conseguimos executar ele com o seguinte comando

    ./router <ip> <port>

## 🤔 Funcionamento
Ao executar o programa vamos ter acesso as seguintes opções:

    1 - Enviar mensagem
    2 - Exibir mensagens recebidas
    0 - Finalizar

Cada opção terá uma execução diferente, para a sua respectiva funcionalidade.