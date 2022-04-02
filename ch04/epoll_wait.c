#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <stdlib.h>

#define MAX_EVENTS 64
#define TIMEOUT 5

#define CLOSEFD()({close(infd);close(outfd);})

void makepipe() {
    if (mkfifo("IN", 0666) == -1) {
        perror("mkfifo IN");
        //exit(1);
    }

    if (mkfifo("OUT", 0666) == -1) {
        perror("mkfifo OUT");
        //exit(1);
    }
}

int main() {
	struct epoll_event *events, inevent, outevent;
	int nr_events, i, epfd, infd, outfd, ret;

	makepipe();

	if ((infd = open("IN", O_RDONLY)) == -1) {
        	perror("Open IN");
        	exit(1);
    	}

    	if ((outfd = open("OUT", O_WRONLY)) == -1) {
        	close(infd);
        	perror("Open OUT");
        	exit(1);
    	}

	epfd = epoll_create1(0);

	inevent.data.fd = infd;
	inevent.events = EPOLLIN;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, infd, &inevent))
		perror("epoll_ctl");

	outevent.data.fd = outfd;
	outevent.events = EPOLLOUT;

	if(epoll_ctl(epfd, EPOLL_CTL_ADD, outfd, &outevent))
		perror("epoll_ctl out");

	events = malloc(sizeof(struct epoll_event) * MAX_EVENTS);
	if (!events) {
		perror("malloc");
		CLOSEFD();
		return 1;
	}

	nr_events = epoll_wait(epfd, events, MAX_EVENTS, TIMEOUT * 1000);
	if (nr_events < 0) {
		perror("epoll_wait");
		free(events);
		CLOSEFD();
		return 1;
	}

	for (i=0; i<nr_events; i++) {
		printf("event=%d on fd=%d\n",
				events[i].events,
				events[i].data.fd);
	}

	free(events);
	CLOSEFD();
	return 0;
}
