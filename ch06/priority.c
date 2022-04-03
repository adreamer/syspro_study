#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

void main() {
	int ret;

	ret = getpriority(PRIO_USER, 0);
	printf("nice value is %d\n", ret);
	ret = setpriority(PRIO_PGRP, 0, 10);
	if (ret == -1)
		perror("setpriority");
	printf("new nice : %d\n", ret);
}
