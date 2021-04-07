#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
  int fd[2];
  int pid;

  if (pipe(fd)) {
    perror("pipe error");
    return 1;
  }

  pid = fork();

  if (pid == 0) {
    close(fd[0]);

    char msg[] = "MB KFIXBJ\n";
    write(fd[1], msg, strlen(msg) + 1);
    close(fd[1]);

    return 0;
  }

  close(fd[1]);
  
  char buffer[1024];
  int buffer_size = sizeof(buffer) / sizeof(char);
  read(fd[0], buffer, buffer_size);
  close(fd[0]);

  printf("%s", buffer);

  wait(NULL);

  return 0;
}
