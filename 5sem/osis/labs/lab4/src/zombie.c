#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  // создаем потомка
  pid_t child_pid = fork();
  if (child_pid > 0) {
    // подождём, чтобы потомок заработал
    sleep(2);

    // отправим потомку сигнал. из потомка получится зомби
    if (kill(child_pid, SIGKILL) == 0)
      printf("SIGKILL отправлен потомку (%d)!\n", child_pid);

    // подождём 
    sleep(2);
    // потомок прервал своё выполнение

    // проверим, можно ли ещё отправить потомку сигнал
    if (kill(child_pid, 0) == 0)
      printf("Сигнал отправлен потомку (%d). Потомок ещё не умер!\n", child_pid);

    // считаем информацию о завершении потомка
    if (wait(NULL) == child_pid)
      printf("Считали информацию о завершении потомка (%d)!\n", child_pid);

    // отправим сигнал снова
    if (kill(child_pid, 0) == -1)
      printf("Сигнал не отправлен потомку (%d). Теперь зомби убит!\n", child_pid);
  } else {
    while (1) {
      printf("Дочерний процесс работает!\n");
      sleep(1);
    }
  }
  return 0;
}