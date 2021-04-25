#include <stdio.h>
#include <string.h>
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
  struct shm_segm {
		int length;
		char content[SHM_SIZE - sizeof(int)];
	} *segm;

  shm_id = shmget(key, shm_size, shm_flag);

  if (shm_id < 0) {
    perror("shmget call unsuccessful\n");
    return -1;
  }

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

  return 0;
}
