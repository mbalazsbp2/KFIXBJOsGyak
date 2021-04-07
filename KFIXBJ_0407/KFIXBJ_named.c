#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(void) {
  int fd;
  int pid;

  mkfifo("kfixbj", S_IRUSR | S_IWUSR);

  pid = fork();

  if (pid == 0) {
    char msg[] = "Molnár Balázs\n";
    fd = open("kfixbj", O_WRONLY);
    write(fd, msg, strlen(msg) + 1);
    close(fd);
    
    return 0;
  }

  char buffer[1024];
  int buffer_size = sizeof(buffer) / sizeof(char);
  fd = open("kfixbj", O_RDONLY);
  read(fd, buffer, buffer_size);
  close(fd);
  unlink("kfixbj");

  printf("%s", buffer);

  wait(NULL);

  return 0;
}
