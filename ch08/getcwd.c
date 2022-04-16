#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
    char cwd[256], *cwd2, *cwd3;

    if (!getcwd(cwd, 256)) {
        perror("getcwd");
        exit(1);
    }

    printf("cwd = %s\n", cwd);

    cwd2 = getcwd(NULL, 0);
    if(!cwd2) {
        perror("getcwd2");
        exit(1);
    }
    printf("cwd2 = %s\n", cwd2);
    free(cwd2);

    cwd3 = get_current_dir_name();
    if(!cwd3) {
        perror("get_current_dir_name");
        exit(1);
    }

    printf("cwd3 = %s\n", cwd3);
    free(cwd3);
}