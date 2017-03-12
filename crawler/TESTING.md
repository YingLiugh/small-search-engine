Argument number testing:
./crawler
3 arguments needed [seedURL] [Directory] [Maxdepth]

./crawler http://www.cs.dartmouth.edu/~cs50/index.html
3 arguments needed [seedURL] [Directory] [Maxdepth]

./crawler ./data
3 arguments needed [seedURL] [Directory] [Maxdepth]

Invalid base URL testing:
./crawler http://www.nonexistentURL  ./data 1
Incorrect domain

Invalid directory testing:
./crawler http://www.cs.dartmouth.edu/~cs50/index.html ./nonexistentpath 1
The directory is not valid.

Invalid depth number testing:
./crawler http://www.cs.dartmouth.edu/~cs50/index.html ./data -5
Incorrect depth. Please provide a non negative integer.

Use  http://old-www.cs.dartmouth.edu/~cs50/data/tse/ to test crawling:

./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/ ./data/ 0   file saved : 1
 0  Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/
 0    Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/


./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse/ ./data/ 1   file saved: 7
 0  Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/
 0    Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/
 0 Scanning:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/
 0    Found:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html
 0    Added:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html
 0    Found:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
 0    Added:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
 0    Found:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
 0    Added:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
 0    Found:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
 0    Added:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
 0    Found:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
 0    Added:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
 0    Found:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html
 0    Added:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html
 1   Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html
 1     Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html
 1   Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
 1     Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html
 1   Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
 1     Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html
 1   Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
 1     Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html
 1   Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
 1     Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html
 1   Fetched:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html
 1     Saved:: http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html

Check memory:
valgrind --leak-check=full --show-leak-kinds=all ./crawler 