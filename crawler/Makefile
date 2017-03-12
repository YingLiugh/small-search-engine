# Makefile TEMPLATE for 'crawler' module
PROG = crawler
LIBS = -lcurl
CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

BAGDIR = ../lib/bag/
HTDIR  = ../lib/hashtable/
WEBDIR = ../common/
SRCS = crawler.c $(WEBDIR)web.c $(BAGDIR)bag.c $(HTDIR)hashtable.c
OBJS = crawler.o web.o bag.o hashtable.o

# build the crawler
$(PROG): $(OBJS) 
	$(CC) $(CFLAGS) $(LIBS) -o $(PROG) $(OBJS) 

# debug
debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(PROG) $(OBJS) $(LIBS)

# crawler source dependencies; add others as needed
crawler.o: crawler.c $(WEBDIR)web.h $(BAGDIR)bag.h $(HTDIR)hashtable.h
	$(CC) $(CFLAGS) -c crawler.c

web.o: $(WEBDIR)web.c $(WEBDIR)web.h
	$(CC) $(CFLAGS) -c $(WEBDIR)web.c

bag.o: $(BAGDIR)bag.c $(BAGDIR)bag.h
	$(CC) $(CFLAGS) -c $(BAGDIR)bag.c

hashtable.o: $(HTDIR)hashtable.c $(HTDIR)hashtable.h
	$(CC) $(CFLAGS) -c $(HTDIR)hashtable.c

# build the library
lib/cs50ds.a: 
	cd lib; $(MAKE)

clean:
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
	cd lib; $(MAKE) clean
