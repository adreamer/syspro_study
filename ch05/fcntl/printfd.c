#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>

void main() {
	DIR *dp;
	struct dirent *dent;
	char fdpath[64];
	int i=0;

	snprintf(fdpath, 64, "/proc/%i/fd/", getpid());
	dp = opendir(fdpath);

	while ((dent = readdir(dp))) {
		if (i++ < 2) continue;
		printf("Opened FD : %s\n", dent->d_name);
	}

	closedir(dp);
}
