/* ========================================================================================= */
/* File: bagTest.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file is used to test the bag.c  
 After running the file use valgrind --leak-check=full --show-leak-kinds=all ./bagTest 
delete_bag doesn't free every node because when nodes are extracted from the bag, in order to return the extracted nodes, they are not freed. Hence delete_bag only frees all the nodes that are still in the bag.
It is the user's responsibility to free the extracted nodes. 

Expected Output: 
[firstData]
[secondData]
[firstData]
[secondData]
The bag is empty.

 LEAK SUMMARY:
             definitely lost: 24 bytes in 1 blocks
	     indirectly lost: 24 bytes in 1 blocks
	     possibly lost: 0 bytes in 0 blocks
	     still reachable: 0 bytes in 0 blocks
	     suppressed: 0 bytes in 0 blocks
=========================================================================================== */
#include <stdio.h>
#include<stdlib.h>
#include "bag.h"
#include "bag.c"

int main(int argc, char **argv){
   bag_t *bag = bag_new();

   char *data1 = "firstData";
   bag_insert(bag, (void *)data1);
   char *d1 = (char*)bag->head->data;
   printf("[%s]\n",d1);

   char *data2 = "secondData";
   bag_insert(bag, (void *)data2);
   char *d2 = (char*)bag->head->data;
   printf("[%s]\n",d2);

   BagNode *extractedNode1 = bag_extract(bag);
   char *d3 = (char*)extractedNode1->data;
   printf("[%s]\n",d3);

   BagNode *extractedNode2 = bag_extract(bag);
   char *d4 = (char*)extractedNode2->data;
   printf("[%s]\n",d4);

   bag_extract(bag);
    bag_delete(bag);
}


