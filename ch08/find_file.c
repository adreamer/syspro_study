#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

int find_file_in_dir(const char *path, const char *file) {
    struct dirent *entry;
    int ret = 1;
    DIR *dir;

    dir = opendir(path);

    errno = 0;
    while((entry = readdir(dir)) != NULL) {
        if(strcmp(entry->d_name, file) == 0) {
            ret = 0;
            break;
        }
    }

    if (errno && !entry)
        perror("readdir");

    closedir(dir);
    return ret;
}

void main(int argc, char *argv[]) {
    char *path, *file;
    int ret;

    if (argc < 3) {
        printf("usage: %s path name\n", argv[0]);
        exit(1);
    }

    path = argv[1], file = argv[2];

    ret = find_file_in_dir(path, file);
    if (ret == 0) {
        printf("found\n");
    } else {
        printf("not found\n");
    }
}