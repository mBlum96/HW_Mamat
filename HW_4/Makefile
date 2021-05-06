CC=gcc
CCLINK=$(CC)
CFLAGS=-g -Wall -std=c99
RM=rm -rf prog *.o libgrades.so

libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: linked-list.h grades.h grades.c
	$(CC) $(CFLAGS) -c -fpic grades.c

clean:
	$(RM)