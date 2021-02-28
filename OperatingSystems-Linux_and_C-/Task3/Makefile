CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -O

TAG1 = cw3_a
TAG2 = cw3_b
TAG3 = cw3_c_2


EXEC1 = $(TAG1).x
OBJS1 = $(TAG1).o
EXEC2 = $(TAG2).x
OBJS2 = $(TAG2).o
EXEC3 = $(TAG3).x
OBJS3 = $(TAG3).o



.PHONY: cleaner
cleaner:
	 rm -f *.o *~ *.a *.x

.PHONY: fully
fully: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4)
    $(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^   
    $(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^
    $(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^    
    $(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^  

.PHONY: startCW_a startCW_b startCW_c
    startCW_a: $(EXEC1) 
	./$(EXEC1) signal_handler 2
    startCW_b: $(EXEC1) $(EXEC2)
	./$(EXEC2) default 2
    startCW_c: $(EXEC1) $(EXEC3) 
	./$(EXEC3) ignore 2

.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c
	$(CC) $(CFLAGS) -c $<
