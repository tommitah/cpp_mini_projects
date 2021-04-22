#include <iostream>

int main() {
  double value = 1;

  while(value < 1000000000000000000) {
    value += value / (1 / value);
  }

  std::cout << value;


  return 0;
}
