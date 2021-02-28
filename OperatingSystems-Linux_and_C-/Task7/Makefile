CFLAGS := -Wall -pedantic -c
RM := rm -f

DIR = `basename $(CURDIR)`

NAME1 := main

OBJ1 := $(NAME1).o

EXEC1d1 := $(NAME1)d1.x
EXEC1d2 := $(NAME1)d2.x

LIBSONAME := shmem
LIBSO := lib$(LIBSONAME).so


.PHONY: fully

fully: libsem.a libshmem.so main.x producer.x consumer.x

#=========================================================
# 			LINKOWANIE WYKONYWALNYCH PLIKÓW
#=========================================================
$(EXEC1d1): $(OBJ1) libshmem.so
	gcc -std=c99 -L. -lshmem -o $@ $^ -Wl,-rpath . 

$(EXEC1d2): $(OBJ1) libshmem.so
	gcc -std=c99 -L. -lshmem -o $@ $^
	export LD_LIBRARY_PATH=.

%.x: %.o libshmem.so libsem.a
	gcc -std=c99 -L. -pthread -lshmem -lsem -o $@ $^ -lrt -Wl,-rpath  . 
#=========================================================
# 			KOMPILOWANIE OBIEKTOWYCH PLIKÓW
#=========================================================
%.o: %.c
	gcc -std=c99 -pthread $(CFLAGS) -o $@ $< 

#=========================================================
# 			   BIBLIOTEKI
#=========================================================

$(LIBSO): $(LIBSONAME).o
	gcc -std=c99 -pthread -shared -o $@ $< 

$(LIBSONAME).o: $(LIBSONAME).c
	gcc -std=c99 -pthread $(CFLAGS) -fPIC -o $@ $< 

lib%.a: %.o
	ar rv $@ $^

.PHONY: cleaner

cleaner:
	$(RM) *.o *.x a.out *.a *.so output.txt

.PHONY: tar
tar: cleaner
	    (cd ../; tar -cvzf $(DIR).tar.gz $(DIR))


