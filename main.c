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
    //! TODO.. maybe this need error handling.. i dont know
    fclose(fopen(subpath, "a"));
    free(subpath); // free the memory
}

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("this take exactly one argument\n");
        return 1;
    }
    create(argv[1], '/');

    return 0;
}
