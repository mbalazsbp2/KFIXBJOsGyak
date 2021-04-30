#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define NUM_OF_CHILDREN 3
#define SECONDS 3

union semun {
  int              val;   // Value for SETVAL
  struct semid_ds *buf;   // Buffer for IPC_STAT, IPC_SET
  unsigned short  *array; // Array for GETALL, SETALL
  struct seminfo  *__buf; // Buffer for IPC_INFO (Linux-specific)
};

void pass(int signal_num) {}

int main(void) {
  key_t key = ftok("gyak11_2a.c", (int)'S');
  int flag = 00666 | IPC_CREAT;
  int sem_id = semget(key, 1, flag);

  if (sem_id < 0) {
    perror("semget unsuccessful");
    return -1;
  } else {
    printf("Semaphore ID: %d\n", sem_id);
  }

  int command = SETVAL;
  union semun argument;
  argument.val = 0;

  int status = semctl(sem_id, 0, command, argument);
  printf("Setting semaphore to %d - Status: %d\n", argument.val, status);

  int num_of_children = NUM_OF_CHILDREN;

  for (int i = 0; i < NUM_OF_CHILDREN; i++) {
    int pid = fork();

    if (pid < 0) {
      perror("fork error");
      return -1;
    }

    if (pid == 0) {
      // children
      pid = (int)getpid();

      struct sembuf sem_op_buf[2];
      int status;

      // enter critical section
      sem_op_buf[0].sem_num = 0;
      sem_op_buf[0].sem_op = 0;
      sem_op_buf[0].sem_flg = 0666;

      sem_op_buf[1].sem_num = 0;
      sem_op_buf[1].sem_op = 1;
      sem_op_buf[1].sem_flg = 0666;

      printf("PID %d: waiting for semaphore\n", pid);
      status = semop(sem_id, sem_op_buf, 2);

      if (status < 0) {
        printf("PID %d:\n", pid);
        perror("cannot enter critical section");
        return -1;
      } else {
        printf("PID %d: entered critical section\n", pid);
        signal(SIGALRM, pass);
        alarm(SECONDS);
        pause();
      }

      // exit critical section
      sem_op_buf[0].sem_num = 0;
      sem_op_buf[0].sem_op = -1;
      sem_op_buf[0].sem_flg = 0666;

      status = semop(sem_id, sem_op_buf, 1);

      if (status < 0) {
        printf("PID %d:\n", pid);
        perror("cannot exit critical section");
        return -1;
      } else {
        printf("PID %d: exited critical section\n", pid);
      }

      return 0;
    }
  }

  while (num_of_children) {
    int pid = wait(NULL);
    printf("PID %d: terminated\n", pid);
    num_of_children--;
  }

  return 0;
}
