/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * The index is keyed by words (strings) and stores counter sets; 
 * each counter set represents the set of documents where that word 
 * appeared, and the number of occurrences of that word in each document.
 * 
 * Ying Liu, Winter 2017
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdbool.h>
#include "../lib/hashtable/hashtable.h"
#include "../lib/counters/counters.h"

/**************** global types ****************/

// The index is actually a hashtable. 
typedef hashtable_t index_t;

/********** add function prototypes here *********/
//void updateIndex(char *word, int fileID,  index_t *invertedIndex);
//index_t *createIndex();
void saveIndex(index_t *invertedIndex, char *outputFile);
hashtable_t *createIndex();  
void updateIndex(char *word, int fileID,  hashtable_t *invertedIndex);      
#endif // __INDEX_H
