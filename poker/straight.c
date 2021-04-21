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

extern inline int is_straight(int *k);

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
            if (is_straight(k))
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





















