#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    pid_t pids[3];
    int n = sizeof(pids) / sizeof(pid_t);

    for (int i = 0; i < n; i++) {
        pids[i] = fork();

        if (pids[i] < 0) {
            perror("fork error");
            return -1;
        }
        
        else if (pids[i] == 0) {
            if (i == 0) {
                printf("Exit\n");
                exit(0);
            }

            else if (i == 1) {
                printf("Abort\n");
                abort();
            }

            else {
                printf("125 / 0 = %d", 125 / 0);
            }

            return 0;
        }
    }

    printf("Exit: PID %ld\n", (long)pids[0]);
    printf("Abort: PID %ld\n", (long)pids[1]);
    printf("Zerooszto: PID %ld\n", (long)pids[2]);

    int status;
    pid_t pid;

    while (n > 0) {
        pid = wait(&status);
        printf("PID %ld - befejezodesi allapot: %d\n", (long)pid, status);

        int torles = 0;

        for (int i = 0; i < n - 1; i++) {
            if (!torles) {
                torles = pids[i] == pid;
            }

            if (torles) {
                pids[i] = pids[i+1];
            }
        }

        n--;
    }

    printf("minden processz terminalodott\n");

    return 0;
}
