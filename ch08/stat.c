#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void main(int argc, char* argv[]) {
	char * path;
	struct stat f_stat;
       	path = argv[1];
	if (stat(path, &f_stat) != 0) {
		perror("stat");
		exit(1);
	}

	printf("file %s - inode: %ld uid: %d bytes: %ld\n", path, f_stat.st_ino, f_stat.st_uid, f_stat.st_size);
}


