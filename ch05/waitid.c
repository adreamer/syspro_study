#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	int status;
	pid_t pid;
	siginfo_t infop;

	if ((pid = fork()) < 0) {
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		printf("-> Child\n");
		sleep(2);
		exit(2);
	}

	printf("->Parent\n");
	while (waitid(P_PID, pid, &infop, WEXITED) != 0) {
		printf("Parent wait..\n");
	}
	printf("Child PID:%d\n", infop.si_pid);
	printf("Child UID:%d\n", infop.si_uid);
	printf("Child Code:%d\n", infop.si_code);
	printf("Child Status:%d\n", infop.si_status);
}
