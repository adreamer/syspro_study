#include <sched.h>
#include <stdio.h>
#include <string.h>

int main() {
	struct sched_param sp, sp2;
	int ret;
	int min, max;
	struct timespec tp;

	sched_setscheduler(0, SCHED_RR, &sp);

	min = sched_get_priority_min(SCHED_RR);
	max = sched_get_priority_max(SCHED_RR);
	printf("SCHED_RR priority range %d - %d\n", min, max);

	ret = sched_rr_get_interval(0, &tp);
	if (ret == -1) {
		perror("sched_rr_get_interval");
		return 1;
	}

	printf("Our time quantum is %.2lf msec\n", (tp.tv_sec * 1000.0f) + (tp.tv_nsec / 1000000.0f));

	ret = sched_getparam(0, &sp);
	if (ret == -1) {
		perror("sched_getparam");
		return 1;
	}
	printf("Priority: %d\n", sp.sched_priority);
	memset(&sp, 0, sizeof(struct sched_param));
	sp.sched_priority = min;
	ret = sched_setparam(0, &sp);
	if (ret == -1) {
		perror("sched_setparam");
		return 1;
	}
	ret = sched_getparam(0, &sp);
	printf("Priority: %d\n", sp.sched_priority);
}
