/* ========================================================================== */
/* File: counters.h
 * Project: Tiny Search Web Engine
 * Component name: Crawler
 *
 * This file contains the definitions for a  doubly-linked list with key and count in each node. 
 *
  ======================================================================== */

#ifndef COUNTERS_H
#define COUNTERS_H

typedef struct CounterNode {
  struct CounterNode *prev;
  struct CounterNode *next;
  int key;
  int count;

} CounterNode;

typedef struct counters_t {
  struct CounterNode *head;
  struct CounterNode *tail;
} counters_t;

// -------------------- Macros
counters_t *counters_new(void);   // create a new empty data structure.
void counters_add(counters_t *ctrs, int key);  // if key exists, increment its counter; otherwise add key and set its counter to 1.
int counters_get(counters_t *ctrs, int key); // return the current value of the counter for key, or 0 if key is not found.
void counters_delete(counters_t *ctrs); // delete the whole data structure and its contents.

void counters_set(counters_t *ctrs, int key, int count);  // set value of the counter indicated by key. If the key does not yet exist, create a counter for it and initialize its counter value to 'count'. NULL counters is ignored.

void counters_iterate(counters_t *ctrs, void (*itemfunc)(void *arg, const int key, int count), void *arg); // Iterate over all counters in the set. call itemfunc for each item, with (arg, key, count).




#endif
