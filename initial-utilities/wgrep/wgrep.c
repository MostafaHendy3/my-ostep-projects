#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *searchterm = argv[1];

    if (argc == 2) {
        char buffer[1024];
        while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (strstr(buffer, searchterm) != NULL) {
                printf("%s", buffer);
            }
        }
    } else {
    for (int i = 2; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        char *line = NULL;
        size_t len = 0;
        while(getline(&line, &len, file) != -1) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
        free(line);

            fclose(file);
        }
    }

    return 0;
}