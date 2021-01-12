#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define READ_LENGTH 512
#define ACCEPT_STDIN 0

//Implementing my own "cat" utility
void cat(FILE *fd) {

    if (!fd) {
        char buffer[READ_LENGTH];
        while(fgets(buffer, READ_LENGTH, stdin)) {
            printf("%s", buffer);
        }
    }
    else {
        char buffer[READ_LENGTH];
        while(fgets(buffer, READ_LENGTH, fd)) {
            printf("%s", buffer);
        }
    }
}


int main(int argc, char *argv[]) {

#if ACCEPT_STDIN == 1
    if (argc == 1) {
        cat(NULL);
    }
#endif
    int count = 1;
    while (count < argc) {
        FILE *fd = fopen(argv[count++], "r");
        if (fd == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        cat(fd);
        fclose(fd);
    }
    return 0;
}