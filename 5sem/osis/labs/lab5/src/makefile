CC=gcc
CFLAGS=-I.

all: no_mutex mutex factorial deadlock

no_mutex : no_mutex.c
	$(CC) -pthread -o no_mutex no_mutex.c $(CFLAGS)

mutex : mutex.c
	$(CC) -pthread -o mutex mutex.c $(CFLAGS)

factorial : factorial.c
	$(CC) -pthread -o factorial factorial.c $(CFLAGS)

deadlock : deadlock.c
	$(CC) -pthread -o deadlock deadlock.c $(CFLAGS)
	
clean :
	rm no_mutex mutex factorial deadlock
