#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
  key_t key;
  int msg_id;

  key = ftok("msgcreate.c", (int)'M');
  msg_id = msgget(key, 0664 | IPC_CREAT);

  msgctl(msg_id, IPC_RMID, NULL);
  printf("Removed message queue\n");

  return 0;
}
