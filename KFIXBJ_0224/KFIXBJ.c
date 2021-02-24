#include <stdio.h>

int main(void) {
    char beolvasott[100];
    FILE *fp = fopen("vezeteknev.txt", "w+t");

    fprintf(fp, "Molnar\n");
    fseek(fp, 0L, SEEK_SET);
    fgets(beolvasott, sizeof(beolvasott) / sizeof(char), fp);
    printf("%s", beolvasott);
    fclose(fp);

    return 0;
}
