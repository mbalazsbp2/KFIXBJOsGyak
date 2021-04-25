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
  
  return 0;
}
