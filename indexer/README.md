The TSE indexer is a component of the Tiny Search Engine program. It reads the document files produced by the
TSE crawler and builds an index and saves into a file.
The main program is indexer.c

Usage: The following commands must be issued to run the program
       In bash/shell:
       make (Up date all dependent files and create object files. The object file to run this program is indexer)

       The program uses the libraries built in ../common and ../lib.
       To build the libraries, use the following commands in the top directory tse:
       
       make lib
       make common
       
Input: ./indexer [webPageDirectory] [outputFile]

       [webPageDirectory] : for example ../data
       Requirement: The directory must exist and already created. The documents in the files are assumed to be the files produced by the crawler and follow the format.

       [outputFile] : for example output.dat
       Requirment: The output name should be named with extension .dat for easy cleanup.

Output: inverted index in the file in the current directory.
