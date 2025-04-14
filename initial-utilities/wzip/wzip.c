#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    int count = 0;
    int current_char = -1;  // Initialize to invalid character

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }

        int c;
        while ((c = fgetc(file)) != EOF) {
            if (current_char == -1) {
                // First character encountered
                current_char = c;
                count = 1;
            } else if (c == current_char) {
                // Same character, increment count
                count++;
            } else {
                // Different character, write out the current run
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&current_char, sizeof(char), 1, stdout);
                
                // Start a new run
                current_char = c;
                count = 1;
            }
        }

        fclose(file);
    }

    // Write the last run if there was any data
    if (current_char != -1) {
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&current_char, sizeof(char), 1, stdout);
    }

    return 0;
}