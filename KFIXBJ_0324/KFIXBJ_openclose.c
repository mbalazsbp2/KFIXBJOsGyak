#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


void read_then_write(int fd, char buffer[], int buffer_size, char content[]);
void write_then_read(int fd, char buffer[], int buffer_size, char content[]);


int main(void) {
  int fd, buffer_size;
  char buffer[128], content[128];

  buffer_size = sizeof(buffer) / sizeof(char);

  fd = open("KFIXBJ.txt", O_RDWR);

  if (fd == -1) {
    perror("open() error");
    exit(-1);
  }

  strcpy(content, "abcdef\n");
  printf("\n1. Write then read:\n");
  write_then_read(fd, buffer, buffer_size, content);

  strcpy(content, "KFIXBJ\n");
  printf("\n2. Read then write:\n");
  read_then_write(fd, buffer, buffer_size, content);

  printf("\n");

  return 0;
}


void read_then_write(int fd, char buffer[], int buffer_size, char content[]) {
  int result;

  lseek(fd, 0, SEEK_SET);
  
  result = read(fd, buffer, buffer_size);
  printf("Read %d bytes with read(): %s", result, buffer);

  result = lseek(fd, 0, SEEK_SET);
  printf("lseek() - Current file offset: %d\n", result);

  result = write(fd, content, strlen(content));
  printf("Wrote %d bytes with write(): %s", result, content);

  return;
}


void write_then_read(int fd, char buffer[], int buffer_size, char content[]) {
  int result;

  lseek(fd, 0, SEEK_SET);

  result = write(fd, content, strlen(content));
  printf("Wrote %d bytes with write(): %s", result, content);

  result = lseek(fd, 0, SEEK_SET);
  printf("lseek() - Current file offset: %d\n", result);
  
  result = read(fd, buffer, buffer_size);
  printf("Read %d bytes with read(): %s", result, buffer);

  return;
}
