#include <iostream>

class Big_Data {
  public:
    Big_Data(size_t size) { _buffer = (char*)malloc(size); }
    ~Big_Data() { free(_buffer); }

  private:
    char* _buffer;
};


