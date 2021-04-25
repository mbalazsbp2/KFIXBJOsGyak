#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 128

struct msg_buffer {
  long msg_type;
  char msg_content[MSG_SIZE];
} message;

int main(void) {
  key_t key;
  int msg_id;

  key = ftok("gyak10_2_create.c", (int)'M');
  msg_id = msgget(key, 0664 | IPC_CREAT);
  message.msg_type = 1;

  int exit = 0;

  while (!exit) {
      printf("In: ");
      fgets(message.msg_content, MSG_SIZE, stdin);

      if (strcmp(message.msg_content, "exit\n") == 0) {
          exit = 1;
          continue;
      }

      msgsnd(msg_id, &message, sizeof(message), 0);
      printf("Sent: %s", message.msg_content);
  }
  
  printf("Exiting...\n");

  return 0;
}
