CC = gcc
CFLAGS = -g -Wall -std=gnu99 -pedantic
MAIN = dirtr
OBJS = dirtr.o dirfunc.o

all : $(MAIN)

$(MAIN) : $(OBJS) dirfunc.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

dirtr.o : dirtr.c dirfunc.h
	$(CC) $(CFLAGS) -c dirtr.c

dirfunc.o : dirfunc.c dirfunc.h
	$(CC) $(CFLAGS) -c dirfunc.c

test : $(MAIN)
	./dirtr ../..

clean :
	rm -f *.o $(MAIN) core
