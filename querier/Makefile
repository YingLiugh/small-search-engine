CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make
LIBCOMMON = ../common/libcommon.a
LIBTSEUTIL = ../lib/libtseutil.a
LIB = -lm
HASHTABLE = ../lib/hashtable/hashtable.c
COUNTERS = ../lib/counters/counters.c
WORD = ../common/word.c

PROG = querier
SRCS = querier.c ../common/index.c ../lib/hashtable/hashtable.c ../lib/counters/counters.c ../common/word.c ../lib/bag/bag.c ../lib/list/list.c

$(PROG):
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIB) $(LIBCOMMON) $(LIBTSEUTIL) 
clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
