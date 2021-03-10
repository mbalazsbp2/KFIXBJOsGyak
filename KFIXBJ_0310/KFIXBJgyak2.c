#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int exit = 0;
    char command[100];
    int command_size = sizeof(command) / sizeof(char);

    while (!exit) {
        printf("Adjon meg egy parancsot: ");
        fgets(command, command_size, stdin);

        if (strcmp(command, "exit\n") == 0) {
            exit = 1;
            continue;
        }

        system(command);
    }
    
    return 0;
}
