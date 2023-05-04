#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

// Função para ler entrada e classifica-las
void readInput(string words[], int lengths[], int& numWords) {

  // Lê uma linha inteira da entrada padrão e a armazena em line.
  string line;
  getline(cin, line);

  // Define numWords como 0.
  numWords = 0;
  bool completeWord = true;
  string currentWord;

  // Começa um loop que percorre cada caractere da string line.
  for (int i = 0; i < line.length(); i++) {

    // Se o caractere atual for um espaço em branco:
    if (line[i] == ' ') {
      // Recebe a palavra atual e o comprimento dessa palavra.
      words[numWords] = currentWord;
      lengths[numWords] = currentWord.length();

      // Limpa a string currentWord.
      currentWord.clear();
      numWords++;

      // Define completeWord como falso.
      completeWord = false;

    } else {
      // Adiciona o caractere atual à string currentWord.
      currentWord += line[i];

      // Define completeWord como verdadeiro.
      completeWord = true;
    }
  }

  // Se a última palavra lida não terminou com um espaço em branco:
  // Recebe a palavra atual e o comprimento dessa palavra.
  if (completeWord) {
    words[numWords] = currentWord;
    lengths[numWords] = currentWord.length();
    numWords++;
  }
}

// Função para ordenar palavras pelo tamanho
void sortWordsByLength(string words[], int lengths[], int numWords) {

  // Começa um loop que percorre cada palavra do array de palavras.
  for (int k = 0; k < numWords - 1; k++) {

    // Começa um loop aninhado que percorre cada palavra do array de palavras não ordenadas.
    for (int i = 0; i < numWords - k - 1; i++) {

      // Se a palavra atual for mais curta que a próxima:
      // Troca os comprimentos das duas palavras.
      if (lengths[i] < lengths[i + 1]) {
        swap(lengths[i], lengths[i + 1]);
        swap(words[i], words[i + 1]);
      }
    }
  }
}

// Função para imprimir as palavras
void printWords(string words[], int numWords) {

  // Começa um loop que percorre cada palavra do array de palavras, exceto a última.
  for (int i = 0; i < numWords - 1; i++) {
    cout << words[i] << " ";
  }

  // Imprime a última palavra seguida de uma nova linha.
  cout << words[numWords - 1] << endl;
}

int main() {
  int numCases;
  cin >> numCases;

  // Ignora o caractere '\n' que ficou no buffer de entrada.
  cin.ignore();

  // Começa um loop que executa o numero de casos de vezes.
  while (numCases--) {
    string words[51];
    int lengths[51];
    int numWords;

    // Chama a função readInput para ler as palavras e seus comprimentos.
    readInput(words, lengths, numWords);

    // Chama a função sortWordsByLength para classificar as palavras por comprimento.
    sortWordsByLength(words, lengths, numWords);

    // Chama a função printWords para imprimir as palavras na ordem correta.
    printWords(words, numWords);
  }

  return 0;
}
