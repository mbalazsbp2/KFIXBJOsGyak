#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 123456L
#define SHM_SIZE 512

int main(void) {
  int shm_id;
  key_t key = SHM_KEY;
  int shm_size = SHM_SIZE;
  int shm_flag = 0;

  // parent
  shm_id = shmget(key, shm_size, shm_flag);

  if (shm_id < 0) {
    printf("Creating segment...\n");
    shm_flag = 00666 | IPC_CREAT;
    shm_id = shmget(key, shm_size, shm_flag);

    if (shm_id < 0) {
      perror("shmget call unsuccessful\n");
      return -1;
    }
  } else {
    printf("Segment already exists\n");
  }

  printf("Segment ID: %d\n", shm_id);

  int pid = fork();

  if (pid < 0) {
      perror("fork error");
      return -1;
  } else if (pid == 0) {
      // child
      struct shmid_ds stat;
      struct shm_segm {
        int length;
        char content[SHM_SIZE - sizeof(int)];
      } *segm;

      // attach
      shm_flag = 00666 | SHM_RND;
      segm = (struct shm_segm*)shmat(shm_id, NULL, shm_flag);
      
      if (segm == (void*)-1) {
        perror("attach unsuccessful");
        return -1;
      }

      // read - write
      if (strlen(segm->content) > 0) {
        printf("Old content: %s", segm->content);
        printf("- length: %d\n" ,segm->length);
      }

      printf("New content: ");
      fgets(segm->content, SHM_SIZE - sizeof(int), stdin);
      segm->length = strlen(segm->content);
      printf("New content added: %s", segm->content);

      // detach
      shmdt(segm);

      // control
      int should_exit = 0;

      while (!should_exit) {
        int cmd;
        int valid_cmd = 0;

        while (!valid_cmd) {
          printf("Available commands:\n");
          printf("-> 1: status\n");
          printf("-> 2: remove\n");
          printf("-> 0: exit\n");
          printf("Choose command: ");
          scanf("%d",&cmd);

          if (0 <= cmd && cmd <= 2) {
            valid_cmd = 1;
          }
        }

        switch (cmd) {
          case 0:
            should_exit = 1;
            break;
          case 1:
            shmctl(shm_id, IPC_STAT, &stat);
            printf("Segment size: %d\n", (int)stat.shm_segsz);
            printf("Last operation: PID %d\n", stat.shm_lpid);
            break;
          case 2:
            shmctl(shm_id, IPC_RMID, NULL);
            printf("Segment deleted\n");
            break;
        }
      }

      return 0;
  }

  // wait and exit
  wait(NULL);
  return 0;
}
