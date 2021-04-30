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

  struct sembuf sem_op_buf;
  sem_op_buf.sem_op = 1;
  sem_op_buf.sem_flg = 0666;

  printf("Semaphore number: ");
  scanf("%hu", &sem_op_buf.sem_num);

  if (0 <= sem_op_buf.sem_num && sem_op_buf.sem_num < num_of_sems) {
    int status = semop(sem_id, &sem_op_buf, 1);
    printf("Incrementing semaphore %d - Status: %d", i, status);
  } else {
    perror("no such semaphore");
    return -1;
  }
  
  return 0;
}
