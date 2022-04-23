#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
    char *option, *path;

    if (argc < 3) {
        printf("usage: linker [link|symlink|unlink] path (newpath)\n");
        exit(1);
    }

    option = argv[1];
    path = argv[2];

    if (strcmp(option, "link") == 0) {
        if (argc < 4) {
            printf("usage: linker [link|symlink|unlink] path (newpath)\n");
            exit(1);
        }
        if (link(path, argv[3]) == -1) {
            perror("link");
            exit(1);
        }
    } else if (strcmp(option, "symlink") == 0) {
        if (argc < 4) {
            printf("usage: linker [link|symlink|unlink] path (newpath)\n");
            exit(1);
        }
        if (symlink(path, argv[3]) == -1) {
            perror("symlink");
            exit(1);
        }
    } else if (strcmp(option, "unlink") == 0) {
        if (unlink(path) == -1) {
            perror("unlink");
            exit(1);
        }
    }
}