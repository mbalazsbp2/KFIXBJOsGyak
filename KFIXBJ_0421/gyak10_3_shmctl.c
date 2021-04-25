#include <stdio.h>
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
  struct shmid_ds stat;

  shm_id = shmget(key, shm_size, shm_flag);

  if (shm_id < 0) {
    perror("shmget call unsuccessful\n");
    return -1;
  }

  int cmd;
  int valid_cmd = 0;

  while (!valid_cmd) {
    printf("Available commands:\n");
    printf("-> 0: status\n");
    printf("-> 1: remove\n");
    printf("Choose command: ");
    scanf("%d",&cmd);

    if (0 <= cmd && cmd <= 1) {
      valid_cmd = 1;
    }
  }

  switch (cmd) {
    case 0:
      shmctl(shm_id, IPC_STAT, &stat);
      printf("Segment size: %d\n", (int)stat.shm_segsz);
      printf("Last operation: PID %d\n", stat.shm_lpid);
      break;
    case 1:
      shmctl(shm_id, IPC_RMID, NULL);
      printf("Segment deleted\n");
      break;
  }
  
  return 0;
}
