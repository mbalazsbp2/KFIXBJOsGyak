#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define NUM_OF_SEMS 5

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

  int command = GETVAL;

  for (int i = 0; i < num_of_sems; i++) {
    int current_sem_value = semctl(sem_id, i, command, NULL);
    printf("Semaphore %d: %d\n", i, current_sem_value);
  }
  
  return 0;
}
