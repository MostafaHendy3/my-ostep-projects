#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    
    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wunzip: cannot open file\n");
            return 1;
        }

        int count;
        char c;
        while (fread(&count, sizeof(int), 1, file) == 1 && fread(&c, sizeof(char), 1, file) == 1) {
            for (int j = 0; j < count; j++) {
                printf("%c", c);
            }
        }

        fclose(file);
    }

   
    return 0;
}