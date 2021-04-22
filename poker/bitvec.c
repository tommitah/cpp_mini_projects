#include <stdio.h>
#include <stdlib.h>

int main() {
  unsigned h = 0;
  int k[5] = { 2, 4, 5, 3, 6 };

  h |= 0x1 << (k[0] - 2);

  printf("%d ", h);

  return 0;
}


/*#define WORDSIZE 32*/
/*#define BITS_WS  5*/
/*#define MASK     0x1f*/

/*int init_bv(int** bv, int val) {*/
  /**bv = calloc(val/WORDSIZE + 1, sizeof(int));*/
  /*return *bv != NULL;*/
/*}*/

/*void set(int bv[], int val) {*/
  /*bv[val>>BITS_WS] |= (1 << (val & MASK));*/
/*}*/

/*int member(int bv[], int val) {*/
  /*return bv[val>>BITS_WS] & (1 << (val & MASK));*/
/*}*/

/*int main() {*/
  /*int *bv, i;*/
  /*int s1[] = {32, 5, 0};*/
  /*int s2[] = {32, 4, 5, 0};*/
  
  /*init_bv(&bv, 32);*/
  /*for (i = 0; s1[i]; i++)*/
    /*set(bv, s1[i]);*/
  /*for (i = 0; s2[i]; i++)*/
    /*if(member(bv, s2[i]))*/
      /*printf("%d ", s2[i]);*/

  /*free(bv);*/

  /*return 0;*/
/*}*/
