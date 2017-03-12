
CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

MEMORYDIR = ../lib/memory/

OBJS = $(MEMORYDIR)memory.o web.o file.o index.o word.o webpage.o
LIBCOMMON = libcommon.a

$(LIBCOMMON):$(OBJS)
	ar -cvq $@ $^

memory.o: $(MEMORYDIR)memory.c $(MEMORYDIR)memory.h
	$(CC) $(CFLAGS) -c $(MEMORYDIR)memory.c

web.o: web.c web.h
	$(CC) $(CFLAGS) -c web.c

file.o: file.c file.h
	$(CC) $(CFLAGS) -c file.c

index.o: index.c index.h
	$(CC) $(CFLAGS) -c index.c

word.o: word.c word.h
	$(CC) $(CFLAGS)	-c word.c

webpage.o: webpage.c webpage.h $(MEMORYDIR)memory.h file.h
	$(CC) $(CFLAGS) -c webpage.c

clean:
	rm -f *~
	rm -f *.o
	rm -f $(LIBCOMMON)
