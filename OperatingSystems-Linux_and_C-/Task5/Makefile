CC = gcc
LD = gcc

DIR = `basename $(CURDIR)`

CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic

FILE_IN= file_in.txt
FILE_OUT= file_out.txt
FIFO= fifo.fifo
PRODUCER= ./producer.x $(FILE_IN) $(FIFO)
CONSUMER= ./consumer.x $(FILE_OUT) $(FIFO)

TAG1 = main
TAG2 = producer
TAG3 = consumer

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
fully: $(EXEC1) $(EXEC2) $(EXEC3)
    $(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^  
    $(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^  
    $(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^   

.PHONY: startCW_5a startCW_5b
    startCW_5a: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(FILE_IN) $(FILE_OUT) $(FIFO)
	diff -s $(FILE_IN) $(FILE_OUT)
    startCW_5b: $(EXEC2) $(EXEC3)
	mkfifo $(FIFO)
	xterm -hold -title PRODUCER -e $(PRODUCER) & xterm -hold -title CONSUMER -e $(CONSUMER)
	rm -f $(FIFO)
	diff -s $(FILE_IN) $(FILE_OUT)



.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))

%.o: %.c
	$(CC) $(CFLAGS) -c $<
