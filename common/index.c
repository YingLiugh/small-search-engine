/* 
 * index - a set of functions for creating, saving, loading the index
 * 
 * See index.h for interface descriptions.
 * 
 * Ying Liu, winter 2017
 */

/*  write your implementation of the functions exposed in index.h   */

#include "index.h"

// Update the invertedIndex hashtable.
void updateIndex(char *word, int fileID,  hashtable_t *invertedIndex){ 
  // If the word does not exist, then create a list of counter pair. 
  if(hashtable_find(invertedIndex, word) == NULL) {
    // Create new counter list.
    counters_t *newCounters;
    newCounters = counters_new();
    // Add the new counter pair with the fileID.
    counters_add(newCounters, fileID);
    // Insert the new counter list into the hashtable as the data of the word.
    hashtable_insert(invertedIndex, word, (void *)newCounters);
    
  } else if(hashtable_find(invertedIndex, word) != NULL) {  // If the word already is in the hashtable, then update the counter list.
    counters_t *counters;
    counters = hashtable_find(invertedIndex, word);
    // Update the counter pair with fileID.
    counters_add(counters, fileID);
  }
  
}

// Create the invertedIndex hashtable.
hashtable_t *createIndex() {
  hashtable_t *invertedIndex;
  invertedIndex = hashtable_new();
  return invertedIndex;
}

// Save the index into an output file
void saveIndex(hashtable_t *invertedIndex, char *outputFile) {
  FILE *output; 
  output = fopen(outputFile, "w");
  // If the output file is valid, then start writing. 
  if(output != NULL){
    // Check each bucket in the hashtable.
    for	(int i = 0; i < MAX_HASH_SLOT; i++) {
      HashTableNode *word = invertedIndex->table[i];
      // If there is a word stored in the bucket,then iterate through the list in the bucket.
      while (word != NULL && word->key != NULL) {
	fprintf(output, "%s ", word->key);
	
        counters_t *counters;
        counters = word->data;
	CounterNode *counterNode;
	counterNode = counters->head;
	
	// Iterate through all the documnet id and counts for the word.
        while (counterNode != NULL && counterNode->key != 0) {
          fprintf(output, "%d %d ", counterNode->key, counterNode->count);
          counterNode = counterNode->next;
	}
	fprintf(output, "\n");
	
	// Go to the next word in the list at this slot. 
        word = word->next;	
      }
    }
  } else {
    fprintf(stderr, "The output file name is not valid.\n");
  }
  printf("finished writing the file.\n");
  fclose(output);
}


