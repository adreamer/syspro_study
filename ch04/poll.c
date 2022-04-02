#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

#define TIMEOUT 5
#define BUF_LEN 255

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

int main(void) {
    int infd, outfd;
    struct pollfd fds[4];
    int ret;

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

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    fds[1].fd = STDOUT_FILENO;
    fds[1].events = POLLOUT;

    fds[2].fd = infd;
    fds[2].events = POLLIN;

    fds[3].fd = outfd;
    fds[3].events = POLLOUT;

    while (1) {
        ret = poll(fds, 4, TIMEOUT * 1000);
        if (ret == -1) {
            perror ("select");
            close(infd);
            close(outfd);
            return 1;
        } else if (!ret) {
            printf ("%d seconds elapsed.\n", TIMEOUT);
            close(infd);
            close(outfd);
            return 0;
        }

        if (fds[0].revents & POLLIN) {
            char buf[BUF_LEN+1];
            int len;

            len = read(STDIN_FILENO, buf, BUF_LEN);
            if (len == -1) {
                perror ("error");
                close(infd);
                close(outfd);
                return 1;
            }

            if (len) {
                buf[len] = '\0';
                printf ("read: %s\n", buf);
                write(outfd, buf, len);
            }
        }

        if (fds[2].revents & POLLIN) {
            char buf[BUF_LEN+1];
            int len;

            len = read(infd, buf, BUF_LEN);
            if (len == -1) {
                perror ("error");
                close(infd);
                close(outfd);
                return 1;
            }

            if (len) {
                buf[len] = '\0';
                printf ("read: %s\n", buf);
                write(outfd, buf, len);
            }
        }
    }
    fprintf (stderr, "This should not happan!\n");
    return 1;
}
