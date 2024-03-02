#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void create(const char *path, const char sep)
{
    char *subpath = strdup(path);
    char *p = subpath;

    while (*p != '\0')
    {
        if (*p == '/')
        {
            // replace it with a null terminator
            *p = 0;

            // try to create the directory and handle errors
            if (mkdir(subpath, 0755) == -1 && errno != EEXIST)
            {
                perror("mkdir");
                exit(EXIT_FAILURE);
            }
            // restore the slash
            *p = '/';
        }
        // move to the next character
        p++;
    }

    FILE *ptr = fopen(subpath, "a");
    if (ptr == NULL)
    {
        if (errno == ENOTDIR)
        {
            printf("error: trying to create a file inside a file\n");
        }
        else
        {
            perror("");
        }
        exit(EXIT_FAILURE);
    }
    fclose(ptr);
    free(subpath);
}

int check_is_file(const char *path)
{
    char *p = path;
    char last = *p;
    while (*p != 0)
    {
        last = *p;
        p++;
    }
    return last != 0 && last != '/';
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("this take exactly one argument\n");
        return 1;
    }

    if (!check_is_file(argv[1]))
    {
        printf("argument is not a file\n");
        return 1;
    }

    create(argv[1], '/');

    return 0;
}
