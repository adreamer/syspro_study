#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <string.h>

int main() {
	struct rlimit rlim;
	int ret;

	ret = getrlimit(RLIMIT_CORE, &rlim);
	if (ret == -1) {
		perror("getrlimit");
		return 1;
	}

	printf("RLIMIT_CORE limits: soft=%ld hard=%ld\n", rlim.rlim_cur, rlim.rlim_max);

	memset(&rlim, 0, sizeof(struct rlimit));
	rlim.rlim_cur = 32 * 1024 * 1024;
	rlim.rlim_max = RLIM_INFINITY;
	ret = setrlimit(RLIMIT_CORE, &rlim);
	if (ret == -1) {
		perror("setrlimit");
		return 1;
	}
	ret = getrlimit(RLIMIT_CORE, &rlim);
	printf("RLIMIT_CORE limits: soft=%ld hard=%ld\n", rlim.rlim_cur, rlim.rlim_max);
}
