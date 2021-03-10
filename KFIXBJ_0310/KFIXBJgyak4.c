#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void) {
    int status;
    int pid = fork();

    if (pid < 0) {
        perror("fork error");
        return -1;
    } else if (pid == 0) {
        status = execlp("ls", "ls", (char*)NULL);

        if (status < 0) {
            perror("execlp error");
            return -2;
        }
    } else {
        status = waitpid(pid, NULL, 0);

        if (status < 0) {
            perror("wait error");
            return -3;
        }

        printf("child terminated\n");
    }
    
    return 0;
}
