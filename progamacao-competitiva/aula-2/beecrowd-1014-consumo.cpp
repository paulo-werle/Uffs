#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int km;
  float l;

  cin >> km;
  cin >> l;

  std::cout << std::fixed << std::setprecision(3) << km/l << " km/l\n";

  return 0;
}