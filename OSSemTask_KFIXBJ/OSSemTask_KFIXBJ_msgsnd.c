#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdbool.h>
#include <unistd.h>

#define MSG_CONTENT_SIZE 1024

struct msg_buffer {
  long msg_type;
  char msg_content[MSG_CONTENT_SIZE];
} message;

volatile sig_atomic_t sighup;
volatile sig_atomic_t sigterm;

void sighup_handler(int signal_num);
void sigterm_handler(int signal_num);

int main(void) {
  key_t key = ftok("OSSemTask_KFIXBJ_msgsnd.c", (int)'M');
  int msq_id = msgget(key, 0600 | IPC_CREAT);

  if (msq_id < 0) {
    perror("msgget() error");
    return -1;
  } else {
    printf("Message queue created\n");
  }

  printf("PID: %d\n", (int)getpid());

  sighup = 0;
  sigterm = 0;
  signal(SIGHUP, sighup_handler);
  signal(SIGTERM, sigterm_handler);

  int num_of_msgs_sent = 0;
  message.msg_type = 1;

  while (true) {
    printf("Waiting for signal...\n");
    pause();

    if (sighup) {
      sprintf(message.msg_content, "KFIXBJ - Message %d", num_of_msgs_sent);
      int msg_size = strlen(message.msg_content) + 1;

      int status = msgsnd(msq_id, &message, msg_size, 0);
      printf("Sent: \"%s\" - Status: %d\n", message.msg_content, status);

      num_of_msgs_sent++;
      sighup = 0;
    } else if (sigterm) {
      msgctl(msq_id, IPC_RMID, NULL);
      printf("Message queue removed\n");
      return 0;
    }
  }

  return 0;
}

void sighup_handler(int signal_num) {
  sighup = 1;
}

void sigterm_handler(int signal_num) {
  sigterm = 1;
}
