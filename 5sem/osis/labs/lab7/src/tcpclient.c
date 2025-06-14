#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 100
#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char *argv[]) {
  int fd;
  int nread;
  char buf[BUFSIZE];
  struct sockaddr_in servaddr;
  if (argc < 3) {
    printf("Usage: tcpclient <ip> <port>\n");
    exit(1);
  }
  
  // создание сокета
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket creating");
    exit(1);
  }
  
  // инициализация структуры адреса сервера
  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;

  // преобразование IP-адреса из строки в двоичный формат
  if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
    perror("bad address");
    exit(1);
  }

  // преобразование номера порта из строки в число и установка в структуру адреса
  servaddr.sin_port = htons(atoi(argv[2]));

  // установка соединения с сервером
  if (connect(fd, (SADDR *)&servaddr, SIZE) < 0) {
    perror("connect");
    exit(1);
  }

  write(1, "Input message to send\n", 22);

  // цикл чтения сообщений и отправки их на сервер
  while ((nread = read(0, buf, BUFSIZE)) > 0) {
    // отправка сообщения на сервер
    if (write(fd, buf, nread) < 0) {
      perror("write");
      exit(1);
    }
  }

  close(fd);
  exit(0);
}