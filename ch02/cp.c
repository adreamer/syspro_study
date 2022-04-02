#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BUF_LEN 1024

int main(int argc, char *argv[]) {
	char *source, *dest;
	int sourcefd, destfd;
	mode_t mode;
	char buf[BUF_LEN];
	int n;

	if (argc < 3) {
		printf("cp source_file target_file\n");
		exit(1);
	}

	source = argv[1];
	dest = argv[2];

	sourcefd = open(source, O_RDONLY);
	if (sourcefd == -1) {
		perror("Source Open");
		exit(1);
	}

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	destfd = open(dest, O_CREAT | O_WRONLY | O_TRUNC, mode);
	if (destfd == -1) {
		close(sourcefd);
		perror("Dest Open");
		exit(1);
	}

	while ((n = read(sourcefd, buf, BUF_LEN)) > 0) {
		if (write(destfd, buf, n) != n)
			perror("Write");
	}

	if (n == -1) perror("Read");

	close(sourcefd);
	close(destfd);

	return 1;
}
