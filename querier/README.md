Main program: querier.c

Usage: The following commands should be issued to run the program:
      make
      ./querier [webPageDirectory] [indexFileName]
      make clean

Input: [webPageDirectory] [indexFileName]
    the requirements of parameters:
    [webPageDirectory] is a valid directory containing document files.
    [indexFileName] is a valid index file name.

    the requirements of the query: 1.contains no special characters other than alphabets. 2.and, or cannot be the first word. 3.and, or cannot be the last word. 4. and, or cannot appear consecutively in the query

Output: If the query satistifes the syntax, then the output lists the document ids and their urls, scores in descending order.
For example,
Please enter your query:design implement and project    
Matches 4 documents (ranked).
score 2  doc 3 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html

score 2  doc 5 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html

score 2  doc 6 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html

score 1  doc 4 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html