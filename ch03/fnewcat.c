#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *source;
	FILE *sourcefile;
	int c;

	if (argc != 2) {
		printf("cat file\n");
		exit(1);
	}

	source = argv[1];

	sourcefile = fopen(source, "r");
	if (!sourcefile) {
		perror("Source Open");
		exit(1);
	}

	while ((c = fgetc(sourcefile)) != EOF) {
		if (fputc(c, stdout) == EOF)
			perror("Write");
	}

	if (ferror(sourcefile)) {
		perror("File Read");
	}


	fclose(sourcefile);

	return 1;
}
