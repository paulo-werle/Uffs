#include <cstdio>
#include <cstring>
#include <vector>
#include <set>

using namespace std;

#define sc1(a) scanf("%d", &a)
#define sc2(a,b) scanf("%d %d", &a, &b)
#define INF 0x3f3f3f3f

typedef set<int> si;

si ns;
si::reverse_iterator it;

int arr[10005];
int arr_[10005];

int check(int k, int sum, bool b) {
  it = ns.rbegin();
  int d, n, cnt = 0, i = ns.size()-1;

  while(k && it != ns.rend()) {
    n = *it;
    d = sum-n;

    if(b) {
      // Verifica as condições para decrementar os valores de arr e arr_
      if(arr[n] <= 0 || d < 0 || (d==n ? (arr[d]-1) <= 0 : arr[d] <= 0)) {
        it++;
        continue;
      }
    }
    if(!b) {
      // Verifica as condições para decrementar os valores de arr_ e arr
      if(arr_[n] <= 0 || d < 0 || (d==n ?  (arr_[d]-1) <= 0 : arr_[d] <= 0)) {
        it++;
        continue;
      }
    }

    if(b) {
      // Decrementa os valores de arr
      arr[d]--, arr[n]--;

    } else {
      // Decrementa os valores de arr_
      arr_[d]--, arr_[n]--;
    }

    // Atualiza o contador de números usados
    cnt += (d ? 2 : 1);
    k--;
  }

  // Se não foram usados todos os números necessários, retorna INF
  if(k) return INF;

  // Retorna o contador de números usados
  return cnt;
}

void solveCase() {
  int n, m, l, k, w;

  while(sc2(n, m) && (n || m)) {
    // Limpa os arrays arr e arr_
    memset(arr, 0, sizeof arr);
    memset(arr_, 0, sizeof arr_);
    arr[0] = arr_[0] = INF;

    // Limpa o conjunto ns
    ns.clear();
    sc2(l, k);

    for(int i = 0; i < k; i++) {
      sc1(w);

      // Insere os valores do desafio no conjunto ns
      ns.insert(w);

      // Atualiza os valores de arr e arr_
      arr[w]++, arr_[w]++;
    }

    // Inicializa o resultado como INF
    int r = INF;

    // Verifica se é possível obter o resultado com arr
    if((n * 100) % l == 0) {
      r = min(r, check((n * 100) / l, m, 1));
    }

    // Verifica se é possível obter o resultado com arr_
    if((m * 100) % l == 0) {
      r = min(r, check((m * 100) / l, n, 0));
    }

    // Se o resultado for INF ou negativo, imprime "impossivel"
    if(r >= INF || r < 0) {
      puts("impossivel");

    } else {
      printf("%d\n", r);

    }
  }
}

int main(int argc, char const* argv[]) {
  solveCase();
  return 0;
}