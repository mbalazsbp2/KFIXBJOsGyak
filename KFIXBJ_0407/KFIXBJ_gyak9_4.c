#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void pass(int signal_num) {}
void handleTerm(int signal_num);

int main(void) {
  signal(SIGTERM, handleTerm);
  signal(SIGALRM, pass);

  printf("PID: %d\n", (int)getpid());

  while (1) {
    printf("waiting for signal...\n");
    alarm(3);
    pause();
  }

  return 0;
}

void handleTerm(int signal_num) {
  printf("%d\n", signal_num);
}
