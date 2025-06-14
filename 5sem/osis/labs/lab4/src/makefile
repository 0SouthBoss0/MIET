CC=gcc
CFLAGS=-I.

all: parallel_min_max zombie process_memory

parallel_min_max : utils.o find_min_max.o utils.h find_min_max.h parallel_min_max.c
	$(CC) -o parallel_min_max utils.o find_min_max.o parallel_min_max.c $(CFLAGS)

zombie :  zombie.c
	$(CC) -o zombie zombie.c $(CFLAGS)

process_memory : process_memory.c
	$(CC) -o process_memory process_memory.c $(CFLAGS)

parallel_sum : utils.o parallel_sum.c
	$(CC) -pthread -o parallel_sum utils.o parallel_sum.c $(CFLAGS)

parallel_sum_lib : utils.o  libsum parallel_sum.c
	$(CC) -o parallel_sum utils.o parallel_sum.c -L/workspaces/os_lab_2019/lab4/src -lsum -pthread $(CFLAGS)

libsum : sum.c
	gcc -c sum.c -o sum.o
	ar rcs libsum.a sum.o
	rm sum.o

utils.o : utils.h utils.c
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h find_min_max.c
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

clean :
	rm utils.o find_min_max.o parallel_min_max zombie process_memory parallel_sum libsum.a
