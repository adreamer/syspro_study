#include <sched.h>
#include <stdio.h>

int main() {
	int policy, ret;
	struct sched_param sp = { .sched_priority = 1 };

	policy = sched_getscheduler(0);

	switch (policy) {
		case SCHED_OTHER:
			printf("Policy is normal\n");
			break;
		case SCHED_RR:
			printf("Policy is round-robin\n");
			break;
		case SCHED_FIFO:
			printf("Policy is FIFO\n");
			break;
		case -1:
			perror("sched_getscheduler");
			break;
		default:
			fprintf(stderr, "Unknown policy\n");
	}

	ret = sched_setscheduler(0, SCHED_RR, &sp);
	if (ret == -1) {
		perror("sched_setscheduler");
		return 1;
	}
	policy = sched_getscheduler(0);
	printf("Policy: %d\n", policy);
}
