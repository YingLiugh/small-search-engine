#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../common/index.h"
#include "../common/index.c"
// indexTest.c is used to test index.c. index.c builds the inverted index and saves into a file.
// Usage: gcc -Wall -pedantic -std=c11 -ggdb -o index indexTest.c ../lib/counters/counters.c ../lib/hashtable/hashtable.c

int main(int argc, char **argv){
  hashtable_t *ht;
  ht = createIndex();
  char *word1;
  word1 = "firstWord";
  char *word2;
  word2 = "secondWord";
  char *word3;
  word3 = "thirdWord";

  int fid1 = 1;
  int fid2 = 2;
  int fid3 = 3;
  printf("running\n");
  updateIndex(word1, fid1, ht);
  updateIndex(word1, fid1, ht);
  updateIndex(word1, fid2, ht);
  updateIndex(word2, fid1, ht);
  updateIndex(word2, fid1, ht);
  updateIndex(word3, fid1, ht);
  updateIndex(word3, fid2, ht);
  updateIndex(word3, fid3, ht);
  updateIndex(word3, fid1, ht);
  updateIndex(word3, fid2, ht);
  updateIndex(word3, fid3, ht);
  updateIndex(word3, fid3, ht);

  char *output;
  output = "indexTestOutput.dat";
  saveIndex(ht, output);
 
}



