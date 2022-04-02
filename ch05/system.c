#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main() {
	int ret;
	ret = system("ps -ef | grep sshd > sshd.txt");
	printf("pid: %d\n", (int)getpid());
	printf("Return : %d\n", ret);
}
