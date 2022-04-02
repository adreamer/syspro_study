#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main() {
	pid_t pid;
	int i;

	if ((pid = fork()) == -1) {
		return -1;
	} else if (pid != 0) {
		exit(0);
	}

	if (setsid() == -1) {
		return -1;
	}

	if (chdir("/") == -1) {
		return -1;
	}

	for (i =0; i<FD_SETSIZE; i++) {
		close(i);
	}

	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);

	sleep(3);

	return 0;
}
