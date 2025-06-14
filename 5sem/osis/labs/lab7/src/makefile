CC=gcc
CFLAGS=-I.

all: tcp_server tcp_client udp_server udp_client

tcp_server: tcpserver.c
	$(CC) -o tcpserver tcpserver.c $(CFLAGS)

tcp_client: tcpclient.c
	$(CC) -o tcpclient tcpclient.c $(CFLAGS)

udp_server: udpserver.c
	$(CC) -o udpserver udpserver.c $(CFLAGS)

udp_client: udpclient.c
	$(CC) -o udpclient udpclient.c $(CFLAGS)

clean:
	rm tcpclient tcpserver udpclient udpserver