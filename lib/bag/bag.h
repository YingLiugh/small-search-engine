/* ========================================================================================= */
/* File: bag.h 
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * This file contains the definitions for a generic doubly-linked list with data in each node. 
=========================================================================================== */
#include<stdbool.h>
#ifndef BAG_H
#define BAG_H

typedef struct BagNode {
  struct BagNode *prev;
  struct BagNode *next;
  void *data;
} BagNode;

typedef struct bag_t {
  BagNode *head;
  BagNode *tail;  	
} bag_t;

// -------------------- Macros

bag_t *bag_new(void);      // create a new empty bag data structure
void bag_insert(bag_t *bag, void *data);  // add a new item to the bag.
void *bag_extract(bag_t *bag); // remove any item from the bag and return it to the caller, or NULL if bag is empty.
bool bag_delete(bag_t *bag); // delete the whole data structure and its contents
bool is_empty(bag_t *bag);  // return true if the bag is empty
#endif
