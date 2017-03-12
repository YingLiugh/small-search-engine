/* ========================================================================== */
/* File: list.h
 * Project: Tiny Search Web Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a generic doubly-linked list with key and data in each node. 
 *
 ============================================================================= */

#include<stdbool.h>
#ifndef LIST_H
#define LIST_H

typedef struct ListNode { 
     struct ListNode *prev;  // pointer to the previous node
     struct ListNode *next;  // pointer to next node
     void *data;	     // pointer to generic data
     char *key;              // pointer to the key 
} ListNode;

typedef struct list_t {
     ListNode *head;         // the first node of the list
     ListNode *tail;	     // the last node of the list
  
} list_t; 

// -------------------- Macros

list_t *list_new(void);       // create a new empty list data structure
void *list_find(list_t *list, char *key);  // return data for the given key
bool list_insert(list_t *list, char *key, void *data);  // return false if key already exists, and true if new item inserted 
bool list_delete(list_t *list);          // delete the whole data structure 
bool is_list_empty(list_t *list);            // check if the list is empty 
#endif 
  	
