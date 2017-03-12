                                  
/* ========================================================================================= */
/* File: bag.c                                                                                            
 * Project: Tiny Seach Web Engine       
 * Author: Ying Liu                  
 * Date: 2/9/2017
 * The file implements a generic queue with generic data in each node.                                
=========================================================================================== */
#include<stdio.h>
#include<stdlib.h>
#include "bag.h"
#include<stdbool.h>


// Allocate memory for the bag and create a new empty bag
bag_t *bag_new(void) {
  bag_t *bag = malloc(sizeof(bag_t));
  bag->head = NULL;
  bag->tail = NULL;
  return bag;
}


// Insert data in the bag
void bag_insert(bag_t *bag, void *data) {
  // Check if the bag is null
  if (bag == NULL) {
    printf("The bag is null.\n");
    return;
  }
  // Create a new BagNode and store the data
  BagNode *newNode;
  newNode = malloc(sizeof(BagNode));
  newNode->data = data;
  // If the bag is empty, then create the head
  if (bag->head == NULL) {
    bag->head = newNode;
    bag->tail = newNode;
    bag->head->next = bag->tail;
    bag->tail->prev = bag->head;
    bag->tail->next = NULL;
    bag->head->prev = NULL;
  }
  // Insert at the head and update the head postion
  else {
    newNode->next = bag->head;
    bag->head->prev = newNode;
    bag->head = newNode;
    newNode->prev = NULL;
  }

}

// Extract a BagNode at the tail and return the BadNode
void *bag_extract(bag_t *bag) {
  if (bag == NULL) {
    printf("The bag is null.\n");
    return NULL;
  } else if (bag->head == NULL) {
    printf("The bag is empty.\n");
    return NULL;
  } else {
    BagNode *lastNode;
    lastNode = bag->tail;
    if (bag->head == bag->tail) {
      bag->head = NULL;
      bag->tail = NULL;
    } else {
      bag->tail = bag->tail->prev;
      bag->tail->next = NULL;
    }
    return lastNode;
  }
  
}


// Delete the entire bag and free the memory so that there will be no memory leak.
bool bag_delete(bag_t *bag) {
   if (bag == NULL) {
     printf("The bag is null.\n");
     return false;
   }
   if(bag->head != NULL && bag->head->next != NULL) {
     BagNode *cur;
     cur = bag->head;
     while (cur->next != NULL) {
        BagNode *nextNode;
        nextNode = cur->next;
         cur->next = nextNode->next;
         nextNode->data = NULL;
         free(nextNode);
         nextNode = NULL;
      }
     free(bag->head);
   } else if (bag->head != NULL){
     free(bag->head);
   }

   free(bag);
   bag = NULL;
   return true;
}


// Return true if the bag is empty
bool is_empty(bag_t *bag) {
  if(bag->head == NULL){
    return true;
  } else {
    return false;
  }

}


// Iterate over all items in bag (in undefined order); call itemfunc for each item, passing (arg, data).
 
void bag_iterate(bag_t *bag, void (*itemfunc)(void *arg, void *data), void *arg) {
  if (bag == NULL || itemfunc == NULL) {
    return; // bad bag or null function
  } else {
    // scan the bag
    for (BagNode *node = bag->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->data);
    }
  }
  return;
}
