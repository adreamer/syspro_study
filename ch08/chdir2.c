
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void main() {
    int swd_fd, ret;
    char *cwd;

    swd_fd = open(".", O_RDONLY);
    if (swd_fd == -1) {
        perror("open");
        exit(1);
    }

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

    ret = fchdir(swd_fd);
    if (ret) {
        perror("fchdir");
        exit(1);
    }

    cwd = getcwd(NULL, 0);
    if (!cwd) {
        perror("getcwd");
        exit(1);
    }
    printf("cur dir = %s\n", cwd);
    free(cwd);
    
    ret = close(swd_fd);
    if(ret) {
        perror("close");
        exit(1);
    }
}