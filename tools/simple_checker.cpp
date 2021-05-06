#include <bits/c++config.h>
#include <fstream>
#include <iostream>
#include <new>
#include <sstream>
#include <stdlib.h>
#include <string>

/*
 * Logs the contents of a string to a named text file.
 * */
auto log_to_file(const std::string &text) {
  std::ofstream log_file;
  log_file.open("memory_log.txt", std::ios::out | std::ios::app);
  log_file << text;
  log_file << std::endl;
  log_file.close();
}

/*
 * Changes the returns a string that's a copy of
 * the memory address.
 * */
std::string operator_call_format(void *p) {
  std::stringstream stream;
  std::string str;
  stream << p && stream >> str;
  return str;
}

/*
 * Tester class.
 * */
class tester {
public:
  tester() { std::cout << "new tester" << std::endl; }
  ~tester() { std::cout << "byebye tester" << std::endl; }

  /*
   * Overrides new operator
   * */
  void *operator new(std::size_t n) {
    void *p = malloc(n);
    log_to_file("Memory allocated. " + operator_call_format(p));
    return p;
  }

  /*
   * Overrides delete operator
   * */
  void operator delete(void *p) {
    log_to_file("Memory freed. " + operator_call_format(p));
    free(p);
  }
};

int main() {
  tester *test = new tester();
  delete test;

  return 0;
}
