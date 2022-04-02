#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int status;
	pid_t pid;

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		printf("--> Child\n");
		sleep(3);
		exit(3);
	}

	printf("--> Parent\n");

	while (waitpid(pid, &status, WNOHANG) == 0) {
		printf("Parent wait..\n");
		sleep(1);
	}

	printf("Child :%d\n", status>>8);
}
