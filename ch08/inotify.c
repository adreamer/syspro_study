#include <sys/inotify.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define BUF_LEN 256

void main(int argc, char *argv[]) {
    int fd, wd, i = 0, ret;
    unsigned int queue_len;
    ssize_t len;
    char *path;
    char buf[BUF_LEN] __attribute__((aligned(4)));

    if (argc < 2) {
        printf("usage : %s path\n", argv[0]);
        exit(1);
    }

    path = argv[1];

    fd = inotify_init1(0);
    if (fd == -1) {
        perror("inotify_init1");
        exit(1);
    }

    if ((wd = inotify_add_watch(fd, path, IN_ACCESS)) == -1) {
        perror("inotify_add_watch");
        exit(1);
    }

    ret = ioctl(fd, FIONREAD, &queue_len);
    if (ret < 0) {
        perror("ioctl");
    } else {
        printf("%u bytes pending in queue\n", queue_len);
    }
    
    len = read(fd, buf, BUF_LEN);
    while (i < len) {
        struct inotify_event *event = (struct inotify_event*)&buf[i];

        printf("wd = %d mask=%d cookie=%d len=%d dir=%s\n",
            event->wd, event->mask,
            event->cookie, event->len,
            (event->mask & IN_ISDIR) ? "yes" : "no");

        if(event->len) {
            printf("name=%s\n", event->name);
        }
        i += sizeof(struct inotify_event) + event->len;
    }

    if (inotify_rm_watch(fd, wd)) {
        perror("inotify_rm_watch");
    }

    if (close(fd) == -1) {
        perror("close");
    }
}