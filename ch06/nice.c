#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void main() {
	int ret;
	errno = 0;
	printf("nice: %d\n", nice(0));
	ret = nice(10);
	if (ret == -1 && errno != 0)
		perror("nice");
	else
		printf("new nice: %d\n", ret);
}
