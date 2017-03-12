/* 
 * webpage - utility functions for saving and loading WebPage structs
 *
 * see webpage.h for file and function documentation
 *
 * David Kotz, April 2016
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "webpage.h"
#include "file.h"
#include "../lib/memory/memory.h"

/**************** file-local global variables ****************/
static const char crawlerfile[] = ".crawler";

/**************** file-local function prototypes ****************/
static void *checkp(void *p, char *message);

/**************** init_pageDirectory ****************/
bool
init_pageDirectory(const char *pageDirectory)
{
  if (pageDirectory == NULL)
    return false;

  // make a filename
  int filenamelen = strlen(pageDirectory) + strlen(crawlerfile) + 2;
  char *filename = count_malloc_assert(filenamelen,
				       "init_pageDirectory filename");
  sprintf(filename, "%s/%s", pageDirectory, crawlerfile);

  // now create the file
  FILE *fp = fopen(filename, "w");
  if (fp == NULL) {	      // file creation failed
    count_free(filename);
    return false;
  } else {		      // file creation succeeded
    fclose(fp);
    count_free(filename);
    return true;
  }
}

/**************** is_pageDirectory ****************/
bool
is_pageDirectory(char *pageDirectory)
{
  if (pageDirectory == NULL)
    return false;

  // make a filename
  int filenamelen = strlen(pageDirectory) + strlen(crawlerfile) + 2;
  char *filename = count_malloc_assert(filenamelen,
				       "is_pageDirectory filename");
  sprintf(filename, "%s/%s", pageDirectory, crawlerfile);

  // now open the file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {	      // file open failed
    count_free(filename);
    return false;
  } else {		      // file open succeeded
    fclose(fp);
    count_free(filename);
    return true;
  }
}

/**************** webpage_save ****************/
void 
webpage_save(WebPage *page, char *pageDirectory, const int documentID)
{
  checkp(page, "page_save gets NULL page");
  checkp(page->url, "page_save gets NULL page->url");
  checkp(page->html, "page_save gets NULL page->html");
  checkp(pageDirectory, "page_save gets NULL pageDirectory");

  // create filename string from page directory and document ID
  char *filename = count_malloc_assert(strlen(pageDirectory)+12, "page_save");
  sprintf(filename, "%s/%d", pageDirectory, documentID);

  FILE *fp = fopen(filename, "w");
  checkp(fp, "page_save cannot open file for writing");
  
  fprintf(fp, "%s\n%d\n%s\n", page->url, page->depth, page->html);

  fclose(fp);
  count_free(filename);
}

/**************** webpage_load ****************/
WebPage *
webpage_load(char *pageDirectory, const int documentID)
{
  checkp(pageDirectory, "page_load gets NULL pageDirectory");

  // create filename string from page directory and document ID
  char *filename = count_malloc_assert(strlen(pageDirectory)+12, "page_load");
  sprintf(filename, "%s/%d", pageDirectory, documentID);

  // try to open the file
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    // failed; likely there is no such file
    count_free(filename);
    return NULL;
  } else {
    // parse the file into URL, depth, and html
    // we assume the file is properly formatted
    char *URL = readline(fp); // URL is on first line of file
    char *depthString = readline(fp); // depth is on second line of file
    char *html = readfile(fp);	// page content is rest of the file

    // close up the file
    fclose(fp);
    count_free(filename);

    // sanity checks on what we read
    assertp(URL, "webpage_load URL");
    assertp(depthString, "webpage_load depth");
    assertp(html, "webpage_load html");

    int depth = atoi(depthString);

    // construct a WebPage and copy strings into it:
    WebPage *page = webpage_new(URL, depth, html);

    free(URL);
    free(depthString);
    free(html);
    
    return (page);
  }
}

/**************** webpage_new ****************/
/* Notice we do not use count_malloc for html;
 * that's because some WebPages are filled by GetWebPage and it
 * does not use count_malloc; webpage_delete always calls free().
 */
void *
webpage_new(char *url, const int depth, char *html)
{
  WebPage *page = count_malloc_assert(sizeof(WebPage), "WebPage");

  checkp(url, "webpage_new(url=NULL)");
  page->url = count_malloc_assert(strlen(url)+1, "WebPage->url");
  strcpy(page->url, url);

  checkp(html, "webpage_new(html=NULL)");
  page->html = assertp(malloc(strlen(html)+1), "WebPage->html");
  strcpy(page->html, html);

  page->html_len = strlen(html);
  page->depth = depth;

  return page;
}

/**************** webpage_new_empty ****************/
void *
webpage_new_empty(char *url, const int depth)
{
  WebPage *page = count_malloc_assert(sizeof(WebPage), "WebPage");

  checkp(url, "WebPage(url=NULL)");
  page->url = count_malloc_assert(strlen(url)+1, "WebPage->url");
  strcpy(page->url, url);
  page->html = NULL;
  page->html_len = 0;
  page->depth = depth;

  return page;
}

/**************** webpage_print ****************/
void
webpage_print(FILE *fp, void *data)
{
  WebPage *page = data;

  if (page == NULL)
    fprintf(fp, "(null)");
  else 
    fprintf(fp, "['%s' len=%lu depth=%d]", 
	    page->url, page->html_len, page->depth);
}

/**************** webpage_delete ****************/
void
webpage_delete(void *data)
{
  WebPage *page = data;
  if (page != NULL) {
    if (page->url) count_free(page->url);
    if (page->html) free(page->html); // not count_free
   count_free(page);
  }
}

/**************** checkp ****************/
/* if pointer p is NULL, print error message and die,
 * otherwise, return p unchanged.
 */
static void *
checkp(void *p, char *message)
{
  if (p == NULL) {
    fprintf(stderr, "CHECKP: %s\n", message);
    exit (99);
  }
  return p;
}
