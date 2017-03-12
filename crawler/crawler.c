/* ======================================================================= */
/* File: crawler.c 
 * Project: Tiny Seach Web Engine
 * Author: Ying Liu
 * Date: 2/9/2017
 *
 *Input: ./crawler [seedURL] [fileDirectory] [maxCrawlDepth]
 * Arguments Requirements: 
 *   [seedURL] needs to be in the domain "http://old-www.cs.dartmouth.edu/"
 *   [fileDirectory] needs to be valid.
 *   [maxCrawlDepth] needs to be non-negative integer
 *
 *Output: Webpages that have been crawled will be saved into the directory and with file names in incrementing number
 * The files are in format : 
 *    line 1: current URL
 *    line 2: current depth
 *    line 3: current html contents 
 *The terminal will print out useful information about the crawling process
==================================================================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>  
#include "../common/web.h"
#include "../lib/bag/bag.h"
#include "../lib/hashtable/hashtable.h"
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bag_t *WebPageBag;                    // queue for the curling webpages
hashtable_t *ht;                     // hashtable for the visited pages 
WebPage* currentPage;                 
BagNode *extractedBagNode;            // extracted node containing webpage as the data from the WebPageBag
const char* visitedStatus = "visited";  // message to store in the data of the corresponding webpage in the hashtable
char* seedURL;              // the base url to crawl from
int maxDepth;              
FILE *currentWebPageFile;  // a new file to store the webpage information
int HTMLNumber = 1;    // keep track of the number of webpages saved
WebPage *seedPage;     // the base webpage to crawl from 
char *status;          // the status of each webpage and check it has been visited
char *dir;             // the file directory provided and need to check if it is valid                    

int main(int argc, char *argv[]) {
    // check the number of arguments
    if (argc != 4){
      printf("3 arguments needed [seedURL] [Directory] [Maxdepth]");
      return 1;
    }
    // check if the website is in the allowed domain 
    seedURL = argv[1];  
    if (!IsInternalURL(seedURL)) {
      printf("Incorrect domain");
      return 1;
      }
    // check directory 
    dir = argv[2];
    struct stat s; 
    if (stat(dir, &s)){
      printf("The directory is not valid.");
      return 1;
    } else if (dir[strlen(dir) - 1] != '/') {
      printf("Directory name should end with '/'.\n");
      return 1;
    }
    // check the depth  
    maxDepth = atoi(argv[3]);
    if (maxDepth < 0) {
      printf("Incorrect depth. Please provide a non negative integer.");
      return 1;
    }

    // set up the seed page
    seedPage = malloc(sizeof(WebPage));
    seedPage->url = seedURL;
    seedPage->depth = 0;

    int curl;
    curl = GetWebPage(seedPage);
    if(curl == 0){
      printf("There was error curling the seedURL.");
      return 1;
    }
    
    // initialize a WebPageBag
    WebPageBag = bag_new();
    // initialize a visited page hashtable  
    ht = hashtable_new();
    
    if(WebPageBag->head != NULL) {
      printf("the head of bag is not null");
    }
 
    bag_insert(WebPageBag, (void *) seedPage);
    hashtable_insert(ht, seedURL, (void *) visitedStatus);  
  
    while (!is_empty(WebPageBag)) {
      // get next webpage from the bag
       extractedBagNode = bag_extract(WebPageBag);
       currentPage = malloc(sizeof(WebPage));
       currentPage = (WebPage*)extractedBagNode->data;
       free(extractedBagNode);
       printf("%2d %*s%9s: %s\n", currentPage->depth, currentPage->depth, "", "Fetched:", currentPage->url);
      
      if (!GetWebPage(currentPage)){
	printf("There is a problem curling the page %s.\n", currentPage->url);
      } else {
	// write the file from html
	char *webPageFilePath = malloc((strlen(dir) + HTMLNumber) * sizeof(char));
	sprintf(webPageFilePath, "%s/%d", dir, HTMLNumber);
	// open and write to a file
	currentWebPageFile = fopen(webPageFilePath, "w");
        fprintf(currentWebPageFile, "%s\n%d\n%s", currentPage->url, currentPage->depth, currentPage->html);
	fclose(currentWebPageFile);
	free(webPageFilePath);
	webPageFilePath = NULL;
	// increase the count number of the html file 
	HTMLNumber++;
	printf("%2d %*s%9s: %s\n", currentPage->depth, currentPage->depth, "", "Saved:", currentPage->url);

        if (currentPage->depth < maxDepth) {
  	   printf("%2d %*s%9s: %s\n", currentPage->depth, currentPage->depth, "", "Scanning:", currentPage->url);
	   
	  // get the next url 
	   char *foundURL;
	   foundURL = NULL;  
	   int pos = 0;
	   while((pos = GetNextURL(currentPage->html, pos, currentPage->url, &foundURL)) > 0){
	       printf("%2d %*s%9s: %s\n", currentPage->depth, currentPage->depth, "", "Found:", foundURL);
	       // check if it is within the valid domain
	      if (IsInternalURL(foundURL)){
	        if(NormalizeURL(foundURL)){
		  // get the status of the found URL in the hashtable
		   status = hashtable_find(ht, foundURL);		  
		   // if visited already, then we don't need to visit it again
		  if(status != NULL){
		    free(foundURL);
		    foundURL =NULL;
		  } else {
		       // if not visited, insert into the hashtable		      
		       // create a new WebPage
		       WebPage *newPage;
		       newPage = malloc(sizeof(WebPage));
		       char* copyURL;
		       copyURL = malloc(sizeof(char) * (strlen(foundURL) + 1));
		       strcpy(copyURL, foundURL);
		       newPage->url = copyURL;
		       newPage->depth = currentPage->depth + 1;
		       newPage->html = NULL;
		       
		       // insert into the bag
		       bag_insert(WebPageBag, (void *) newPage);
		       // insert the visited webpage into the hashtable
		       hashtable_insert(ht, copyURL, (void*) visitedStatus);
		       printf("%2d %*s%9s: %s\n", currentPage->depth, currentPage->depth, "", "Added:", newPage->url);
		       
		  }
		  
	        } else {
		    printf("There is a problem parsing the URL %s.\n", foundURL);
	        }
	    } else {
	           printf("%2d %*s%9s: %s\n", currentPage->depth, currentPage->depth, "", "IgnExtrn", foundURL);
	      }
	    free(foundURL);
	    foundURL = NULL;          // free the foundURL and set it to null for it to be updated      
     
	   }
	}
  
      }
      free(currentPage->html);
      currentPage->html = NULL;
      free(currentPage);              // free the currentPage and set it to null for it to be updated
      currentPage = NULL;
    }
    
    printf("Finished crawling.");
    
    bag_delete(WebPageBag);         // free the bag
    hashtable_delete(ht);          // free the entire hashtable 
}
