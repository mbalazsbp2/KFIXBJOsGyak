#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

void handleSignals(int signal_num);

int main(void) {
  signal(SIGINT, handleSignals);
  signal(SIGQUIT, handleSignals);

  printf("PID: %d\n", (int)getpid());
  
  while (1) {
    printf("waiting for signal...\n");
    pause();
  }

  return 0;
}

void handleSignals(int signal_num) {
  if (signal_num == SIGQUIT) {
    char msg[] = "received SIGQUIT\n";
    write(STDOUT_FILENO, msg, strlen(msg));
  }
  
  else if (signal_num == SIGINT) {
    char msg[] = "received SIGINT\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    signal(SIGINT, SIG_DFL);
  }
}
