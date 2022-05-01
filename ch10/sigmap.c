#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("SIG[2] = %s\n", sys_siglist[2]);
    psignal(2, "TEST");
    printf("SIG[2] = %s\n", strsignal(2));
}