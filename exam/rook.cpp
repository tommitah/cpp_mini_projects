#include <iostream>
#include <vector>
#include <ctime>
#include <future>
#include <mutex>

class Ruutu {
public:
  int _x;
  int _y;

  Ruutu(int x, int y) : _x(x), _y(y) {}
};

/*
 * Tehtävä 1: 
 *    Siirto-olio sisältää pointterit tornin lähtö- ja 
 *    loppuruudun arvoihin.
 * */
class Siirto {
public:
  Ruutu *_lahto;
  Ruutu *_loppu;

  Siirto(Ruutu *lahto, Ruutu *loppu) : _lahto(lahto), _loppu(loppu) {}
  void tulostaSiirto() {
    std::cout << _lahto->_x << "," << _lahto->_y << "-->" << _loppu->_x << ","
              << _loppu->_y << std::endl;
  }
};

/*
 * Tehtävä 1:
 *    Sijaintia käyttäen lisätään Siirto-listaan ne Siirrot,
 *    joiden loppusijainti on joko samalla rivillä tai sarakkeella,
 *    poislukien lähtösijainti.
 * Bonus:
 *    siirtoLista sisältää Siirtoja Ruutujen sijasta.
 * */
void annaSiirrot(std::vector<Siirto> &siirtoLista, Ruutu sijainti) {
  // Lisätään kaikki tornin rivissä olevat ruudut.
  for (int x = 0; x < 8; ++x) {
    // ei lasketa lähtöruutua
    if (x == sijainti._x)
      continue;
    // std::cout << x << ", " << sijainti._y << std::endl; // Debug
    Ruutu ruutu(x, sijainti._y);
    Siirto siirto(&sijainti, &ruutu);
    // siirto.tulostaSiirto(); // Debug
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
    // siirto.tulostaSiirto(); // Debug
    siirtoLista.push_back(siirto);
  }
}


/*
 * Tehtävä 3: Yritys
 *    Valitettavasti en saa kääntymään näitä rinnakkaistamisjuttuja, en ehtinyt kokeilla clangilla,
 *    mutta g++ ei suostu kääntämään edes dokumentaation esimerkkejä, 
 *    joten oletan että vika järjestelmän asetuksissa tai jotain.
 *    Muuten periaatteessa sama, kuin teht.1 funktio, mutta lisättiin mutex jolla estetään, 
 *    ettei useampi säie kävisi siirtoListan kimppuun samanaikaisesti.
 * */
static std::mutex s_SiirtoMutex;

static void ASYNC_annaSiirrot(std::vector<Siirto> &siirtoLista, Ruutu sijainti) {
  // Lisätään kaikki tornin rivissä olevat ruudut.
  for (int x = 0; x < 8; ++x) {
    // ei lasketa lähtöruutua
    if (x == sijainti._x)
      continue;
    // std::cout << x << ", " << sijainti._y << std::endl; // Debug
    Ruutu ruutu(x, sijainti._y);
    Siirto siirto(&sijainti, &ruutu);
    // siirto.tulostaSiirto(); // Debug

    // RIIA, luodaan lukko, ja se tuhoutuu scopen päättyessä.
    std::lock_guard<std::mutex> lock(s_SiirtoMutex);
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
    // siirto.tulostaSiirto(); // Debug
    
    // RIIA, luodaan lukko, ja se tuhoutuu scopen päättyessä.
    std::lock_guard<std::mutex> lock(s_SiirtoMutex);
    siirtoLista.push_back(siirto);
  }
}

/*
 * Tehtävä 4: 
 *   Siirtojen toistorakenteiden lavennus vähensi suoritusaikaa,
 *   tosin aika pienen määrän. Jos laventaisi tuon nested loopin niin 
 *   saisi tietystä lisää. Binäärin suoritusaika ~67 ms.
 * */
void LAVENNA_annaSiirrot(std::vector<Siirto>& siirtoLista, Ruutu sijainti) {
  // Luodaan ruutu jokaiselle mahdolliselle destinaatiolle samalla rivillä.
  Ruutu ruutu0(0,sijainti._y);
  Ruutu ruutu1(1,sijainti._y);
  Ruutu ruutu2(2,sijainti._y);
  Ruutu ruutu3(3,sijainti._y);
  Ruutu ruutu4(4,sijainti._y);
  Ruutu ruutu5(5,sijainti._y);
  Ruutu ruutu6(6,sijainti._y);
  Ruutu ruutu7(7,sijainti._y);

  // Luodaan Siirto vastaamaan jokaista Ruutua rivillä
  Siirto siirto0(&sijainti, &ruutu0);
  Siirto siirto1(&sijainti, &ruutu1);
  Siirto siirto2(&sijainti, &ruutu2);
  Siirto siirto3(&sijainti, &ruutu3);
  Siirto siirto4(&sijainti, &ruutu4);
  Siirto siirto5(&sijainti, &ruutu5);
  Siirto siirto6(&sijainti, &ruutu6);
  Siirto siirto7(&sijainti, &ruutu7);

  // Luodaan ruutu jokaiselle mahdolliselle destinaatiolle samalla sarakkeella.
  Ruutu ruutu8 (sijainti._x, 0);
  Ruutu ruutu9 (sijainti._x, 1);
  Ruutu ruutu10(sijainti._x, 2);
  Ruutu ruutu11(sijainti._x, 3);
  Ruutu ruutu12(sijainti._x, 4);
  Ruutu ruutu13(sijainti._x, 5);
  Ruutu ruutu14(sijainti._x, 6);
  Ruutu ruutu15(sijainti._x, 7);

  // Luodaan Siirto vastaamaan jokaista Ruutua sarakkeella
  Siirto siirto8 (&sijainti, &ruutu8);
  Siirto siirto9 (&sijainti, &ruutu9);
  Siirto siirto10(&sijainti, &ruutu10);
  Siirto siirto11(&sijainti, &ruutu11);
  Siirto siirto12(&sijainti, &ruutu12);
  Siirto siirto13(&sijainti, &ruutu13);
  Siirto siirto14(&sijainti, &ruutu14);
  Siirto siirto15(&sijainti, &ruutu15);

  // Talletetaan kaikki siirrot listaan. Pidetään huoli, 
  // että listaan ei päädy "tyhjäsiirtoja"
  if (!(siirto0._loppu == &sijainti))  siirtoLista.push_back(siirto0);
  if (!(siirto1._loppu == &sijainti))  siirtoLista.push_back(siirto1);
  if (!(siirto2._loppu == &sijainti))  siirtoLista.push_back(siirto2);
  if (!(siirto3._loppu == &sijainti))  siirtoLista.push_back(siirto3);
  if (!(siirto4._loppu == &sijainti))  siirtoLista.push_back(siirto4);
  if (!(siirto5._loppu == &sijainti))  siirtoLista.push_back(siirto5);
  if (!(siirto6._loppu == &sijainti))  siirtoLista.push_back(siirto6);
  if (!(siirto7._loppu == &sijainti))  siirtoLista.push_back(siirto7);
  if (!(siirto8._loppu == &sijainti))  siirtoLista.push_back(siirto8);
  if (!(siirto9._loppu == &sijainti))  siirtoLista.push_back(siirto9);
  if (!(siirto10._loppu == &sijainti)) siirtoLista.push_back(siirto10);
  if (!(siirto11._loppu == &sijainti)) siirtoLista.push_back(siirto11);
  if (!(siirto12._loppu == &sijainti)) siirtoLista.push_back(siirto12);
  if (!(siirto13._loppu == &sijainti)) siirtoLista.push_back(siirto13);
  if (!(siirto14._loppu == &sijainti)) siirtoLista.push_back(siirto14);
  if (!(siirto15._loppu == &sijainti)) siirtoLista.push_back(siirto15);
}

/*
 * Tehtävä 2:
 *    Binäärin suoritukseen kuluu ~73 ms.
 *
 * Tehtävä 4:
 *    Binäärin suoritusaika ~67 ms.
 * */
int main() {
  std::vector<Siirto> siirrot;

  clock_t alku = clock();

  // Tehtävä 2: 
  //for (int x = 0; x < 8; ++x) {
    //for (int y = 0; y < 8; ++y) {
      //annaSiirrot(siirrot, *new Ruutu(x, y));
    //}
  //}
  // /Tehtävä 2

  // Tehtävä 3:
  //for (int x = 0; x < 8; ++x) 
    //for (int y = 0; y < 8; ++y)
   //   std::future<void> fut = std::async(std::launch::async, ASYNC_annaSiirrot, *new Ruutu(x, y));
  // /Tehtävä 3

  // Tehtävä 4:
  for (int x = 0; x < 8; ++x) 
    for (int y = 0; y < 8; ++y)
      LAVENNA_annaSiirrot(siirrot, *new Ruutu(x, y));
  // /Tehtävä 4
  

  clock_t loppu = clock();
  clock_t kesto = loppu - alku;

  std::cout << "Kesto: " << (float)kesto / CLOCKS_PER_SEC << " sekuntia" << std::endl;

  return 0;
}
