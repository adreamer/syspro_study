#include <stdlib.h>
#include <stdio.h>

void cleanup1() {
	printf("Cleanup 1 Called\n");
}

void cleanup2(int status, void *arg) {
	printf("Cleanup 2 Called: %ld.\n", (long) arg);
}

int main() {
	atexit(cleanup1);
	on_exit(cleanup2, (void*)20);

	exit(0);

}
