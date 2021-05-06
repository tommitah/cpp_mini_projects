#include <iostream>
#include <vector>

class Ruutu {
public:
  int _x;
  int _y;

  Ruutu(int x, int y) : _x(x), _y(y) {}
};

class Siirto {
public:
  Ruutu *_lahto;
  Ruutu *_loppu;

  Siirto(Ruutu *lahto, Ruutu *loppu) : _lahto(lahto), _loppu(loppu) { }
  void tulostaSiirto() {
    std::cout 
      << _lahto->_x << "," << _lahto->_y 
      << "-->" 
      << _loppu->_x << "," << _loppu->_y 
      << std::endl; 
  }
};

void annaSiirrot(std::vector<Siirto> &siirtoLista, Ruutu sijainti) {
  // Lisätään kaikki tornin rivissä olevat ruudut.
  for (int x = 0; x < 8; ++x) {
    // ei lasketa lähtöruutua
    if (x == sijainti._x)
      continue;
    // std::cout << x << ", " << sijainti._y << std::endl; // Debug
    Ruutu ruutu(x, sijainti._y);
    Siirto siirto(&sijainti, &ruutu);
    siirto.tulostaSiirto(); // Debug
    siirtoLista.push_back(siirto);
  }
  // Lisätään kaikki tornin sarakkeessa olevat ruudut.
  for (int y = 0; y < 8; ++y) {
    // ei lasketa lähtöruutua
    if (y == sijainti._y)
      continue;
    // std::cout << sijainti._x << ", " << y << std::endl; // Debug
    Ruutu ruutu(sijainti._x, y);
    Siirto siirto(&sijainti, &ruutu);
    siirto.tulostaSiirto(); // Debug
    siirtoLista.push_back(siirto);
  }
}

int main() {
  std::vector<Siirto> siirrot;
  Ruutu lahtoruutu(3, 4);

  annaSiirrot(siirrot, lahtoruutu);

  return 0;
}
