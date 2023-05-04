#include <iostream>
#include <queue>

using namespace std;

int main() {
    int deck_size;

    // Lê o valor de n enquanto houver entrada
    while (cin >> deck_size) {
      // Cria uma fila de inteiros, e insere o valor 2 na fila
      queue<int> card_queue;
      card_queue.push(2);

      // Cria variavel para contar as operações
      int num_shuffles = 1;

      // Enquanto o primeiro elemento da fila não for 1
      while (card_queue.front() != 1) {
        // Pega o primeiro elemento da fila, e o remove da fila
        int current_card = card_queue.front();
        card_queue.pop();

        // Calcula o valor de n/2
        int half_deck = deck_size / 2;

        // Se o valor da carta for menor ou igual a n/2
        // Dobra o valor da carta
        // Insere a nova carta na fila
        if (current_card <= half_deck) {
          current_card += current_card;
          card_queue.push(current_card);

        // Se não
        // Subtrai o valor de (n - carta + 1) da carta
        // Insere a nova carta na fila
        } else {
          current_card -= (deck_size - current_card + 1);
          card_queue.push(current_card);
        }

        // Incrementa o contador de embaralhamentos
        num_shuffles++;
      }

       // Imprime o número de embaralhamentos realizados
      cout << num_shuffles << endl;
    }
    return 0;
}
