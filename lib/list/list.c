/* ========================================================================================= */
/* File: list.c 
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file implements a  generic doubly linked list with key and generic data in each ndoe 
=========================================================================================== */
#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include<stdbool.h>
#include <string.h>

// Allocate memory for the list and create a new empty list
struct list_t *list_new(void) {
   struct list_t *list = malloc(sizeof(struct list_t));
   list->head  = NULL;
   list->tail = NULL;
   return list;
}

// Given a key return the data stored in the linked list
void *list_find(list_t *list, char *key) {
  // Check if it is a null 
  if (list == NULL) {
    printf("The list is null.\n");
    return NULL;
  }
  // Traverse the linked list, if there is a match then return the data.
  // If there is no match then return null.
  ListNode *cur = list->head;
  while (cur != NULL && cur->key != NULL) {
    if (strcmp(cur->key, key) == 0) {
       return cur->data;
     }
     cur = cur->next; 
  }
  return NULL;
}

// Insert a node in the list, return true if succeeded and false if not suceeded.
bool list_insert(list_t *list, char *key, void *data) {
  // Check if the list is null
  if (list == NULL) {
    printf("The list is null.\n");
    return false;
  }
  // Create a new ListNode
  struct ListNode *newNode = malloc(sizeof(struct ListNode));
  // Store the key and data information in the ListNode
  newNode->key = key;
  newNode->data = data;

  // If the list is empty, then create the head
  if (list->head == NULL) {
       list->head = newNode;
       list->tail = newNode;
       list->head->next = list->tail;
       list->tail->prev = list->head;
       list->tail->next = NULL;
       list->head->prev = NULL;
  } else{
    // Insert at the head and update the head postion
       newNode->next = list->head;
       list->head->prev = newNode;
       list->head = newNode;
       newNode->prev = NULL;      
  }
  return true;
}

// Delete the entire list and free the memory so that there will be no memory leak.
// Return true if succeeded.
bool list_delete(list_t *list) {
   if (list == NULL) {
     printf("The list is null.\n");
     return false;
   }
   if(list->head != NULL && list->head->next != NULL) {
     ListNode *cur;
     cur = list->head;
     while (cur->next != NULL) {
        ListNode *nextNode;
       nextNode = cur->next;
         cur->next = nextNode->next;
         nextNode->data = NULL;
	 nextNode->key = NULL;
         free(nextNode);
	 nextNode = NULL;
      }
     free(list->head);
   } else if (list->head != NULL){
     free(list->head);
   } 
   
   free(list);
   list = NULL;
   return true;
}

// Return true if the list is empty
bool is_list_empty(list_t *list) {
  if (list->head == NULL){
    return true;
  } else {
    return false;
  }
}

//  Iterate over all items in bag (in undefined order): call itemfunc for each item, passing (arg, data).
 
void list_iterate(list_t *list, void (*itemfunc)(void *arg, const char *key, void *data),void *arg) {
  if (list == NULL || itemfunc == NULL) {
    return; // bad list or null function
  } else {
    // scan the list
    for (ListNode *node = list->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->data);
    }
  }
  return;
}


