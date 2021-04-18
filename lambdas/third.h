#include <iostream>

class Big_Data {
public:
  Big_Data(size_t size) { _buffer = (char *)malloc(size); }
  ~Big_Data() { free(_buffer); }

  // copy constructor and assignment operator
  Big_Data(const Big_Data &data) {
    _buffer = (char *)malloc(sizeof(data._buffer));
  }

  Big_Data &operator=(const Big_Data &data) {
    if (_buffer == data._buffer)
      return *this;
    _buffer = (char *)malloc(sizeof(data._buffer));
    return *this;
  }

  auto get() { return &_buffer; }

private:
  char *_buffer;
};
