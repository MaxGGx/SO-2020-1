CC=gcc
CFLAGS=-Wall -pedantic

tarea1: tarea1.o lista3.o

tarea1.o: tarea1.c lista3.h
	$(CC) $(CFLAGS) -c tarea1.c
lista3.o: lista3.c lista3.h
	$(CC) $(CFLAGS) -c lista3.c

clean:
	rm tarea1 tarea1.o lista3.o