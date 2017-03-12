/* ========================================================================================= */
/* File: countersTest.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file is used to test the counters.c  
 After running the file use valgrind --leak-check=full --show-leak-kinds=all ./countersTest to 
check that no memory is leaked. 

Expected Output: 
2
1
1
3
3
=========================================================================================== */
#include <stdio.h>
#include "counters.h"
#include <stdlib.h>

int main(int argc, char **argv){
   counters_t *counters= counters_new();
   counters_add(counters, 2);
   counters_add(counters, 1);
   printf("%d\n",counters->head->key);
   printf("%d\n",counters->tail->key);
   printf("%d\n",counters->tail->count);
   counters_add(counters, 3);
   counters_add(counters, 3);
   counters_add(counters, 3);
   counters_add(counters, 4);
   printf("%d\n",counters->tail->count);
   int c1 =  counters_get(counters, 3);
   printf("%d\n", c1);
   printf("%d\n", counters->tail->key);
   printf("%d\n", counters->tail->prev->key);
   counters_add(counters, 5);
   counters_add(counters, 6);
   counters_add(counters, 7);
   counters_delete(counters);
}
