CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

LIBCOMMON = ../common/libcommon.a
LIBTSEUTIL = ../lib/libtseutil.a

HASHTABLE = ../lib/hashtable/hashtable.c
COUNTERS = ../lib/counters/counters.c


PROG = indexer
SRCS = indexer.c ../lib/hashtable/hashtable.c ../lib/counters/counters.c

$(PROG): 
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBCOMMON) $(LIBTSEUTIL)

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	rm -f *.dat

