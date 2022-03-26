#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

void main(int argc, char *argv[]) {
	int fd, val;
	fd = open("test.txt", O_CREAT);

	val = fcntl(fd, F_GETFD, 0);
	if (val & FD_CLOEXEC) {
		printf("CLOEXEC ON\n");
	} else {
		printf("CLOEXEC OFF\n");
	}

	if (argc > 1 && strcmp(argv[1], "--on") == 0) {
		printf("SET CLOEXEC ON\n");
		val |= FD_CLOEXEC;
		fcntl(fd, F_SETFD, val);
	}

	if(execl("./printfd.o", "printfd.o", NULL) == -1)
		perror("execlp");
}
