/* ========================================================================================= */
/* File: listTest.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file is used to test the list.c  
 After running the file use valgrind --leak-check=full --show-leak-kinds=all ./listTest to 
check that no memory is leaked. 
Expected Output: 
Inserted  firstKey, firstData.
The key of the head of the list is firstKey.
The data of the head of the list is firstData.
Inserted  secondKey, secondData.
The key of the head of the list is secondKey.
The key of the tail of the list is firstKey.
The data of the head of the list is secondData.
The data of the tail of the list is firstData.
Inserted  thirdKey, thirdData.
The key of the head of the list is thirdKey.
The data of the head of the list is thirdData.
Given secondKey, list_find finds secondData
Given fourthKey, list_find finds (null) 

 total heap usage: 5 allocs, 5 frees, 1,136 bytes allocated
 All heap blocks were freed -- no leaks are possible
=========================================================================================== */

#include <stdio.h>
#include<stdlib.h>
#include "list.h"
#include "list.c"

int main(int argc, char **argv){
   list_t *list = list_new();

   char *key1 = "firstKey";
   char *data1 = "firstData";
   list_insert(list, key1, (void *)data1);
   printf("Inserted  %s, %s.\n", key1, data1);
   printf("The key of the head of the list is %s.\n",list->head->key);
   char *d1 = (char*)list->head->data;
   printf("The data of the head of the list is %s.\n",d1);

   char *key2 = "secondKey";
   char *data2 = "secondData";
   list_insert(list, key2, (void *)data2);
    printf("Inserted  %s, %s.\n", key2, data2);
   printf("The key of the head of the list is %s.\n",list->head->key);
   printf("The key of the tail of the list is %s.\n",list->tail->key);
   char *d2 = (char*)list->head->data;
    printf("The data of the head of the list is %s.\n",d2);
     char *d2_t = (char*)list->tail->data;
    printf("The data of the tail of the list is %s.\n",d2_t);

   char *key3 = "thirdKey";
   char *data3 = "thirdData";
   list_insert(list, key3, (void *)data3);
    printf("Inserted  %s, %s.\n", key3, data3);
    printf("The key of the head of the list is %s.\n",list->head->key);
   char *d3 = (char*)list->head->data;
     printf("The data of the head of the list is %s.\n",d3);

   char *key4 = "fourthKey";
   char *f1 = (char*)list_find(list, key2);
   printf("Given secondKey, list_find finds %s\n",f1);
   char *f2 = (char*)list_find(list, key4);
    printf("Given fourthKey, list_find finds %s \n",f2);

   list_delete(list);

}
