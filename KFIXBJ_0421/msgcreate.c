#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg_buffer {
  long msg_type;
  char msg_content[128];
} message;

int main(void) {
  key_t key;
  int msg_id;

  key = ftok("msgcreate.c", (int)'M');
  msg_id = msgget(key, 0664 | IPC_CREAT);
  message.msg_type = 1;

  strcpy(message.msg_content, "KFIXBJ\n");
  msgsnd(msg_id, &message, sizeof(message), 0);
  printf("Sent: %s", message.msg_content);

  return 0;
}
