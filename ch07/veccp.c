#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h> //times
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h> //iov
#include <string.h>

int main(int argc, char *argv[]) {
	char *source, *dest;
	int sourcefd, destfd;
	mode_t mode;
	char buf[3][BUFSIZ];
	int nr;
    struct iovec iov[3];
    int eof = 0;

	// time
	struct tms timebuf;
	clock_t ct, t1, t2;

	if (argc < 3) {
		printf("cp source_file target_file\n");
		exit(1);
	}

	source = argv[1];
	dest = argv[2];

	ct = sysconf(_SC_CLK_TCK);

	if ((t1 = times(&timebuf)) == -1) {
		perror("times 1");
		exit(1);
	}

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

    for (int i = 0; i < 3; i++) {
		iov[i].iov_base = buf[i];
		iov[i].iov_len = sizeof(buf[i]);
	}
    while (!eof) {
   	nr = readv(sourcefd, iov, 3);
    	if (nr == -1) {
		perror ("readv");
		return 1;
	}
    if (nr < BUFSIZ * 3) {
		int remain = nr;
		for (int i=0; i<3; i++) {
			if (remain < BUFSIZ) {
				iov[i].iov_len = remain;
				remain = 0;
			} else {
				remain -= BUFSIZ;
			}
		}
        	eof = 1;
    	}
    	//printf("read %d bytes\n", nr);
    	nr = writev(destfd, iov, 3);
    	if (nr == -1) {
            perror ("writev");
            return 1;
        }
	    //printf("wrote %d bytes\n", nr);
    }

	close(sourcefd);
	close(destfd);

	if ((t2 = times(&timebuf)) == -1) {
		perror("times 2");
		exit(1);
	}

    printf("Time : %.1f sec\n", (double)(t2 - t1) / ct);

	return 0;
}

