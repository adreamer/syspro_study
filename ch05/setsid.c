#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
	pid_t pid;
	pid_t sid;
	pid = fork();
	if (pid == -1) {
		perror("fork");
		return -1;
	} else if (pid != 0)
		exit(0);

	sid = getsid(0);
	if (sid == -1) {
		perror("getsid");
	}
	printf("cur sid:%d\n",sid);
	if ((sid = setsid()) == -1) {
		perror("setsid");
		return -1;
	}

	printf("sid:%d\n",sid);
}

