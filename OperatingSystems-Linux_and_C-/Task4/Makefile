CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

TAG1 = cw4

EXEC1 = $(TAG1).x
OBJS1 = $(TAG1).o

.PHONY: cleaner
cleaner:
	 rm -f *.o *~ *.a *.x

.PHONY: fully
fully: $(EXEC1)
    $(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^   

.PHONY: startCW_4
    startCW_4: $(EXEC1) 
	./$(EXEC1) 
	diff -s file_in.txt file_out.txt


.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c
	$(CC) $(CFLAGS) -c $<
