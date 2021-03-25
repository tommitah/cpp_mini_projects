#include <iostream>
#include <string>
#include <memory>
#include "Log_Ptr.h"

class Foo {
  public:
    Foo() { std::cout << "Ima Foo" << std::endl; }
    ~Foo() { std::cout << "Ima dead Foo" << std::endl;  }
    auto say_something(std::string something) {
      std::cout << something << std::endl;
    }
};

int main() {
  Log_Ptr<Foo> log_ptr_foo(new Foo);
  (*log_ptr_foo).say_something("Hey y'all.");
  log_ptr_foo->say_something("HIYA BICHAS.");
  
  // copy:
  Log_Ptr<Foo> copy_ptr = log_ptr_foo;
  // assignment: ":-D"
  Log_Ptr<Foo> ass_ptr(new Foo);
  ass_ptr = log_ptr_foo;
 
  return 0;
}




















