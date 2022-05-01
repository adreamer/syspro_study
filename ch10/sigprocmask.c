#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(void) {
    sigset_t set, oldset, pendingset;

    sigemptyset(&set);
    sigemptyset(&oldset);
    sigemptyset(&pendingset);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("SIGINT, SIGQUIT Blocked! (Will Print)\n");
    sleep(5);

    if (sigpending(&pendingset) == 0) {
        printf("\nPending Signal: ===\n");
        if (sigismember(&pendingset, SIGQUIT))
            printf("SIGQUIT\n");
        if (sigismember(&pendingset, SIGINT))
            printf("SIGINT\n");
        printf("=== \n");
    }

    sigdelset(&set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &set, &oldset);

    printf("SIGQUIT not blocked\n");

    sleep(5);

    set=oldset;
    sigprocmask(SIG_SETMASK, &set, NULL);

    printf("SIGINT, SIGQUIT Blocked again!\n");

    sleep(5);

    //sigprocmask(SIG_UNBLOCK, &set, NULL);
    //printf("All signal unblocked\n");
    printf("Suspend\n");
    sigemptyset(&set);
    sigsuspend(&set);
    return 0;
}