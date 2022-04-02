#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char *source, *dest;
	int sourcefd, destfd;
	mode_t mode;
    char *sourcemap, *destmap;
    struct stat sb;


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
	destfd = open(dest, O_CREAT | O_RDWR | O_TRUNC, mode);
	if (destfd == -1) {
		close(sourcefd);
		perror("Dest Open");
		exit(1);
	}

    if (fstat(sourcefd, &sb) == -1) {
        perror("fstat");
        exit(1);
    }

    if (truncate(dest, sb.st_size) == -1) {
        perror("truncate");
        exit(1);
    }

    sourcemap = mmap(NULL, sb.st_size, PROT_READ, MAP_SHARED, sourcefd, 0);
    if (sourcemap == MAP_FAILED) {
	    perror("mmap");
	    exit(1);
    }
    destmap = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, destfd, 0);
    if (destmap == MAP_FAILED) {
	    munmap(sourcemap, sb.st_size);
	    perror("mmap2");
	    exit(1);
    }

    memcpy(destmap, sourcemap, sb.st_size);

    /*
    for(int i=0; i<sb.st_size; i++) {
        destmap[i] = sourcemap[i];
    }*/

	msync(destmap, sb.st_size, MS_ASYNC);

	    munmap(sourcemap, sb.st_size);
	    munmap(destmap, sb.st_size);
	close(sourcefd);
	close(destfd);

	return 1;
}

