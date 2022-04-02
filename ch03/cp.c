#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *source, *dest;
	FILE *sourcefile, *destfile;
	mode_t mode;
	char buf[BUFSIZ];
	int n;

	if (argc < 3) {
		printf("cp source_file target_file\n");
		exit(1);
	}

	source = argv[1];
	dest = argv[2];

	sourcefile = fopen(source, "r");
	if (!sourcefile) {
		perror("Source Open");
		exit(1);
	}

	destfile = fopen(dest, "w");
	if (!destfile) {
		fclose(sourcefile);
		perror("Dest Open");
		exit(1);
	}

	while ((n = fread(buf, BUFSIZ, 1, sourcefile)) > 0) {
		if (fwrite(buf, BUFSIZ, 1, destfile) != n)
			perror("Write");
	}

	if (ferror(sourcefile)) {
		perror("File Read");
	}
	if (feof(sourcefile)) {
		int i = 0;
		while (buf[i] != EOF && i < BUFSIZ) {
			if (fputc(buf[i++], destfile) == EOF)
				perror("Write");
		}
	}


	fclose(sourcefile);
	fflush(destfile);
	fclose(destfile);

	return 1;
}
