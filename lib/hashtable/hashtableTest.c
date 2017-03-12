/* ========================================================================================= */
/* File: hashtableTest.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file is used to test the counters.c  
 After running the file use valgrind --leak-check=full --show-leak-kinds=all ./hashtableTest to 
check that no memory is leaked. 
Expected Output: 
[firstData]
the key is null
[thirdData]

  total heap usage: 10,002 allocs, 10,002 frees, 321,032 bytes allocated
  All heap blocks were freed -- no leaks are possible
=========================================================================================== */
#include <stdio.h>
#include<stdlib.h>
#include "hashtable.h"

int main(int argc, char **argv){
   hashtable_t *ht = hashtable_new();;

   char *key1 = "firstKey";
   char *data1 = "firstData";
   hashtable_insert(ht, key1, (void *)data1);
   char *key2  = "secondKey";
   char *data2 = "secondData";
   hashtable_insert(ht, key2, (void *)data2);
   char *key3 = "thirdKey";
   char *data3 = "thirdData";
   hashtable_insert(ht, key3, (void *)data3);

   char *d1 =  hashtable_find(ht, key1);
   printf("[%s]\n",d1);

   if(ht->table[8]->key == NULL) {
     printf("the key is null\n");
   };

   char *d2 =  hashtable_find(ht,key3);
   printf("[%s]\n",d2);

   hashtable_delete(ht);
}
