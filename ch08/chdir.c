#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void main() {
    char *swd, *cwd;
    int ret;

    swd = getcwd(NULL, 0);
    if (!swd) {
        perror("getcwd");
        exit(1);
    }
    printf("saved dir = %s\n", swd);

    ret = chdir("/usr/lib");
    if (ret) {
        perror("chdir");
        exit(1);
    }

    cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("getcwd");
        exit(1);
    }
    printf("cur dir = %s\n", cwd);
    free(cwd);

    ret = chdir(swd);
    if(ret) {
        perror("chdir");
        exit(1);
    }
    free(swd);
}