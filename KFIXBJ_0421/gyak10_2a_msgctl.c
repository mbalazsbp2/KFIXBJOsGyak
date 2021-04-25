#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
  long msg_type;
  char msg_content[128];
} message;

int get_num_of_msgs(int msg_id);
void print_msg(int msg_id);

int main(void) {
  key_t key;
  int msg_id;

  key = ftok("gyak10_2_create.c", (int)'M');
  msg_id = msgget(key, 0664 | IPC_CREAT);

  int should_exit = 0;

  while (!should_exit) {
    int cmd;
    int valid_cmd = 0;

    while (!valid_cmd) {
      printf("\nAvailable commands:\n");
      printf("-> 1: number of messages\n");
      printf("-> 2: read one message\n");
      printf("-> 3: read all messages\n");
      printf("-> 4: delete message queue\n");
      printf("-> 0: exit\n");
      printf("Choose command: ");
      scanf("%d",&cmd);

      if (0 <= cmd && cmd <= 4) {
        valid_cmd = 1;
      }
    }

    int num_of_msgs;

    switch (cmd) {
      case 0:
        should_exit = 1;
        break;
      case 1:
        printf("Number of messages: %d\n", get_num_of_msgs(msg_id));
        break;
      case 2:
        print_msg(msg_id);
        break;
      case 3:
        num_of_msgs = get_num_of_msgs(msg_id);

        for (int i = 0; i < num_of_msgs; i++) {
          print_msg(msg_id);
        }

        break;
      case 4:
        msgctl(msg_id, IPC_RMID, NULL);
        printf("Removed message queue\n");
        break;
    }
  }

  return 0;
}

int get_num_of_msgs(int msg_id) {
  struct msqid_ds stat;
  msgctl(msg_id, IPC_STAT, &stat);
  return stat.msg_qnum;
}

void print_msg(int msg_id) {
  msgrcv(msg_id, &message, sizeof(message), 1, 0);
  printf("Received: %s", message.msg_content);
}
