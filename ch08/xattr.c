#include <sys/types.h>
#include <sys/xattr.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage()
{
    printf("usage: xattr option option_name path value\n");
    printf("get: xattr get (option_name) (path)\n");
    printf("set: xattr set (option_name) (path) (value)\n");
    printf("list: xattr list (path)\n");
}

void get_xattr(char *option_name, char *path)
{
    char value[256];
    ssize_t size;

    size = getxattr(path, option_name, &value, 256);

    printf("option %s[%ld] : %s\n", option_name, size, value);
}

void list_xattr(char *path)
{
    char *buf, *key, value[256];
    ssize_t size, vallen;
    int keylen;

    size = listxattr(path, NULL, 0);
    if (size == -1)
    {
        perror("listxattr");
        exit(1);
    }
    if (size == 0)
    {
        printf("no xattr\n");
        exit(1);
    }

    buf = malloc(size);

    size = listxattr(path, buf, size);

    key = buf;
    while (size > 0)
    {
        vallen = getxattr(path, key, &value, size);
        if (vallen == -1)
        {
            perror("getxattr");
        }

        printf("option %s[%ld] : %s\n", key, vallen, value);

        keylen = strlen(key) + 1;
        size -= keylen;
        key += keylen;
    }
    free(buf);
}

void set_xattr(char *option_name, char *path, char *value)
{
    if (setxattr(path, option_name, value, strlen(value), 0) == -1)
    {
        perror("setxattr");
        exit(1);
    }
}

void main(int argc, char *argv[])
{
    char *option;

    if (argc < 3)
    {
        print_usage();
        exit(1);
    }

    option = argv[1];

    if (strcmp(option, "get") == 0)
    {
        get_xattr(argv[2], argv[3]);
    }
    else if (strcmp(option, "set") == 0)
    {
        set_xattr(argv[2], argv[3], argv[4]);
    }
    else if (strcmp(option, "list") == 0)
    {
        list_xattr(argv[2]);
    }
    else
    {
        print_usage();
    }
}