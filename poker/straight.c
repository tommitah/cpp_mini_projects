/*

  Harjoitus 3

  Optimoi suorien tunnistus. Älä muuta kääntäjäoptioita.
  Pidä ohjelma yksisäikeisenä.

  Vertaa alkuperäistä ja optimoitua versiota:

  - kuinka paljon enemmän muistia optimoitu versio kuluttaa?
  - kuinka paljon nopeammin optimoitu versio toimii?

  Käännös: gcc straight.c -o straight

*/

#include <stdio.h>
#include <time.h>

#define STRAIGHT_1 0x1F
#define STRAIGHT_2 0x3E
#define STRAIGHT_3 0x7C
#define STRAIGHT_4 0xF8
#define STRAIGHT_5 0x1F0
#define STRAIGHT_6 0x3E0
#define STRAIGHT_7 0x7C0
#define STRAIGHT_8 0xF80
#define STRAIGHT_9 0x1F00
#define STRAIGHT_0 0x100F

extern inline int is_straight(int *k);

extern inline int is_straight_bit(int *k);

int main() {
  /*

    Käydään läpi kaikki viiden kortin permutaatiot, ja lasketaan
    kuin monta suoraa (värisuoraa tai tavallista) löytyy.

    Ks. Wikipedia http://en.wikipedia.org/wiki/Poker_probability :

    Royal flush     4      combinations
    Straight flush  36     combinations
    Straight        10,200 combinations

    Koska 5 korttia voi olla 5 x 4 x 3 x 2 x 1 = 120 järjestyksessä,
    pitäisi suoria löytyä (10200 + 36 + 4) x 120 = 1228800 kappaletta.

  */
  int k0, k1, k2, k3, k4; /*[> Pakan kortit, 0..51<]*/
  int k[5];               /*[> Korttien numeroarvot, 2..14<]*/
  int suoria;             /*[> Suorien lkm<]*/
  clock_t t1, t2;

  t1 = clock();
  suoria = 0;
  for (k0 = 0; k0 < 52; ++k0) {
  for (k1 = 0; k1 < 52; ++k1) { if (k1 == k0) continue;
  for (k2 = 0; k2 < 52; ++k2) { if (k2 == k0 || k2 == k1) continue;
  for (k3 = 0; k3 < 52; ++k3) { if (k3 == k0 || k3 == k1 || k3 == k2) continue;
  for (k4 = 0; k4 < 52; ++k4) { if (k4 == k0 || k4 == k1 || k4 == k2 || k4 == k3) continue;

            k[0] = (k0 % 13) + 2;
            k[1] = (k1 % 13) + 2;
            k[2] = (k2 % 13) + 2;
            k[3] = (k3 % 13) + 2;
            k[4] = (k4 % 13) + 2;
            if (is_straight_bit(k))
              ++suoria;
  }}}}}
  t2 = clock();
  printf("Suoria     : %d kpl (oikea arvo 1228800)\n", suoria);
  printf("Aikaa kului: %.1fs\n", (t2 - t1) / (float)CLOCKS_PER_SEC);

  
  return 0;
}

/*
  Parametrina 5 pelikortin numeroarvoa k, 2..14 (ei välttämättä
  numerojärjesteyksessä).

  Palauttaa 1, jos numeroarvot voidaan järjestää siten, että
  ne muodostavat suoran (esim. 4,5,6,7,8).

  Huom! Ässää (arvo 14) voidaan käyttää suorissa myös arvona 1
  (esim. 1,2,3,4,5).
*/
extern inline int is_straight(int *k) {
  // TODO
  // PERFORMANCE: 15.7s.
  // sort the cards from smallest to greatest. (bubble sort)
  int i, j;

  for (i = 0; i < 5 - 1; i++)
    for (j = 0; j < 5 - i - 1; j++)
      if (k[j] > k[j + 1]) {
        int temp = k[j];
        k[j] = k[j + 1];
        k[j + 1] = temp;
  }

  // check for "small" straight with ace
  if(k[0] == 2 && k[1] == 3 && k[2] == 4 && k[3] == 5 && k[4] == 14) return 1;

  // check if the values are adjacent
  if (k[1] == k[0] + 1
      && k[2] == k[1] + 1
      && k[3] == k[2] + 1
      && k[4] == k[3] + 1)
  {
    return 1;
  }
  else return 0;
}

extern inline int is_straight_bit(int* k) {
  unsigned h = 0;

  h |= 0x1 << (k[0] - 2);
  h |= 0x1 << (k[1] - 2);
  h |= 0x1 << (k[2] - 2);
  h |= 0x1 << (k[3] - 2);
  h |= 0x1 << (k[4] - 2);

  switch(h) {
    case STRAIGHT_0:
      return 1;
      break;
    case STRAIGHT_1:
      return 1;
      break;
    case STRAIGHT_2:
      return 1;
      break;
    case STRAIGHT_3:
      return 1;
      break;
    case STRAIGHT_4:
      return 1;
      break;
    case STRAIGHT_5:
      return 1;
      break;
    case STRAIGHT_6:
      return 1;
      break;
    case STRAIGHT_7:
      return 1;
      break;
    case STRAIGHT_8:
      return 1;
      break;
    case STRAIGHT_9:
      return 1;
      break;
    default:
      return 0;
      break;
  }
}



















