/* ========================================================================================= */
/* File: counters.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file implements a doubly linked list with key and count in each ndoe 
=========================================================================================== */
#include <stdio.h>
#include "counters.h"
#include <stdlib.h>


// Allocate memory for the list and create a new empty list
counters_t *counters_new(void) {
   counters_t *counters;
   CounterNode *node;
   counters = malloc(sizeof(counters_t));
   node = malloc(sizeof(CounterNode));
   node->key = 0;
   node->count = 0;
   node->prev = NULL;
   node->next = NULL;
   counters->head = node;
   counters->tail = node;
   return counters;
}
// Increase the count given a key if the key is already in the list.
// If the key doesn't exist in the list then create new node and initialize the count as 1
void counters_add(counters_t *ctrs, int key) {
   if (ctrs == NULL) {
    printf("The counter list is null \n");
    return;
   } else if (ctrs->head->key == 0) {
     ctrs->head->key = key;
     ctrs->head->count = 1;
     ctrs->head->next = ctrs->tail;
     ctrs->tail->prev = ctrs->head;
     ctrs->tail->next = NULL;
   } else {
     CounterNode *cur = ctrs->head;
     while(cur != NULL && cur->key != 0) {
       if (cur->key == key) {
         cur->count = cur->count + 1;
	 return;
       }
       cur = cur->next;
     }
     CounterNode *newNode;
     newNode = malloc(sizeof(CounterNode));
     newNode->key = key;
     newNode->count = 1;
     newNode->next = NULL;
     
     ctrs->tail->next = newNode;
     newNode->prev = ctrs->tail;
     ctrs->tail = newNode;
   }
}

// Find the given key in the list and return the number of count
int counters_get(counters_t *ctrs, int key) {
   if (ctrs == NULL) {
      printf("The counter list is null \n");
      return 0;
   } else{   
      CounterNode *cur = ctrs->head;
      while(cur != NULL) {
        if (cur->key == key) {
            return cur->count;
	}
         cur = cur->next;
      }
      return 0;
   }
}

// Delete the entire counters list. 
void counters_delete(counters_t *ctrs) {
   if (ctrs == NULL) {
	printf("The counters_t is null.\n");
 	return;
   }
   if(ctrs->head != NULL && ctrs->head->next != NULL) {
     CounterNode *cur;
     cur = ctrs->head;
     while (cur->next != NULL) {
         CounterNode *nextNode;
         nextNode = cur->next;
         cur->next = nextNode->next;
         nextNode->count = 0;
         nextNode->key = 0;
         free(nextNode);
         nextNode = NULL;
      }
     free(ctrs->head);
   } else if (ctrs->head != NULL){
     free(ctrs->head);
   }

   free(ctrs);
   ctrs = NULL;
}

// Set value of the counter indicated by key.
void counters_set(counters_t *ctrs, int key, int count) {
  if (ctrs == NULL) {
     printf("The counter set is null.\n");
     return;
  } else if (ctrs->head->key == 0) {
      ctrs->head->key = key;
      ctrs->head->count = count;

      //  ctrs->head->next = ctrs->tail;
      // ctrs->tail->prev =  ctrs->head;
    /*     CounterNode *newNode;
     newNode = malloc(sizeof(CounterNode));
     newNode->key = key;
     newNode->count = count;

     newNode->next = ctrs->head;
     ctrs->head->prev = newNode;
     newNode->prev = NULL;
     ctrs->head = newNode;
    */
   } else {
     CounterNode *cur = ctrs->head;
     while(cur != NULL && cur->key != 0) {
       // If the key is contained in the counter set, then set its count.
       if (cur->key == key) {
           cur->count = count;
           return;
       }
       cur = cur->next;
     }
     
     // If the key is not contained in the counter set, create a new CounterNode and initialize its count.
     CounterNode *newNode;
     newNode = malloc(sizeof(CounterNode));
     newNode->key = key;
     newNode->count = count;

     //     ctrs->tail->next = newNode;
     // newNode->prev = ctrs->tail;
     //ctrs->tail = newNode;
     newNode->next = ctrs->head;
     ctrs->head->prev = newNode;
     ctrs->head = newNode;
     ctrs->head->prev = NULL;
     
  }

}

// Iterate over all counters in the set.
void counters_iterate(counters_t *ctrs, void (*itemfunc)(void *arg, const int key, int count), void *arg) {    
    if (ctrs == NULL || itemfunc == NULL) {
    return; // bad counter set or null function
  } else {
    // scan the counters 
    for (CounterNode *node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->count);
    }
  }
  return;

}
