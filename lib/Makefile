
# Builds and compiles all the data structures into a library.
OBJS = memory/memory.o list/list.o hashtable/hashtable.o bag/bag.o counters/counters.o
LIBTSE = libtseutil.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
MAKE = make

$(LIBTSE):$(OBJS)
	ar -cvq $@ $^

# add other targets for the other .o files

memory/memory.o: memory/memory.c memory/memory.h
	cd memory; $(MAKE)

list/list.o: list/list.c list/list.h
	cd list; $(CC) $(CFLAGS) -c list.c

hashtable/hashtable.o: hashtable/hashtable.c hashtable/hashtable.h
	cd hashtable; $(CC) $(CFLAGS) -c hashtable.c

bag/bag,o: bag/bag.c bag/bag.h
	cd bag; $(CC) $(CFLAGS) -c bag.c

counters/counters,o: counters/counters,c counters/counters.h
	cd bag; $(CC) $(CFLAGS) -c counters.c


# add cleanup commands for other subdirectories
clean:
	rm -f list/*~
	rm -f hashtable/*~
	rm -f bag/*~
	rm -f counters/*~
	rm -f memory/*~
	rm -f list/*.o
	rm -f hashtable/*.o
	rm -f bag/*.o
	rm -f counters/*.o
	rm -f memory/*.o
