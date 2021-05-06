#include <bits/c++config.h>
#include <fstream>
#include <iostream>
#include <new>
#include <sstream>
#include <stdlib.h>
#include <string>

auto log_to_file(const std::string &text) {
  std::ofstream log_file;
  log_file.open("memory_log.txt", std::ios::out | std::ios::app);
  log_file << text;
  log_file << std::endl;
  log_file.close();
}

std::string operator_call_format(void *p) {
  std::stringstream stream;
  std::string str;
  stream << p && stream >> str;
  return str;
}

class tester {
public:
  tester() { std::cout << "new tester" << std::endl; }
  ~tester() { std::cout << "byebye tester" << std::endl; }

  /*
   * Overrides new operator
   * */
  void *operator new(std::size_t n) noexcept(false) {
    void *p = malloc(n);
    log_to_file("Memory allocated. " + operator_call_format(p));
    return p;
  }

  /*
   * Overrides delete operator
   * */
  void operator delete(void *p) noexcept(true) {
    log_to_file("Memory freed. " + operator_call_format(p));
    free(p);
  }
};

int main() {
  tester *test = new tester();
  delete test;

  return 0;
}
