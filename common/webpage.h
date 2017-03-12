/* 
 * webpage - utility functions for saving and loading WebPage structs
 *
 * David Kotz, April 2016
 */

#ifndef __WEBPAGE_H
#define __WEBPAGE_H

#include <stdio.h>
#include "web.h" // WebPage

/**************** init_pageDirectory ****************/
/* init_pageDirectory - set up the pageDirectory.
 * Our approach is simple: we create a file ".crawler" there.
 * Return true if success. 
 */
bool init_pageDirectory(const char *pageDirectory);

/**************** is_pageDirectory ****************/
/* 
 * Return true if a file '.crawler' can be found in the pageDirectory.
 * Return false otherwise - either that file or pageDirectory does not exist.
 */
bool is_pageDirectory(char *pageDirectory);

/**************** page_save ****************/
/* Write the page to the document file in the pageDirectory.
 */
void webpage_save(WebPage *page, char *pageDirectory, const int docID);

/**************** webpage_load ****************/
/* 
 * Opens a file named with 'documentID' in the given 'pageDirectory', 
 * fills in the 'depth' and 'URL' variables from the first two lines of file,
 * and returns pointer to WebPage struct.
 * Caller must later free both the URL and the returned pointer.
 * Returns NULL if error or no such file.
 */
WebPage *webpage_load(char *pageDirectory, const int documentID);

/**************** webpage_new ****************/
/* Allocate and initialize a new WebPage structure.
 * Both url and html are copied into the struct.
 * It is caller's responsibility to later webpage_delete() the result.
 */
void *webpage_new(char *url, const int depth, char *html);

/**************** webpage_new_empty ****************/
/* Allocate and initialize a new WebPage structure, empty of html.
 * It is caller's responsibility to later count_free() the result.
 */
void *webpage_new_empty(char *url, const int depth);

/**************** webpage_print ****************/
/* Print a representation of the WebPage data structure passed as 'data'.
 */
void webpage_print(FILE *fp, void *data);

/**************** webpage_delete ****************/
/* Delete a WebPage structure created by webpage_new().
 * This function may be called from bag_delete().
 */
void webpage_delete(void *data);

#endif // __WEBPAGE_H
