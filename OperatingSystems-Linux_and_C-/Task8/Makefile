CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

TAG1 = main

EXEC1 = $(TAG1).x
OBJS1 = $(TAG1).o

.PHONY: cleaner
cleaner:
	 rm -f *.o *~ *.a *.x

.PHONY: fully
fully: $(EXEC1) 
    $(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^ -lpthread   

.PHONY: startCW
    startCW: $(EXEC1) 
	./$(EXEC1) 3 3

.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c
	$(CC) $(CFLAGS) -c $<
