#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#define MSG_CONTENT_SIZE 1024

struct msg_buffer {
  long msg_type;
  char msg_content[MSG_CONTENT_SIZE];
} message;

volatile sig_atomic_t sighup;

void sighup_handler(int signal_num);

int main(void) {
  key_t key = ftok("OSSemTask_KFIXBJ_msgsnd.c", (int)'M');
  int msq_id = msgget(key, 0600);

  if (msq_id < 0) {
    perror("msgget() error");
    return -1;
  } else {
    printf("Message queue opened\n");
  }

  printf("PID: %d\n", (int)getpid());

  sighup = 0;
  signal(SIGHUP, sighup_handler);

  while (true) {
    printf("Waiting for signal...\n");
    pause();

    if (sighup) {
      int bytes = msgrcv(msq_id, &message, MSG_CONTENT_SIZE, 1, 0);
      printf("Received: \"%s\" - %d bytes\n", message.msg_content, bytes);
      sighup = 0;
    }
  }

  return 0;
}

void sighup_handler(int signal_num) {
  sighup = 1;
}
