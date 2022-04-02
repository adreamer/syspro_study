#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *source;
	int sourcefd;
	int n, line = 1;
	char c;

	if (argc != 2) {
		printf("cat file\n");
		exit(1);
	}

	source = argv[1];

	sourcefd = open(source, O_RDONLY);
	if (sourcefd == -1) {
		perror("Source Open");
		exit(1);
	}

	printf("%d ", line++);

	while ((n = read(sourcefd, &c, sizeof(char))) > 0) {
		if (fputc(c, stdout) == EOF)
			perror("Write");
		if (c == '\n') {
			printf("%d ", line++);
		}
	}

	if (n == -1) perror("Read");


	close(sourcefd);

	return 1;
}
