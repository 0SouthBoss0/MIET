#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/wait.h>

int main(int argc, char ** argv) {
  const char *NameScript = "./sequential_min_max";
  char *args[4] = {" ", "5", "8", NULL};
  int rv, status;
  int pid = fork();
  if (pid == 0) {
    execvp(NameScript, args);
    exit(rv);
  } else {
    if (wait(&status) >= 0) {
      if (WIFEXITED(status)) {
        printf("Child process exited with %d status\n", WEXITSTATUS(status));
      }
    }
  }
  fflush(NULL);
  return 0;
}