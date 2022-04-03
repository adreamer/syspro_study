#include <unistd.h>
#include <stdio.h>

int main() {
	printf("PID : %d\n", (int)getpid());
	printf("PPID :%d\n", (int)getppid());
	printf("PGRP : %d\n", (int)getpgrp());
	printf("PGID(0) : %d\n", (int)getpgid(0));
	printf("PGID(18020) :%d\n", (int)getpgid(18020));
	printf("SID : %d\n", (int)getsid(0));
}
