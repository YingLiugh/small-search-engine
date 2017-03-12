/* ======================================================================= */
/* File: querier.c
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/25/2017
 *
 * Input: ./crawler [webPageDirectory] [indexFileName]
 * The requirment of query: 
 *       1.contains no special characters other than alphabets. 
 *       2."and", "or" cannot be the first word. 
 *       3."and", "or" cannot be the last word. 
 *       4."and", "or" cannot appear consecutively in the query
 *
 *
 *Output:: If the query satistifes the syntax, then the output lists the document ids and their urls, scores in descending order.
 
==================================================================================== */

#define _DEFAULT_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h> 
#include "../lib/counters/counters.h"
#include "../lib/hashtable/hashtable.h"
#include "../lib/list/list.h"
#include "../lib/bag/bag.h"
#include <math.h>
#include <stdlib.h>
#include "../common/file.h"
#include "../common/word.h"
#include "../common/index.h"
#include <ctype.h>
//typedef char *multi_tok_t;
// ----------------------- Macros definition
#define MAXSTR 1000
// ----------------------- Structures
typedef struct andsequence {  // andsequence
  int size;
  list_t *andWords;
}andsequence;
typedef struct orsequence {   // orsequence
  int size;
  andsequence **orarray;
}orsequence;
struct dirent **nameList; // Used to check the validity of the directory
// ------------------------ Variables
char *indexFileName;
char *webPageDirectory;	      	
hashtable_t *invertedIndex;	
orsequence *orseq;
// --------------------- Prototypes
bool buildOrsequence(char *input, orsequence *orseq, hashtable_t *ht);       
bool buildAndsequence(char *andWords, orsequence *orseq, int c, hashtable_t *ht);
void scoreIntersection(andsequence *andseq, counters_t *intersectionList);
bool allUnrepeatedWords(list_t *andWordsList);
int scoreUnion(counters_t *unionList, bag_t *intersections);
int compare(const void *s1, const void *s2);
void rank(int res, counters_t *unionList, char *webPageDirectory);
void printResult(int docID, int score, char *webPageDirectory);   
char *strCopy(const char *str);                                   
hashtable_t *buildIndex(char *indexFileName);                                              
int isFile(const char *filePath);   
int main(int argc, char *argv[]) {
  
  /* Check command line arguments */
  // Check the argument number.
    if (argc != 3) {
	fprintf(stderr, "The query program requires two input arguments\n");
	return 1;
     }
    
  // Check validity of arguments.
    
    else {
       	// Check if the indexFile is valid.
       indexFileName = strCopy(argv[2]);
       if(!isFile(indexFileName)){
	   fprintf(stderr, "Please provide an existing file for the indexFile.\n");
	   free(indexFileName);
	   return 1;
        }
       
       // Check if the webPageDirectory is valid.
       webPageDirectory = strCopy(argv[1]);
       int n = scandir(webPageDirectory, &nameList, NULL, alphasort);
       if(n < 0) {
	   fprintf(stderr, "Please provide an existing directory for the webPageDirectory\n");
	   free(webPageDirectory);
	   return 1;
       }
       // Build the inverted index from the index file.
       invertedIndex = buildIndex(indexFileName);
     
       // Start the query search.       
       fprintf(stdout, "Please enter your query:");
       // Fetch the input from stdin.
       char *input = malloc(MAXSTR * sizeof(char));
       
       while(fgets(input, MAXSTR, stdin) != NULL) {
	 int n;
	 n = strlen(input);
	 // If the query is too long, the program exits and provides an error message.
	 if( *(input + n - 1) != '\n'){
	   printf("Sorry.The query is too long. Please provide a query within %d characters.", MAXSTR);
	   return 1;
	 }
	 
	 // Replace new line with null terminator.
	 *(input + n - 1) = '\0';
	
	 // Convert all characters to lowercase.
	 char lowerInput[n + 1];
	 strcpy(lowerInput, input);
	 
	 for (int k = 0; k < n; k++) {
	   if((lowerInput[k] >= 'a' && lowerInput[k] <= 'z' )||(lowerInput[k] >= 'A' && lowerInput[k] <= 'Z' )) {
	      lowerInput[k] = tolower(lowerInput[k]);
	   } else if (lowerInput[k] == ' ' || lowerInput[k] == '\0') {
	   } else {
	     printf("Error: Bad character %c. Only alphabets are allowed in query.\n", lowerInput[k]);
	     return 1;
	   }
	 }
	 char *input2 = malloc( (n+1) * sizeof(char));
	 strcpy(input2, lowerInput);
	
	 // Build the orsequences which contain all components separated by "or",
	 orseq = malloc(sizeof(orsequence));
	 if (!buildOrsequence(input2, orseq, invertedIndex)) {
	   fprintf(stderr, "Syntax error: incorrect query format.\n");
	   return 1;
	   // deleteSequence(orsequence);
	   //   fprintf(stdout, "Please enter your query:");
	   // continue;
	 }
	  // Create a docRankings counter list keeping track of each document id and its score.
           counters_t *unionList;
	   unionList = counters_new();
	   bag_t *intersections;
	   intersections = bag_new();
	 
	  // Iterate through all andsequences in the orsequence and build the docRankings with the shared ids and their scores.  
	  for(int i = 0; i < orseq->size; i++) {
	 
	    counters_t *intersectionList;
            intersectionList = counters_new();
     
	    andsequence *andseq = orseq->orarray[i];
	    // Calculate the score for each andsequence.
	    scoreIntersection(andseq, intersectionList);
	    bag_insert(intersections, (void *)intersectionList); 
	    intersectionList = NULL;
	    
	  }
	  // Calculate the final score. 
	  int res;   
	  res = scoreUnion(unionList, intersections);
	  // Rank the document ids based on their scores.
	  rank(res, unionList, webPageDirectory);
	  fprintf(stdout, "Please enter your query:");
       }
    }
}
// Rank all the documnent ids based on their scores.
void rank(int res, counters_t *unionList, char *webPageDirectory) {
  // Get all the scores.
  CounterNode *counter;
  counter = unionList->head;
  CounterNode counters[res];
  
  for(int i = 0; i < res; i++) {
    counters[i].key = counter->key;
    counters[i].count = counter->count;
    counter = counter->next;
  }
  // Use qsort to sort the documents based on their scores.
  qsort(counters, res, sizeof(CounterNode), compare);
  
  printf("Matches %d documents (ranked).\n", res);
  // Iterate through every ranked document and print its information.
  for(int j = 0; j < res; j++) {
    if(counters[j].key != 0){
       printResult(counters[j].key, counters[j].count, webPageDirectory);
    }
  }
  
}
// Print the result of the ranked documents.
void printResult(int docID, int score, char *webPageDirectory) {
  char *path = calloc(strlen(webPageDirectory) + 100, sizeof(char));
  sprintf(path, "%s/%d", webPageDirectory, docID);
  
  FILE *ifp = fopen(path, "r");
  char url[MAXSTR];
   
  // Get the first line from the document which is the url. 
  fgets(url, MAXSTR, ifp);
  fprintf(stdout, "score %d  doc %d : %s\n", score, docID, url);
  fclose(ifp);
}
// A helper function to get the descending order in qsort. 
int compare(const void *s1, const void *s2) {
  int c1  = ((struct CounterNode *)s1)->count;
  int c2 = ((struct CounterNode *)s2)->count;
  if (c1 == c2){
    return 0;
  } else if (c1 > c2) {
    return -1;
  } else {
    return 1;
  }
}
// Calculate the score of a orsequence.
int scoreUnion(counters_t *unionList, bag_t *intersections) {
  if (is_empty(intersections)) {
    return 0;
  }
  BagNode *intersection = intersections->head;
  // For each andsequence in the orsequence, iterate through all the docIds and their scores.
  // If the docIds already exist in the unionList, then just add the score to the exisiting score and update it.
  // Otherwise, insert docId and its socre into the unionList.
  while (intersection != NULL) {    
    counters_t *intersectionScores;
    intersectionScores = intersection->data;
    CounterNode *intersectionScore = intersectionScores->head;
    
    while (intersectionScore != NULL) {
      int docID = intersectionScore->key;
      int score = intersectionScore->count;
      int oldScore = counters_get(unionList, docID);
      if (oldScore == 0){
	counters_set(unionList, docID, score);
      } else {
	counters_set(unionList, docID, oldScore + score);
      }
      intersectionScore = intersectionScore->next;
    }
    
    intersectionScores = NULL;
    intersection = intersection->next;
  }
 
  CounterNode *unionhead;
  unionhead = unionList->head;
  int c = 0;
  while(unionhead != NULL) {
    if (unionhead->key != 0) {
      c++;
    }
    unionhead = unionhead->next;
  }
  return c;
}
// Calculate the scores for the shared doc ids in each word in the andsequence.
void scoreIntersection(andsequence *andseq, counters_t *intersectionList) {
  // Get the first andWord in the andseq.  
  list_t *andWords;
  if (andseq == NULL) {
    return;
  }
  andWords = andseq->andWords;
  
  ListNode *andWord;
  andWord = andWords->head;
  if(andWord == NULL) {
    return;
  }
  counters_t *headWordDocs = andWord->data;
  // Iterate through  each docId in the first andWord.
  if (headWordDocs != NULL) {
    CounterNode *headWordDoc = headWordDocs->head;
    ListNode *nextAndWord;
    nextAndWord = andWord->next;
         
      while (headWordDoc != NULL && headWordDoc->key != 0) {
          int count = 1;
          int min = headWordDoc->count;
      // Iterate through all the other andWords and their docIds and find all the shared docIds.
	 while (nextAndWord != NULL) {
	   counters_t *wordDocs = nextAndWord->data;
	   
	   if (wordDocs != NULL){
	     CounterNode *wordDoc = wordDocs->head;
	
	     while (wordDoc != NULL) {
	     // If the andWord is also in the current docId headWordDoc is in, then increase the count.	       
	       if (wordDoc->key == headWordDoc->key) {
		  count++;
		  
		 if (wordDoc->count < min) {
		   min = wordDoc->count;
		 }
	       }
	       wordDoc = wordDoc->next;
	     }
	     
	   }
	   
	    nextAndWord = nextAndWord->next;
      	   
	 }
	
      // If all andWords share the docId, then get the minimum frequency as its score.
	 if(count == andseq->size) {
	   counters_set(intersectionList, headWordDoc->key, min);
	 }
         nextAndWord = andWord->next;
	 
	 headWordDoc = headWordDoc->next;
       }
  }
  
}
// Build the orsequence which contains an array of andsequences based on the "or"/"OR" separators in the query.
bool buildOrsequence(char *input, orsequence *orseq, hashtable_t *ht){
  char *curWord;
  char *prevWord = NULL; 
  orseq->size = 0;
  char *inputCopy;
  inputCopy = strCopy(input);
  // Check if the last word is "and" or "or".
  char *inputCopy2;
  inputCopy2 = strCopy(input);
  char *p = strrchr(inputCopy2, ' ');
  if (p && *(p + 1)){
    if(strcmp(p + 1, "or") == 0 || strcmp(p + 1, "and") == 0) {
      printf("Error: %s cannot be last. \n", p+1);
      return false;
    };
  }
 
  curWord = strtok(input, " ");
   
  while (curWord != NULL) {
    
    // Check if the first query word is "and" or "or"..
    if ((strcmp("or", curWord) == 0 || strcmp("and", curWord) == 0) && prevWord == NULL) {
      printf("%s cannot be first.\n", curWord);
      free(curWord);
      curWord = NULL;
      return false;
    }
    // Check if the conjunction and disjunction words are consecutive in the query.
    if ((strcmp("or", curWord) == 0 || strcmp("and", curWord) == 0) && (strcmp("or", prevWord) == 0 || strcmp("and", prevWord) == 0)) {
      printf("The syntax cannot have %s and %s consecutively.\n", prevWord, curWord);
      //  free(curWord);
      //  curWord = NULL;
      return false;
    }
    
    if (prevWord != NULL) {
      free(prevWord);
      prevWord = NULL;
    }
    // Update the prevword.
    prevWord = strCopy(curWord);
    
    if (strcmp(curWord, "or") == 0) {
       orseq->size++;
     } else if (strcmp(curWord, "and") == 0) {
     } else{
       NormalizeWord(curWord);
     }
     curWord = strtok(NULL, " ");
  }
  // Initialize the oreseq and update the number of andsequences. 
     orseq->size++;   
     orseq->orarray = calloc(orseq->size, sizeof(andsequence*));
     // Split the input into andsequences separated by "or".
     char *delim = " or";
     char *token;
     token = strstr(inputCopy,delim);
     int index = 0;
     
     // There are no "or"s. 
     if (token == NULL) {
       return buildAndsequence(inputCopy, orseq, index, ht);
     }
     // Take each part separated by "or" and build the corresponding andsequence.
     while (token != NULL) {
       token = strstr(inputCopy, delim);
       
        if (token) 
         *token = '\0';
	
       if(!buildAndsequence(inputCopy, orseq, index, ht)) {
          return false;                                                                                 
       }    	
       inputCopy = token+strlen(delim);
       index++;
    }
     return true;
  
}
// Build andsequence and calculate its score using the index.
bool buildAndsequence(char *andWords, orsequence *orseq, int i, hashtable_t *ht) {
  andsequence *andseq = malloc(sizeof(andsequence));
  orseq->orarray[i] = andseq;
  
  NormalizeWord(andWords);
  
  char *word;
  char *delim = " ";
  word = strstr(andWords,delim);
  list_t *andWordsList;
  andWordsList = list_new();
  andseq->andWords = andWordsList;
  int count = 0;
  // Process the first andWord.
  char *firstWord;
  firstWord = strCopy(andWords);
  counters_t *firstCounters = hashtable_find(ht, firstWord);
  // If the word exists then insert it into the andWordsList.                                                                                
  if (firstCounters != NULL){
      list_insert(andWordsList, firstWord, (void *)firstCounters);
      count++;
  }
   while (word != NULL) {
       word = strstr(andWords, delim);
       
       if (word)
         *word= '\0';
       if ((strcmp(andWords, " ") != 0) && (strcmp(andWords, "and") != 0) && (strcmp(andWords, "") != 0)) {
	 char *andWordCopy;
	 andWordCopy = strCopy(andWords);
	 // Try to find the andWord in the index. 
	 counters_t *counters = hashtable_find(ht, andWordCopy);
	 // If the word exists then insert it into the andWordsList.
	 if (counters != NULL){
	   list_insert(andWordsList, andWordCopy, (void *)counters);
	   count++;
	 }
       }
       andWords = word+strlen(delim);
  }
   if (!allUnrepeatedWords(andWordsList)) {
     printf("Error: there can't be duplicate words.\n");
     return false;
   }
   
   andseq->size = count;
   return true;
 }
// Check if the words are not repeated. 
bool allUnrepeatedWords(list_t *andWordsList) {
  ListNode *curWord = andWordsList->head;
  while (curWord != NULL) {
    ListNode *nextWord;
    nextWord = curWord->next;
    while (nextWord != NULL) {
      if (strcmp(nextWord->key, curWord->key) == 0) {
	printf("the repeated words are %s and %s.\n", nextWord->key, curWord->key);
	return false;
      }
      nextWord = nextWord->next;
    }
    curWord = curWord->next;
  }
  return true;
}
// Construct the invertedIndex. 
hashtable_t *buildIndex(char *indexFileName) {
  hashtable_t *index;
  index = createIndex();
  FILE *indexFile = fopen(indexFileName, "r");
  if (indexFile == NULL) {
    perror("Failed to open the index file.\n");
    exit(1);
  } else {
    // Set the cursor to the start of the file.
    rewind(indexFile);
    int offset = 0;
    int c = fgetc(indexFile);
    int pos = 1;
    
 
    while (!feof(indexFile)) {
      // Restart count at a new line.
      if (c == '\n') {
	// Read a line;
	fseek(indexFile, offset, SEEK_SET);
	char *buffer = calloc((pos - offset + 1), sizeof(char));
	fread(buffer, sizeof(char), (pos - offset), indexFile);
	
	// Get the first token which is the word.
	char *token = strtok(buffer, " ");
	char *word = strCopy(token);
	
	token = strtok(NULL, " ");
       // Iterate through all the tokens in the line.
	while (token != NULL) {
	  char tokenChar;
	  sscanf(token, "%c", &tokenChar);
	  if(tokenChar == '\n') {
	     break;
	   }
	  // Get the docID and the frequency.
	  int docID = atoi(token);
	  token = strtok(NULL, " ");
	  int freq = atoi(token);
	  
	 for(int i = 0; i < freq; i++) {
	    updateIndex(word, docID, index);
	  }
	  token = strtok(NULL, " "); 
	 
	}	
	// Reset the buffer and word;
	free(buffer);
	//free(word);
	offset = pos;
      }
      c =fgetc(indexFile);
      pos++;
	
    }
    fclose(indexFile);
	    
  }
  return index;
}
// strCopy is a function to copy string and suppress error messages. 
char *strCopy(const char *str) {
    int n = strlen(str) + 1;
    char *dup = malloc(n * sizeof(char));
    if(dup != NULL){
      strcpy(dup, str);
      return dup;
    } else {
      return NULL;
    }
   
}
// Check if a file is valid.
int isFile(const char *filePath) {
   struct stat buffer;
   if(!filePath){
     return 0;
   }
   return (!stat(filePath, &buffer) && S_ISREG(buffer.st_mode));
 }
 
