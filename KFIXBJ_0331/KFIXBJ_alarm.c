#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define SECONDS 1

void pass(int signal_num) {}
void handle_interrupt(int signal_num);

int main(void) {
  signal(SIGINT, handle_interrupt);
  signal(SIGALRM, pass);

  for (int i = 0; i < 5; i++) {
    printf("i'll pause for %d second(s)\n", SECONDS);
    alarm(SECONDS);
    pause();
    printf("i'm back\n");
  }

  return 0;
}

void handle_interrupt(int signal_num) {
  char msg[] = "received an interrupt\n";
  write(STDOUT_FILENO, msg, strlen(msg));
  signal(SIGINT, SIG_IGN);
}
