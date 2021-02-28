CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -O -fPIC
LFLAGS = -Wall -O

TAG1 = cw_a
TAG2 = cw_b
TAG3 = cw_c
TAG4 = cw_d
TAG5 = cw_e

EXEC1 = $(TAG1).x
OBJS1 = $(TAG1).o
EXEC2 = $(TAG2).x
OBJS2 = $(TAG2).o
EXEC3 = $(TAG3).x
OBJS3 = $(TAG3).o
EXEC4 = $(TAG4).x
OBJS4 = $(TAG4).o
EXEC5 = $(TAG5).x
OBJS5 = $(TAG5).o

.PHONY: cleaner
cleaner:
	 rm -f *.o *~ *.a *.x

.PHONY: fully
fully: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)
    $(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^   
    $(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^   
    $(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^   
    $(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^
    $(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: startCW_a startCW_b startCW_c startCW_d startCW_e
    startCW_a: $(EXEC1)
	./$(EXEC1)
    startCW_b: $(EXEC2)
	./$(EXEC2)
    startCW_c: $(EXEC3)
	(./$(EXEC3);(pstree -p | egrep "systemd\(1\)|cw_c.x"))
    startCW_d: $(EXEC4)
	./$(EXEC4)
    startCW_e: $(EXEC5)
	./$(EXEC5)

.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c
	$(CC) $(CFLAGS) -c $<
