#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	pid_t pid;
	switch (pid = fork()) {
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			printf("Child - My: %d Parent: %d\n", (int)getpid(), (int)getppid());
			break;
		default:
			printf("Parent - My: %d Parent: %d Child: %d\n",
			       (int)getpid(), (int)getppid(), (int)pid);
			break;
	}
	printf("End\n");
}
