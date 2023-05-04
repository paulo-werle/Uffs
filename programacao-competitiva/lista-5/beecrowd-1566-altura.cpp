#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

// Definimos o tamanho máximo do array a ser utilizado
const int MAXN = 3000005;

// Declaramos os arrays que serão utilizados no algoritmo
int cnt[MAXN], a[MAXN], b[MAXN];

// Definimos a função counting sort
void counting_sort(int n) {
  // Inicializamos o array cnt com zero
  memset(cnt, 0, sizeof(cnt));

  // Contamos quantos elementos possuem cada valor no array a
  for (int i = 1; i <= n; i++) {
    cnt[a[i]]++;
  }

  // Calculamos a posição final de cada valor no array b
  for (int i = 1; i <= 230; i++) {
    cnt[i] += cnt[i-1];
  }

  // Copiamos os elementos de a para b em ordem crescente
  for (int i = n; i >= 1; i--) {
    b[cnt[a[i]]] = a[i];
    cnt[a[i]]--;
  }
}

int main() {
  int t;
  scanf("%d", &t);

  // Loop para cada caso de teste
  while (t--) {
    int n;
    scanf("%d", &n);

    // Lemos os elementos do array a
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }

    // Ordenamos os elementos de a e colocamos em b
    counting_sort(n);

    // Imprimimos os elemento de b
    for (int i = 1; i <= n; i++) {
      printf("%d", b[i]);

      // Se não for o último elemento, imprimimos um espaço em branco
      if (i < n) {
        printf(" ");
      }
    }

    // Imprimimos uma nova linha para o próximo caso de teste
    printf("\n");
  }

  return 0;
}