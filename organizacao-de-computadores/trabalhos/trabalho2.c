#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// Alunos:
// Paulo Eduardo Rodrigues Werle
// André Lucas Machado Giachini

// Repositorio
// https://github.com/paulo-werle/Uffs/blob/master/Organizacao-de-Computadores/Trabalhos/Trabalho2.c

// Como rodar o projeto
// gcc Trabalho2.c -lm -o nome_do_arquivo
// ./nome_do_arquivo

// Descrição
// Número de células na MP: 128;
//  Tamanho do bloco: 4 células;
//  Número de linhas na cache: 8;
//  Tamanho da célula: 8 bits;
//  Tamanho do conjunto: 2 ou 4 linhas (definida pelo número entre parênteses ao lado da política de cada grupo);

// OBS1: Os valores e endereços devem ser apresentados em hexadecimal ou binário.
// OBS2: Ao ler um endereço deve informar se encontrou na cache ou não. Qual o número do bloco a que se refere o endereço, qual o quadro na cache que está mapeado e o deslocamento do mesmo.
// OBS3: A memória principal deve ser preenchida com valores aleatórios (entre 0x00 e 0xFF) no início da execução.
// OBS4: Os contadores da política de substituição possuem 3 bits.

// Configurações do programa
// Número de células na MP: 128;
#define CELULAS_NA_MP 128
// Tamanho do bloco: 4 células;
#define TAMANHO_BLOCO 4
// Número de linhas na cache: 8;
#define LINHAS_NA_CHACHE 8
// Tamanho da célula: 8 bits
#define CELULA 8

// Structs
struct bloco
{ // Bloco de memoria
  
  char celula[TAMANHO_BLOCO][9];
};
typedef struct bloco Bloco;

struct memoria_principal
{ // Memoria principal
  
  Bloco bloco[32];
};
typedef struct memoria_principal MemoriaPrincipal;

struct linhas
{ // Linhas da memoria cache
  Bloco bloco; 
  char rotulo[6]; // 5 bits 00111  11
  char LRU[4];      
  int validade;
};
typedef struct linhas Linhas;

struct cache
{ //Memoria cache
  Linhas linhas[LINHAS_NA_CHACHE];
};
typedef struct cache Cache;

struct estatistica
{ // Estatisticas
  int leitura_acertos;
  int leitura_falta; 
  int escrita_acertos;
  int escrita_falta;
};
typedef struct estatistica Estatistica;

// ---------- Funções auxiliares ----------
int menu() {
  // Inicia variavel
  int op;

  // Imprime opções
  printf("1) Ler o conteúdo de um endereço da memória\n");
  printf("2) Escrever endereço da memória\n");
  printf("3) Apresentar as estatísticas\n");
  printf("4) Mostrar cache\n");
  printf("5) Mostrar memoria principal\n");
  printf("0) Encerrar o programa\n");
  scanf("%d", &op );
  printf("\n");

  return op;
}

float calculaPorcentagem(int valor1, int valor2){
  if (valor1 == 0 && valor2 == 0){
    return 0.0;
  }

  float valor = valor1;
  valor = (valor / (valor1 + valor2) ) * 100;
  return valor;
}

int binarioParaDecimal( int binario ){
  // Inicia variaveis
  int contador, decimal = 0;

  // Converte binario para decimal
  for (contador = 0; binario > 0; contador++){
    decimal += pow(2, contador) * (binario % 10);
    binario = binario / 10;
  }

  return decimal;
}

int decimalParaBinario(int numero){
  // Inicia variaveis
  int contador, binario = 0;
  
  // Converte para binario
  for (contador = 1; numero > 0; contador *= 10){
    binario = binario + numero % 2 * contador;
    numero = numero / 2;
  }

  return binario;
}

void extrairDado( char dado_origem[], char dado_destino[], int origem, int destino){
  // Inicia variaveis
  int contador_destino = 0, contador_origem = origem;


  //Pega do bit 0 ao 5 para extrair o rotulo
  //Pega do bit 5 ao 7 para extrair o deslocamento
  
  // Copia dado
  while(contador_origem < destino){
    dado_destino[contador_destino] = dado_origem[contador_origem];

    contador_destino++;
    contador_origem++;
  }
}

int stringParaInteiro(char origem[]) {
  // Inicia variaveis
  int contador, inteiro = 0;

  // Converte numero para inteiro
  for ( contador = 0; contador < strlen(origem); contador++ ){
    inteiro = inteiro * 10;
    inteiro = inteiro + (origem[contador] - '0');
  }

  return inteiro;
}
// ---------- Funções auxiliares ----------

void inteiroParaString(int origem, char destino[]){
  
  sprintf(destino, "%08d" ,origem);
}

// ---------- Funções de dados ----------
MemoriaPrincipal *iniciarMemoriaPrincipal(){
  // Inicia variaveis
  int contador1, contador2, aleatorio;
  
  // Aloca memoria principal
  MemoriaPrincipal *memoria_principal = malloc (sizeof(MemoriaPrincipal));

  // Percorre memoria principal iniciando dados
  for ( contador1 = 0; contador1 < (CELULAS_NA_MP / TAMANHO_BLOCO); contador1++ ){
    for ( contador2 = 0; contador2 < TAMANHO_BLOCO; contador2++ ){
      aleatorio = rand() % 256;

      int result;
      char celula[8];
      result = decimalParaBinario(aleatorio);  //numero em binario e inteiro

      inteiroParaString(result, celula); //string do binario em 8 bits
      //memoria_principal->bloco[contador1].celula[contador2] = teste;

      strcpy(memoria_principal->bloco[contador1].celula[contador2], celula);

      
    }
  }

  return memoria_principal;
}

Cache *iniciarCache(){
  // Inicia variaveis
  int contador;

  // Aloca memoria cache
  Cache *cache = malloc (sizeof(Cache));

  // Percorre memoria cache iniciando dados
  for ( contador = 0; contador < LINHAS_NA_CHACHE; contador++ ){
    cache->linhas[contador].validade = 0;
    strcpy(cache->linhas[contador].LRU, "000");
  }
  
  return cache;
}

Estatistica *iniciarEstatistica(){

  Estatistica *estatistica = malloc (sizeof(Estatistica));
  estatistica->leitura_acertos = 0;
  estatistica->leitura_falta = 0;
  estatistica->escrita_acertos = 0;
  estatistica->escrita_falta = 0;

  return estatistica;
}

int vereficaDadoNaCache(Cache *cache, char rotulo[]){
  // Inicia variaveis
  int contador, hit = 0;
  
  // Percorre cache verificando se dado está presente
  for ( contador = 0; contador < LINHAS_NA_CHACHE; contador++){
    if ( cache->linhas[contador].validade == 1 && !strcmp(cache->linhas[contador].rotulo, rotulo) ){
      hit = 1;
      
    }
  }

  return hit;
}

void colocaDadoNaCache(MemoriaPrincipal *memoria_principal, Cache *cache, char rotulo[]){
  // Inicia variaveis
  int contador, lru_cache, posicao_linha, lru_contador = 0;

  // Inicia um bloco auxiliar
  Bloco bloco_auxiliar;
  // Seleciona dado da memoria principal
  bloco_auxiliar = memoria_principal->bloco[ binarioParaDecimal(stringParaInteiro(rotulo)) ];

  // printf("%s\n", rotulo);
  
  // Percorre cache
  for ( contador = 0; contador < LINHAS_NA_CHACHE; contador++){

    // Caso tiver uma linha em que o bit de validade seja 0
    if (!cache->linhas[contador].validade){
      
      // Coloca bloco na cache
      cache->linhas[contador].bloco = bloco_auxiliar;
      cache->linhas[contador].validade = 1;
      strcpy(cache->linhas[contador].rotulo, rotulo);
      strcpy(cache->linhas[contador].LRU, "000");
      return;
    }

    // Pega lru da cache e converte para decimal
    lru_cache = binarioParaDecimal( stringParaInteiro(cache->linhas[contador].LRU) );

    // Caso o contador atual for menor do que o da cache
    if (lru_contador < lru_cache){
      lru_contador = lru_cache;
      posicao_linha = contador;
    }
  }

  cache->linhas[posicao_linha].bloco = bloco_auxiliar;
  cache->linhas[posicao_linha].validade = 1;
  strcpy(cache->linhas[posicao_linha].rotulo, rotulo);
  strcpy(cache->linhas[posicao_linha].LRU, "000");
}

void alteraDadoNaCache(Cache *cache, char rotulo[], char deslocamento[], char celula[]){
  // Inicia variaveis
  int contador, lru_linha;
  char dado_lru[8];

  // Percorre cache para alterar o dado
  for ( contador = 0; contador < LINHAS_NA_CHACHE; contador++ ){
    if ( !strcmp(cache->linhas[contador].rotulo, rotulo) ){
      strcpy(cache->linhas[contador].LRU, "000");
      strcpy(cache->linhas[contador].bloco.celula[ binarioParaDecimal(stringParaInteiro(deslocamento)) ], celula);
    } else {
      // Incrementa LRU
      lru_linha = binarioParaDecimal( stringParaInteiro(cache->linhas[contador].LRU) );
      if ( lru_linha < 7 ){
        lru_linha++;
        inteiroParaString(decimalParaBinario(lru_linha), dado_lru);
        extrairDado(dado_lru, cache->linhas[contador].LRU, 5, 8);
      }
    }
  }
}

void imprimeMemoriaPrincipal(MemoriaPrincipal *memoria_principal){
  // Inicia variaveis
  int contador1, contador2;

  // Imprime cabecalho
  printf("-----   MEMORIA PRINCIPAL   ------------------------------\n");
  printf("| Bloco \t| C0 \t\t| C1 \t\t| C2 \t\t| C3 \t\t|\n");

  // Percorre linhas na memoria principal
  for ( contador1 = 0; contador1 < 32; contador1++){
    
    // Imprime dados da memoria principal
    printf("| %d \t\t", contador1);
    
    // Percorre bloco
    for ( contador2 = 0; contador2 < TAMANHO_BLOCO; contador2++){

      // Imprime celulas do bloco da memoria principal
      printf("| %s \t", memoria_principal->bloco[contador1].celula[contador2]);
    }
    printf("|\n");
  }
  printf("------------------------------------------------------\n");
}

void imprimeCache(Cache *cache){
  // Inicia variaveis
  int contador1, contador2;

  // Imprime cabecalho
  printf("-----   MEMORIA CACHE   ------------------------------\n");
  printf("|LRU \t| Val. \t| Rot. \t| C0 \t\t| C1 \t\t| C2 \t\t| C3 \t\t|\n");

  // Percorre linhas na cache
  for ( contador1 = 0; contador1 < LINHAS_NA_CHACHE; contador1++){
    
    // Imprime dados da cache 
    printf("|%s \t| %d \t| %s ", cache->linhas[contador1].LRU, cache->linhas[contador1].validade, cache->linhas[contador1].rotulo);
    
    // Percorre bloco
    for ( contador2 = 0; contador2 < TAMANHO_BLOCO; contador2++){

      // Imprime celulas do bloco da cache
      printf("| %s \t", cache->linhas[contador1].bloco.celula[contador2]);
    }
    printf("|\n");
  }
  printf("------------------------------------------------------\n");
}
// ---------- Funções de dados ----------

// ---------- Funções de operações ----------
void lerConteudo(MemoriaPrincipal *memoria_principal, Cache *cache, Estatistica *estatistica){
  // Inicia variaveis
  int contador, celula, lru_linha;
  char entrada[8], rotulo[6], deslocamento[3], dado_lru[8];
  
  // Pegar dado de qual memoria vai ser lida
  printf("Digite qual endereço de memoria deseja ler; Ex 00000 00\n");
  scanf("%s", entrada); 

  // Manipula dados
  extrairDado(entrada, rotulo, 0, 5);
  extrairDado(entrada, deslocamento, 5, 8);
  //printf("deslocamento %s\n", deslocamento);

  // Caso não tiver na cache coloca
  if( !vereficaDadoNaCache(cache, rotulo) ){
    printf("Não encontrado na Cache, buscando na memória principal..\n");
    colocaDadoNaCache(memoria_principal, cache, rotulo);
    
    // Houve uma falta
    estatistica->leitura_falta++;
  } else {
    estatistica->leitura_acertos++;
    printf("Dado encontrado na cache\n");
  }

  // Imprime cabecalho
  printf("DADO DA MEMORIA\n");
  printf("|Lin. \t| Cel. \t| Val. \t|\n");

  // Converte deslocamento para decimal
  int inteiro = stringParaInteiro(deslocamento);
  int decimal = binarioParaDecimal(inteiro);

  // Percorre cache para imprimir dado
  for ( contador = 0; contador < LINHAS_NA_CHACHE; contador++){

    // Caso achar o dado o imprime
    if ( !strcmp(cache->linhas[contador].rotulo, rotulo) ){
      strcpy(cache->linhas[contador].LRU, "000");

      printf("| %d \t| %d \t| %s \t|\n", contador, decimal, cache->linhas[contador].bloco.celula[decimal]);
    } else {

      // Incrementa o lru
      lru_linha = binarioParaDecimal( stringParaInteiro(cache->linhas[contador].LRU) );
      if ( lru_linha < 7 ){
        lru_linha++;
        inteiroParaString(decimalParaBinario(lru_linha), dado_lru);
        extrairDado(dado_lru, cache->linhas[contador].LRU, 5, 8);
      }
      
    }
  }
  printf("\n");
}

void escreverNaMemoria(MemoriaPrincipal *memoria_principal, Cache *cache, Estatistica *estatistica){

  // Inicia variaveis
  char endereco[8], rotulo[6], deslocamento[3], celula[9];

  // Pegar dado de qual memoria vai ser lida
  printf("Digite qual endereço de memoria deseja escrever; Ex 0000000 (7bits) \n");
  scanf("%s", endereco); 

  // Le dado que vai ser armazenado
  printf("Informe o que deseja escrever na memoria; Ex 00000000 (8bits)\n");
  scanf("%s", celula);

  // Manipula dados
  extrairDado(endereco, rotulo, 0, 5);
  extrairDado(endereco, deslocamento, 5, 8);

  // Caso não tiver na cache coloca
  if( !vereficaDadoNaCache(cache, rotulo) ){
    colocaDadoNaCache(memoria_principal, cache, rotulo);

    estatistica-> escrita_falta++;
  }else {
    estatistica->escrita_acertos++;
    printf("Dado encontrado na cache\n");
  }

  // Altera dados na cache
  alteraDadoNaCache(cache, rotulo, deslocamento, celula);

  // Escreve dado na memoria principal
  strcpy(memoria_principal->bloco[ binarioParaDecimal(stringParaInteiro(rotulo)) ].celula[ binarioParaDecimal(stringParaInteiro(deslocamento)) ], celula);
}

void mostraEstatisticas(Estatistica *estatistica){

  printf("-----   ESTATISTICAS   ------------------------------\n");
  printf("Leituras: %d \n", estatistica->leitura_acertos + estatistica->leitura_falta);
  
  printf("\t hit: %d, %.2f%% \n", estatistica->leitura_acertos, calculaPorcentagem(estatistica->leitura_acertos, estatistica->leitura_falta));
  printf("\t miss: %d, %.2f%% \n\n", estatistica->leitura_falta, calculaPorcentagem(estatistica->leitura_falta, estatistica->leitura_acertos));
  
  printf("Escritas: %d \n", estatistica->escrita_acertos + estatistica->escrita_falta);
  printf("\t hit: %d, %.2f%% \n", estatistica->escrita_acertos, calculaPorcentagem(estatistica->escrita_acertos, estatistica->escrita_falta));
  printf("\t miss: %d, %.2f%% \n\n", estatistica->escrita_falta, calculaPorcentagem(estatistica->escrita_falta, estatistica->escrita_acertos));

  printf("Total de acessos: %d\n\n", (estatistica->leitura_acertos + estatistica->leitura_falta) + (estatistica->escrita_acertos + estatistica->escrita_falta));

}
// ---------- Funções de operações ----------

int main(){
  // Inicia variaveis
  int operation = 1;
  //apresentar as estatísticas de acertos e faltas (absolutos e percentuais)
  //para as três situações: leitura, escrita e geral;
  
  srand(time(0));

  // Inicia estatisticas
  Estatistica *estatistica = iniciarEstatistica();

  // Inicia memoria principal
  MemoriaPrincipal *memoria_principal = iniciarMemoriaPrincipal();

  // Inicia memoria cache
  Cache *cache = iniciarCache();

  // Entra no laço do programa
  while ( operation ) {
    operation = menu();

    switch (operation)
    {
      case 1:
        // Ler o conteúdo de um endereço da memória
        lerConteudo(memoria_principal, cache, estatistica);
        break;
 
      case 2:
        // Escrever endereço da memória
        escreverNaMemoria(memoria_principal, cache, estatistica);
        break;
 
      case 3:
        //Apresentar as estatísticas
        mostraEstatisticas(estatistica);
        break;

      case 4:
        imprimeCache(cache);
        break;

      case 5:
        // Imprimir memoria principal
        imprimeMemoriaPrincipal(memoria_principal);
        break;
    }
  }

  return 0;
}