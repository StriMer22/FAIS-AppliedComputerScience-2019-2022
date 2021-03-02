CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

TAG1 = mult
TAG2 = worker

EXEC1 = $(TAG1).x
OBJS1 = $(TAG1).o
EXEC2 = $(TAG2).x
OBJS2 = $(TAG2).o

.PHONY: cleaner
cleaner:
	 rm -f *.o *~ *.a *.x *.out

.PHONY: fully
fully: $(EXEC1) $(EXEC2)
    $(EXEC1): $(OBJS1)
	$(LD) sem.h -pthread -o $@ $(LFLAGS) $^  
    $(EXEC2): $(OBJS2)
	$(LD) sem.h -pthread -o $@ $(LFLAGS) $^ 

.PHONY: startCW_6 
    startCW_6: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2) 3 2 1

.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 
