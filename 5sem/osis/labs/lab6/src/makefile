CC=gcc

all: client server

client: client.c libutils.so
	$(CC) client.c utils.o -L -lutils -pthread -o client

server: server.c libutils.so
	$(CC) server.c utils.o -L -lutils -pthread -o server

libutils.so: utils.o
	$(CC) -shared utils.o -o libutils.so

utils.o : utils.c
	$(CC) -c -fPIC utils.c -o utils.o

run_servers: server.c
	./server --port 20000 --tnum 4 &
	./server --port 20001 --tnum 4 &
	./server --port 20002 --tnum 4 &

run_client: client.c
	./client --k 25 --mod 123 --servers servers.txt

clean :
	rm client server libutils.so utils.o