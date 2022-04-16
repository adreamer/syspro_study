#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define BUF_LEN BUFSIZ
#define DEBUG
#ifdef DEBUG
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif
    

int is_recursive = 0;

void copy(int sdirfd, char *source, char *dest);

void copy_file(int sdirfd, char *source, char *dest)
{
    int sourcefd;
    FILE *sourcefile, *destfile;
    int c;

    LOG("-copy file %s -> %s\n", source, dest);

    sourcefd = openat(sdirfd, source, O_RDONLY);
    sourcefile = fdopen(sourcefd, "r");
    if (!sourcefile)
    {
        perror("Source Open");
        exit(1);
    }

    destfile = fopen(dest, "w");
    if (!destfile)
    {
        fclose(sourcefile);
        perror("Dest Open");
        exit(1);
    }

    while ((c = fgetc(sourcefile)) != EOF) {
		if (fputc(c, destfile) == EOF)
			perror("Write");
	}

   	if (ferror(sourcefile)) {
		perror("File Read");
	}

    fclose(sourcefile);
    fflush(destfile);
    fclose(destfile);
}

void copy_dir(int sdirfd, char *source, char *dest) {
    int swd_fd, sourcefd;
    struct dirent *entry;
    DIR *source_dir;

    LOG("-copy dir %s -> %s\n", source, dest);

    swd_fd = open(".", O_RDONLY);
    if (swd_fd == -1) {
        perror("open");
        return;
    }

    // 생성하고 그 디렉토리로 이동
    if (mkdir (dest, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == -1) {
        perror("mkdir");
        return;
    }
    if (chdir(dest) == -1) {
        perror("chdir");
        return;
    }

    LOG("-dest dir: %s\n", get_current_dir_name());

    // copy dir
    sourcefd = openat(sdirfd, source, 0);
    source_dir = fdopendir(sourcefd);
    while((entry = readdir(source_dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        copy(sourcefd, entry->d_name, entry->d_name);
    }

    closedir(source_dir);
    if (fchdir(swd_fd) == -1) {
        perror("fchdir");
        return;
    }
    close(swd_fd);
}

void copy(int sdirfd, char *source, char *dest)
{
    struct stat sb;
    LOG("copy %s -> %s\n", source, dest);
    if (fstatat(sdirfd, source, &sb, 0)) {
        perror("stat");
        return;
    }

    switch(sb.st_mode & S_IFMT) {
        case S_IFDIR:
            if (!is_recursive) {
                printf("-r not specified; omitting directory %s\n", source);
                exit(1);
            }
            copy_dir(sdirfd, source, dest);
            break;
        default:
            copy_file(sdirfd, source, dest);
            break;
    }
}

int main(int argc, char *argv[])
{
    extern int optind;

    int opt, pathind = 0;

    int sdirfd;

    while ((opt = getopt(argc, argv, "r")) != -1)
    {
        switch (opt)
        {
        case 'r':
            LOG("is recursive\n");
            is_recursive = 1;
            break;
        default:
            break;
        }
    }

    if (argv[optind] == NULL || argv[optind + 1] == NULL)
    {
        printf("usage : %s source dest\n", argv[0]);
        exit(1);
    }

    if ((sdirfd = open(".", O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    copy(sdirfd, argv[optind], argv[optind + 1]);

    close(sdirfd);

    return 0;
}
