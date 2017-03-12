/* ========================================================================================= */
/* File: list.c 
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 * The file implements a  generic doubly linked list with key and generic data in each ndoe 
=========================================================================================== */
#include<stdbool.h>
#ifndef HASHTABLE_H
#define HASHTABLE_H
#define MAX_HASH_SLOT 10000    // The number of buckets in the hashtable

typedef struct HashTableNode {
   char *key;
   void *data;
   struct HashTableNode *next;
} HashTableNode;

typedef struct hashtable_t {
  HashTableNode  *table[MAX_HASH_SLOT];
  int size;
} hashtable_t;

// -------------------- Macros

hashtable_t *hashtable_new(void);     // create a new empty hash table data structure with 10000 slots.
void *hashtable_find(hashtable_t *ht, char *key); // return data for the given key, or NULL if not found.
bool hashtable_insert(hashtable_t *ht, char *key, void *data);  // return false if key already exists, and true if new item was inserted.
bool hashtable_delete(hashtable_t *ht); // delete the whole data structure and its contents.
unsigned long JenkinsHash(const char *str, unsigned long mod); // hashfunction 


#endif

