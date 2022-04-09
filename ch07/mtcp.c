#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h> //times
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/uio.h> //iov
#include <sys/mman.h> //mmap
#include <string.h>
#include <pthread.h> //pthread

#define BUFFER_SIZE BUFSIZ

char *destmap;

struct th_arg {
	struct iovec *iov;
	long index;
	int thread_num;
};

void *consumer(void *ptr)
{
	struct th_arg tharg = *(struct th_arg *)ptr;
	struct iovec iov = *(tharg.iov);

	//printf("[Thread %d] Start. index %ld\n", tharg.thread_num, tharg.index);

	memcpy(destmap + tharg.index, iov.iov_base, iov.iov_len);

	//printf("[Thread %d] wrote %ld bytes\n", tharg.thread_num, iov.iov_len);
	return ptr;
}

void producer(int thread_num, char *source, char *dest)
{
	int sourcefd, destfd;
	mode_t mode;
	struct iovec iov[thread_num];
	char buf[thread_num][BUFFER_SIZE];
	int nr;
	int eof = 0;
	pthread_t thread[thread_num];
	int ret;
	struct th_arg tharg[thread_num];
	struct stat sb;
	long index = 0;

	sourcefd = open(source, O_RDONLY);
	if (sourcefd == -1)
	{
		perror("Source Open");
		exit(1);
	}

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	destfd = open(dest, O_CREAT | O_RDWR | O_TRUNC, mode);
	if (destfd == -1)
	{
		close(sourcefd);
		perror("Dest Open");
		exit(1);
	}

	// get source size
    if (fstat(sourcefd, &sb) == -1) {
        perror("fstat");
        exit(1);
    }

	// set dest size
    if (truncate(dest, sb.st_size) == -1) {
        perror("truncate");
        exit(1);
    }

	// mmap dest
	destmap = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, destfd, 0);
    if (destmap == MAP_FAILED) {
	    perror("mmap");
	    exit(1);
    }

	// prepare iov, thread
	for (int i = 0; i < thread_num; i++)
	{
		iov[i].iov_base = buf[i];
		iov[i].iov_len = sizeof(buf[i]);
		tharg[i].iov = &iov[i];
		tharg[i].thread_num = i;
	}
	while (!eof)
	{
		nr = readv(sourcefd, iov, thread_num); // vector read
		if (nr == -1)
		{
			perror("readv");
			exit(1);
		}
		// calculate iov_len(remaining)
		if (nr < BUFFER_SIZE * thread_num)
		{
			int remain = nr;
			for (int i = 0; i < thread_num; i++)
			{
				if (remain < BUFFER_SIZE)
				{
					iov[i].iov_len = remain;
					remain = 0;
				}
				else
				{
					remain -= BUFFER_SIZE;
					if (remain < 0) {
						remain = 0;
					}
				}
			}
			eof = 1;
		}
		//printf("read %d bytes\n", nr);

		for (int i=0; i<thread_num; i++) {
			tharg[i].index = index;
			//printf("[Create Thread %d] Index: %ld\n", i, index);
			pthread_create(&thread[i], NULL, consumer, (void*)&tharg[i]);
			index += BUFFER_SIZE;
		}

		for (int i=0; i<thread_num; i++) {
			//printf("[Join Thread %d]\n", i);
			pthread_join(thread[i], NULL);
			//printf("[Join Thread %d] Done\n", i);
		}
	}

	msync(destmap, sb.st_size, MS_ASYNC);
	munmap(destmap, sb.st_size);
	
	close(sourcefd);
	close(destfd);
}

int main(int argc, char *argv[])
{
	int thread_num;
	char *source, *dest;
	struct tms buf;
	clock_t ct, t1, t2;

	if (argc < 4)
	{
		printf("%s thread_num source_file target_file\n", argv[0]);
		exit(1);
	}

	thread_num = atoi(argv[1]);
	source = argv[2];
	dest = argv[3];

	ct = sysconf(_SC_CLK_TCK);

	if ((t1 = times(&buf)) == -1) {
		perror("times 1");
		exit(1);
	}
	producer(thread_num, source, dest);
	if ((t2 = times(&buf)) == -1) {
		perror("times 2");
		exit(1);
	}

	printf("Time : %.1f sec\n", (double)(t2 - t1) / ct);

	return 0;
}
