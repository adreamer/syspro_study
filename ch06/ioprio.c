#include <unistd.h>
#include <stdio.h>

void main() {
	int ret;
	ret = ioprio_get(IOPRIO_WHO_PROCESS, 0);
	printf("nice = %d\n",ret);
}
