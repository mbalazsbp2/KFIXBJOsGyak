#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_OF_SEMS 5

union semun {
  int              val;   // Value for SETVAL
  struct semid_ds *buf;   // Buffer for IPC_STAT, IPC_SET
  unsigned short  *array; // Array for GETALL, SETALL
  struct seminfo  *__buf; // Buffer for IPC_INFO (Linux-specific)
};

int main(void) {
  key_t key = ftok("gyak11_2_semset.c", (int)'S');
  int flag = 00666 | IPC_CREAT;
  int num_of_sems = NUM_OF_SEMS;
  int sem_id = semget(key, num_of_sems, flag);

  if (sem_id < 0) {
    perror("semget unsuccessful");
    return -1;
  } else {
    printf("Semaphore ID: %d\n", sem_id);
  }

  int command = IPC_RMID;
  union semun argument;

  int status = semctl(sem_id, 0, command, argument);

  if (status < 0) {
    perror("remove unsuccessful");
    return -1;
  } else {
    printf("Semaphore set removed\n");
  }
  
  return 0;
}
