CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O

TAG1 = cw_mod_b
TAG2 = cw_b


EXEC1 = $(TAG1).x
OBJS1 = $(TAG1).o
EXEC2 = $(TAG2).x
OBJS2 = $(TAG2).o


.PHONY: cleaner
cleaner:
	 rm -f *.o *~ *.a *.x

.PHONY: fully
fully: $(EXEC1) $(EXEC2)
    $(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^   
    $(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^   

.PHONY: startCW
    startCW: $(EXEC1) $(EXEC2)
	./$(EXEC1) ./$(EXEC2) $(EXEC2)

.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c
	$(CC) $(CFLAGS) -c $<
