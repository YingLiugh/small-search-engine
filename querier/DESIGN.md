Requirement spec:
The TSE querier is a standalone program that reads the index file produced by the TSE indexer, and answers search queries submitted via stdin.

The querier shall:

execute from a command line with usage syntax

./querier pageDirectory indexFilename
where pageDirectory is a directory produced by the crawler, and
where indexFilename is an index file produced by the indexer.
load the index from indexFilename into an internal data structure.

read search queries from stdin, one per line, until EOF.

clean and parse each query according to the syntax described below.
print the 'clean' query for user to see.
use the index to identify the set of documents that satisfy the query, as described below.
if no documents satisfy the query, print No documents match.
otherwise, rank the resulting set of documents according to its score, as described below, and print the set of documents in decreasing rank order; for each, list the score, document ID and URL. (Obtain the URL by reading the first line of the relevant document file from the pageDirectory.)
The querier shall validate its command-line arguments:

pageDirectory is a directory produced by the crawler, and
indexFilename is the name of a readable file.
The querier may assume that the input directory and files follow the designated formats.

pageDirectory has files named 1, 2, 3, ..., without gaps.
The content of document files in pageDirectory follow the format as defined in the crawler specs; thus your code (to read a document file) need not have extensive error checking.
The content of the file named by indexFilename follows our Index file format; thus your code (to recreate an index structure by reading a file) need not have extensive error checking.


Design spec:
The querier takes two parameters pageDirectory and indexFilename. The querier reads in the indexFilename and builds the inverted index for lookup. Then the querier reads the query input provided by the user and checks if the query is valid.
The requirement of the format of query:
    - contains no special characters other than alphabets
    - and, or cannot be the first word
    - and, or cannot be the last word
    - and, or cannot appear consecutively in the query

Then the querier parses the query and gets all the andsequences separated by "or"s. The querier will calculates the scores for each of the andsequences. Each document id that is shared by all the words in one andseuqnece will have a score which is the minimum frequency of these words.The score for a document satisfying a conjunction (aka andsequence) wordA and wordB is the minimum of the score for wordA and the score for wordB on this document. By induction, the score for a document satisfying <andsequence> and wordC is the minimum of the score for the andsequence and the score for wordC on this document.

Then the querier will combine all the scores of the andsequences under the "or" operation. In this process, the score for a document satisfying a disjunction wordA or wordB is the sum of the score for wordA and the score for wordB on this document. By induction, the score for a document satisfying <andsequenceA> or <andsequenceB> is the sum of the score for andsequenceA and the score for andsequenceB on this document.
 
At the end, the querier rank the document IDs and delivers the results in descending order.


Implementation spec:
The querier reads the index file and builds a hashtable_t, with each word as the key and a counters_t as the data. The counters_t contains a list of the document id and frequency pairs. The querier uses index.h to helper update the index table.  Then the querier parses the query input and uses structs andsequence and orsequence to store the fragments. One input line is an orsequqnce, containing a list of andsequences.
For ranking the querier uses qsort.

Testing plan:
First use the crawler and indexer to generate the document files and the inverted index file and then use the querier.
Test the querier on a small number of document files and then a larger number of document files.
Test the arguments:
   the number of arguments
   the validity of arguments: the validity of file, directoy
       		   	      the validity of query