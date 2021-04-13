#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handleAlarm(int signal_num);

int main(void) {
  signal(SIGALRM, handleAlarm);

  printf("PID: %d\n", (int)getpid());
  printf("waiting for alarm...\n");
  pause();

  printf("Resumed\n");
  return 0;
}

void handleAlarm(int signal_num) {
  char msg[] = "KFIXBJ\n";
  write(STDOUT_FILENO, msg, strlen(msg));
}
