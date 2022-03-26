#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void main() {
	printf("UID=%d EUID=%d\n",getuid(),geteuid());
	if (execlp("ls", "ls", NULL) == -1) {
		perror("execlp");
		exit(1);
	}
}
