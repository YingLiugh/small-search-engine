 ./indexer
Two arguments are required.

./indexer outputFile
Two arguments are required.

./indexer ../fakeDir outputFile.dat
The directory is not valid.

Use indexTest.c to test the index.c, which builds the inverted index and saves to a file indexTestOutput.dat:
firstWord 1 2 2 1
secondWord 1 2
thirdWord 1 2 2 2 3 3

Use small files from testdir to test the indexer
./indexer ../testdir outputTest.dat
The contents of the outputTest.dat
line 1 1
words 1 1
the 1 4
just 1 1
title 2 1
for 1 1
should 1 1
doctype 2 1
page 2 1
heading 2 1
a 1 1 2 2
small 1 1
get 1 1
test 1 1
third 1 1
this 2 2
to 1 1
from 1 1
able 1 1
starting 1 1
indexer 1 2
html 2 1
his 1 1
is 1 1 2 2
paragraph 2 1
be 1 1

Use large amount of data to test indexer
./indexer ../data outputFile.dat