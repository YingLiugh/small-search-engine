Requirements spec:
The TSE indexer is a standalone program that reads the document files produced by the TSE crawler, builds an index, and writes that index to a file. Its companion, the index tester, loads an index file produced by the indexer and saves it to another file.

The indexer shall:

1. execute from a command line with usage syntax
       ./indexer pageDirectory indexFilename
       where pageDirectory is a directory produced by the crawler, and
       where indexFilename is the name of a file into which the index should be written.

2. read documents from the pageDirectory, each of which has a unique document ID,
       wherein the document id starts at 1 and increments for each new document,
       and the filename is of form pageDirectory/id,
       and the first line of the file is the URL,
       and the second line of the file is the depth,
       and the rest of the file is the page content.

3. build an inverted-index data structure mapping from words to (documentID, count) pairs, wherein each count represents the number of occurrences of the given word in the given document. Ignore words with fewer than three characters, and NormalizeWord before indexing.

4. create a file indexFilename and write the index to that file, in the format described below.

The indexer shall validate its command-line arguments:

pageDirectory is a directory produced by the crawler (see below), and
indexFilename is the name of a writeable file.
The indexer may assume that

pageDirectory has files named 1, 2, 3, ..., without gaps.
The content of files in pageDirectory follow the format as defined in the crawler specs; 

Index file format:

The indexer writes the inverted index to a file, and the querier reads the inverted index from a file; the file must be in the following format.

      one line per word, one word per line
      each line provides the word and one or more (docID, count) pairs, in the format
      word docID count [docID count]...
      where word is a string of lower-case letters,
      where docID is a positive non-zero integer,
      where count is a positive non-zero integer,
      where the word and integers are separated by spaces.


Design spec:
To create the index of words, we need to read every word from the files and keep track of the counts of them in each file. In order to do this, we can use an inverted index which maps words to document ids and the counts in each document. When we want to look up a word, then we can find the word from the inverted index and then go each document id and count pair. 

Implementation spec:
We can use the hashtable data structure to implement the inverted index. The hashtable has words as its keys and a counter list as its value. In the counter list, every counter node stores the information of the document id and the word's count in this document. We can use the data structure counter_t to achieve so. In order to address collision in the hashtable, we use chaining and therefore each key in the bucket slot of the hashtable has a pointer to the next. If another word is hashed to the same slot, then it can be stored in next.  

Testing plan:
In the test, we want to first test the arguments in the cases of inefficient arguments and invalid arguments. Then we first use simple small documents that follow the format of the document specified in the requirement spec to test index. Then we use the documents produced by the crawler to test indexer.We use both small and large documents to test the performance of the indexer.