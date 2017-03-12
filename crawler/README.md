Main program: crawler.c
Usage: The following commands should be issued to run the program:
      make : Build the program and update all dependent files and create object files
      make debug : Run the program in debug mode
      make clean : Clean up
      mkdir [fileDirectory] : Create a directory to serve as the databse for webpage storage


Dependent files: The following files should be in the directory as crawler.c
      bag.h 
      bag.c
      web.h
      web.c
      hashtable.h
      hashtable.c
      Makefile

Input: ./crawler [seedURL] [fileDirectory] [maxCrawlDepth]
      Arguments Requirements: 
         [seedURL] needs to be in the domain "http://old-www.cs.dartmouth.edu/"
	 [fileDirectory] needs to be valid.
         [maxCrawlDepth] needs to be non-negative integer

Output:
     Output: Webpages that have been crawled will be saved into the directory and with file names in incrementing number
     The files are in format : 
     	    line 1: current URL
 	    line 2: current depth
 	    line 3: current html contents 
The terminal will print out useful information about the crawling process