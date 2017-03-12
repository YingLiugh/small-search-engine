/* ========================================================================================= */
/* File: hashtable.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file implements a hashtable 
=========================================================================================== */
#include <stdio.h>
#include<stdlib.h>
#include "hashtable.h"
#include <stdbool.h>
#include <string.h>

// Allocate memory and create a hashtable
hashtable_t *hashtable_new(void){
   hashtable_t *hashtable;
   hashtable = malloc(sizeof(hashtable_t));
   hashtable->size = MAX_HASH_SLOT;
   // Allocate memory for all the HashTableNodes in the hashtable
   for (int i = 0; i < MAX_HASH_SLOT; i++) {
     HashTableNode *node;
     node = malloc(sizeof(HashTableNode));
     node->key = NULL;
     node->data = NULL;
     node->next = NULL;
     hashtable->table[i] = node;
   }
   return hashtable;
}

// Look up the hashtable and return the data given the key 
void *hashtable_find(hashtable_t *ht, char *key) {
   HashTableNode *searchNode;
   searchNode = ht->table[JenkinsHash(key, ht->size)];
   if (searchNode->key == NULL) {
     return NULL;
   } else{ 
     if (strcmp(searchNode->key, key) == 0) {
        return searchNode->data; 
     } else {
       while ((searchNode != NULL) && (strcmp(searchNode->key, key) != 0)) {
             searchNode = searchNode->next;
	     if (searchNode != NULL && (strcmp(searchNode->key, key) == 0)) {
	       return searchNode->data;
	      }
	}
	return NULL;
     }
   }
}

// Return true if insertion in hashtable suceeds and false otherwise 
bool hashtable_insert(hashtable_t *ht, char *key, void *data) {
   HashTableNode *searchNode;
   searchNode = ht->table[JenkinsHash(key, ht->size)];
   if (searchNode->key == NULL) {
     searchNode->key = key;
     searchNode->data = data; 
     return false;
   } else {
     while (searchNode->next != NULL) {
	    searchNode = searchNode->next;
     }
     HashTableNode *newNode;
     newNode = malloc(sizeof(HashTableNode));
     newNode->key = key;
     newNode->data = data;
     newNode->next = NULL;
     searchNode->next = newNode;
     return true;
   }
}


// Return true if the entire hashtable id freed 
bool hashtable_delete(hashtable_t *ht) {
  if (ht == NULL) {
    printf("The hashtable is null.\n");
    return false;
  }
  for (int i = 0; i < ht->size; i++) {
    HashTableNode *head;
    head = ht->table[i];
    if(head != NULL && head->next != NULL) {
      HashTableNode *cur;
      cur = head;
      while (cur->next != NULL) {
         HashTableNode *nextNode;
         nextNode = cur->next;
         cur->next = nextNode->next;
         nextNode->data = NULL;
         nextNode->key = NULL;
         free(nextNode);
         nextNode = NULL;
      }
      free(head);
      head = NULL;
    } else if (head->next == NULL){
      free(head);
   }
   
  }
  free(ht);
   ht = NULL;
  return true; 
}

// Hash function that returns the index for a particular string 
unsigned long JenkinsHash(const char *str, unsigned long mod)
{
    if (str == NULL)
      return 0;
    size_t len = strlen(str);
    unsigned long hash, i;
    for (hash = i = 0; i < len; ++i)
    {
        hash += str[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash % mod;
}


// Iterate over all items in hashtable (in undefined order): call itemfunc for each item, with (arg, key, data).
 
void hashtable_iterate(hashtable_t *ht, void (*itemfunc)(void *arg, const char *key,void *data), void *arg) {
    if (ht == NULL || itemfunc == NULL) {
      return; // bad hashtable or null function
    } else {
    // scan the hashtable
      for (int i = 0; i < ht->size; i++) {
        HashTableNode *node = ht->table[i];
        (*itemfunc)(arg, node->key, node->data);
        for (HashTableNode *nextNode = node->next; nextNode != NULL; nextNode = nextNode->next) {
	  (*itemfunc)(arg, nextNode->key, nextNode->data);
        }
      }
    }
  return;
}



 
