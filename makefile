CC=gcc
CFLAGS=-I.

all: sequential_min_max parallel_min_max utils.o find_min_max.o zombiemaker parallel_sum

parallel_sum : parallel_sum.c utils.o utils.h sum.h
	$(CC) utils.o parallel_sum.c -o parallel_sum -lpthread sum.c $(CFLAGS)

sequential_min_max : utils.o find_min_max.o utils.h find_min_max.h 
	$(CC) -o sequential_min_max find_min_max.o utils.o sequential_min_max.c $(CFLAGS)

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)
	
zombiemaker: 
	$(CC) -o zombiemaker zombiemaker.c

clean :
	rm utils.o find_min_max.o sequential_min_max parallel_min_max zombiemaker.o
