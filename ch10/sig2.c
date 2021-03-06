#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
    if (signo == SIGINT) {
        printf("Caught SIGINT!\n");
    } else if (signo == SIGTERM) {
        printf("Caught SIGTERM!\n");
    } else {
        fprintf(stderr, "Unexpected Signal!\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}

int main(void) {
    int ret;

    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGINT!\n");
        exit(EXIT_FAILURE);
    }

    if(signal(SIGTERM, signal_handler) == SIG_ERR) {
        fprintf(stderr, "Cannot handle SIGTERM!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGPROF, SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "Cannot reset SIGPROF!\n");
        exit(EXIT_FAILURE);
    }

    if (signal(SIGHUP, SIG_IGN) == SIG_ERR) {
        fprintf(stderr, "Cannot ignore SIGHUP!\n");
        exit(EXIT_FAILURE);
    }

    ret = kill (getpid(), SIGHUP);
    if (ret) perror("kill");

    ret = raise(SIGPROF);
    if (ret) printf("error = %d\n", ret);

    for(;;)
        pause();
    
    return 0;
}