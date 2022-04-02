#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	char *source, *dest;
	FILE *sourcefile, *destfile;
	int c;

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

	while ((c = fgetc(sourcefile)) != EOF) {
		if (fputc(c, destfile) == EOF)
			perror("Write");
	}

	if (ferror(sourcefile)) {
		perror("File Read");
	}


	fclose(sourcefile);
	fflush(destfile);
	fclose(destfile);

	return 1;
}
