========================================================================================================================
First use crawler and indexer to generate the document files and the index. In this case, two document files are generated.
./crawler  http://old-www.cs.dartmouth.edu/~cs50/index.html ../querier/data/ 1
 ./indexer ../querier/data ../querier/index/index
 
Please enter your query:and
The first query word cannot be and.
Syntax error: incorrect query format.

Please enter your query:or
The first query word cannot be or.
Syntax error: incorrect query format.

Please enter your query:and dartmouth
The first query word cannot be and.
Syntax error: incorrect query format.

Please enter your query:dartmouth college and or computer 
The syntax cannot have and and or consecutively.
Syntax error: incorrect query format.

Please enter your query:dartmouth college and and computer 
The syntax cannot have and and and consecutively.
Syntax error: incorrect query format.

Please enter your query:dartmouth college or
Error: or cannot be last. 
Syntax error: incorrect query format.

Please enter your query:dartmouth college and
Error: and cannot be last. 
Syntax error: incorrect query format.

Please enter your query:5
Error: Bad character 5. Only alphabets are allowed in query.

Please enter your query:! 
Error: Bad character !. Only alphabets are allowed in query.

Please enter your query:apple
Matches 0 documents (ranked).
Please enter your query:dartmouth college and educate     
Matches 2 documents (ranked).
score 1  doc 1 : http://old-www.cs.dartmouth.edu/~cs50/index.html

score 1  doc 2 : http://old-www.cs.dartmouth.edu/~cs50/

Please enter your query:bottle or college
Matches 2 documents (ranked).
score 1  doc 1 : http://old-www.cs.dartmouth.edu/~cs50/index.html

========================================================================================================================

First use crawler and indexer to generate the document files and the index. In this case, eight document files are generated.
 ./crawler http://old-www.cs.dartmouth.edu/~cs50/data/tse ../querier/data/ 2
 ./indexer ../querier/data ../querier/index/index
 
Please enter your query:program or engine and college or music
Matches 6 documents (ranked).
score 25  doc 4 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html

score 15  doc 6 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html

score 10  doc 3 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html

score 9  doc 5 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html

score 4  doc 7 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html

score 4  doc 8 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html

PROGRAM OR engine AND college OR music
Matches 6 documents (ranked).
score 25  doc 4 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html

score 15  doc 6 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html

score 10  doc 3 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html

score 9  doc 5 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html

score 4  doc 7 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html

score 4  doc 8 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html


Please enter your query:design implement and project    
Matches 4 documents (ranked).
score 2  doc 3 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html

score 2  doc 5 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html

score 2  doc 6 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html

score 1  doc 4 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html

Please enter your query:design
Matches 7 documents (ranked).
score 18  doc 3 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Computer_science.html

score 13  doc 6 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Dartmouth_College.html

score 6  doc 5 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Unix.html

score 4  doc 4 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/C_(programming_language).html

score 2  doc 7 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Hash_table.html

score 2  doc 8 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/wiki/Linked_list.html

score 1  doc 2 : http://old-www.cs.dartmouth.edu/~cs50/data/tse/