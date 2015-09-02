CC=gcc
CFLAGS=-Wall -g -std=c99

brickletter: brickletter.o board.o color.o cursor.o matrix.o square.o

.PHONY: clean distclean

clean:
	rm -f *.o

distclean: clean
	rm -f brickletter
