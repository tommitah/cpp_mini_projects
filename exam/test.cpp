#include <iostream>
#include <future>

bool is_prime(int x) {
  std::cout << "Calc. pls w8 ....." << std::endl;
  for (int i = 2; i < x; ++i) if (x % i == 0) return false;
  return true;
}

int main() {
  std::future<bool> fut = std::async(std::launch::async, is_prime, 313222313);

  bool ret = fut.get();

  if (ret) std::cout << "YUEAH";
  else std::cout << "NOAIUYDO";

  return 0;
}
