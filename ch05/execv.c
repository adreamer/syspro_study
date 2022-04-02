#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	char *argv[3];

	printf("Before\n");

	argv[0] = "ls";
	argv[1] = "-a";
	argv[2]= NULL;
	if (execv("/usr/bin/ls", argv) == -1) {
		perror("execv");
		exit(1);
	}

	printf("After\n");
}
