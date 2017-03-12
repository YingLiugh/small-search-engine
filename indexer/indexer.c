 /* ======================================================================= */
/* File: indexer.c 
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/15/2017
 *
=========================================================================== */

#define _DEFAULT_SOURCE
#include <stdio.h>                           
#include <string.h>
#include <sys/types.h>
#include <sys/dir.h>
#include "../lib/counters/counters.h"
#include "../lib/hashtable/hashtable.h"
#include <stdlib.h>
#include "../common/file.h"
#include "../common/word.h"
#include "../common/index.h"

char *webPageDirectory;
char *indexFileName;
hashtable_t *invertedIndex;
struct dirent **nameList;
int n;
bool indextable_delete(hashtable_t *ht);

int main(int argc, char *argv[]) {
   /* Check command line arguments */
   // Must have 3 arguments
   if (argc != 3) {
      fprintf(stderr, "Two arguments are required.\n");
      return 1;
    } else {
	// Check if the webPageDirectory is a valid exisitng directory.
       webPageDirectory = argv[1];	 
       n = scandir(webPageDirectory, &nameList, NULL, alphasort);
       if(n < 0) {
	 fprintf(stderr,"The directory is not valid.\n");
	  return 1;
       }
   }
   indexFileName = argv[2];
   
   /* Initialize data strucures */
   
   invertedIndex = createIndex();
   char *fileContent;
   char *fullFileName;
   int fileID;
   char *word;
   for (int i = 0; i < n; i++) {
     int c1;
     int c2;
     if ((c1 = strcmp(nameList[i]->d_name, ".")) != 0 && (c2 = strcmp(nameList[i]->d_name, "..")) != 0) {
        fullFileName = malloc((strlen(nameList[i]->d_name) + strlen(webPageDirectory) + 2) * sizeof(char));
        sprintf(fullFileName, "%s/%s", webPageDirectory, nameList[i]->d_name);

	FILE *file = fopen(fullFileName, "r");

        fileContent = readfile(file);
	NormalizeWord(fileContent);
       	fileID = atoi(nameList[i]->d_name);

	rewind(file);
	int pos = 0;
	int lineCount = 0;
	int c;
	 c = fgetc(file);
	 
	// Ignore the first two lines in the file, which are the url and the url id
	while (lineCount != 2 && !feof(file)) {
	  if (c == '\n'){
	    lineCount++;
	  }
	  c = fgetc(file);
       	}    
       	// Set the postion to start at the third line  
       	pos = (int) ftell(file);
	
	// Read the words from the file.	
	while((pos = GetNextWord(fileContent, pos, &word)) > 0) {
	  // String copy to avoid errors.
	  char *wordCpy =  malloc((strlen(word) + 1) * sizeof(char));
	  strcpy(wordCpy, word);

	  // Update the invertedIndex.
	  updateIndex(wordCpy, fileID, invertedIndex);
    
	  free(word);
	
	}
         
       	free(fullFileName);
	free(fileContent);
	
	fclose(file);
       
     }
    
     free(nameList[i]);
    
     // Write the indices in the output file
     saveIndex(invertedIndex, indexFileName);
     
   }
   free(nameList);         
 
  
   // Delete the hashtable and its contents.
   //indextable_delete(invertedIndex);
}

bool indextable_delete(hashtable_t *ht) {
  if (ht == NULL) {
    printf("The hashtable is null.\n");
    return false;
  }
  for (int i = 0; i < ht->size; i++) {
    HashTableNode *head;
    head = ht->table[i];
    if(head != NULL) {
      HashTableNode *cur;
      cur = head;
      while (cur->next != NULL) {
         HashTableNode *nextNode;
         nextNode = cur->next;
         cur->next = nextNode->next;
         // Free each counter list in the data                                                                    
         counters_t *counterList = nextNode->data;
         counters_delete(counterList);
         counterList = NULL;
         nextNode->data = NULL;
         nextNode->key = NULL;

         free(nextNode);
         nextNode = NULL;
      }
      counters_t *headCounterList = head->data;
      if(headCounterList != NULL){
         counters_delete(headCounterList);
         headCounterList = NULL;
       }
      head->data = NULL;
      head->key = NULL;
      free(head);
      head = NULL;
    }
  }

  free(ht);
  ht = NULL;
  return true;

}
