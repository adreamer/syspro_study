#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <unistd.h>

void main() {
	cpu_set_t set;
	int ret, i;

	CPU_ZERO(&set);
	ret = sched_getaffinity(0, sizeof(cpu_set_t), &set);
	if (ret == -1)
		perror("sche_getaffinity");

	for (i = 0; i<CPU_SETSIZE; i++) {
		int cpu;
		cpu = CPU_ISSET(i, &set);
		printf("cpu=%i is %s\n", i, cpu ? "set":"unset");
	}

	CPU_ZERO(&set);
	CPU_SET(0, &set);
	CPU_CLR(1, &set);
	ret = sched_setaffinity(0, sizeof(cpu_set_t), &set);
	if (ret == -1)
		perror("sche_setaffinity");

	for (i = 0; i<CPU_SETSIZE; i++) {
		int cpu;

		cpu = CPU_ISSET(i, &set);
		printf("cpu=%i is %s\n", i, cpu ? "set":"unset");
	}
}
