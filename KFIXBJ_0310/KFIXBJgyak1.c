#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int visszateresi_ertek;

    visszateresi_ertek = system("ls");
    printf("Az 'ls' hivas eredmenye: %d\n", visszateresi_ertek);

    visszateresi_ertek = system("jump");
    printf("A 'jump' hivas eredmenye: %d\n", visszateresi_ertek);
    
    return 0;
}
