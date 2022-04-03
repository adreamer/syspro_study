#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main() {
	pid_t newsid, newpid;
	printf("PID: %d PPID: %d PGID: %d SID: %d\n", (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));

	if ((newpid = fork()) == -1)
		perror("fork");
	if (newpid != 0) {
		printf("[Parent] PID: %d PPID: %d PGID: %d SID: %d\n", (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
		return 0;
	}
	printf("[Child] PID: %d PPID: %d PGID: %d SID: %d\n", (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
	newsid = setsid();
	if (newsid == -1)
		perror("setsid");
	printf("[New Session] PID: %d PPID: %d PGID: %d SID: %d\n", (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));

	if ((newpid = fork()) == -1)
		perror("fork");
	if (newpid != 0) {
		printf("[Parent] PID: %d PPID: %d PGID: %d SID: %d\n", (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
		return 0;
	}
	//sleep(500);
	printf("[Child] PID: %d PPID: %d PGID: %d SID: %d\n", (int)getpid(), (int)getppid(), (int)getpgrp(), (int)getsid(0));
}
