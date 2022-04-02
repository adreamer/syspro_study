#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *source;
	int sourcefd;
	mode_t mode;
	char buf[BUFSIZ];
	int n;

	if (argc < 2) {
		printf("cp source_file\n");
		exit(1);
	}

	source = argv[1];

	sourcefd = open(source, O_RDONLY);
	if (sourcefd == -1) {
		perror("Source Open");
		exit(1);
	}

	while ((n = read(sourcefd, buf, BUFSIZ)) > 0) {
		printf("%d\n", n);
		printf("%s\n", buf);
	}

	if (n == -1) perror("Read");

	close(sourcefd);

	return 1;
}
