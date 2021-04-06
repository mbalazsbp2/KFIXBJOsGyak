#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void pass(int signal_num) {}

int main(void) {
  sigset_t signal_set;
  sigfillset(&signal_set);
  int signal_num;

  signal(SIGALRM, pass);

  printf("PID: %d\n", (int)getpid());
  printf("waiting for alarm...\n");

  int received_alarm = 0;

  while (!received_alarm) {
    sigwait(&signal_set, &signal_num);
    if (signal_num == SIGALRM) {
      printf("received alarm\n");
      received_alarm = 1;
    }
  }

  return 0;
}
