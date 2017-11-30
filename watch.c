#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>

#define DEFAULT_INTERVAL 2000;
#define ARGS_MAX 128;

void help()
{
    printf(
        "\n"
        "  Usage: watch [options] <cmd>\n"
        "\n"
        "  Options:\n"
        "\n"
        "    -q, --quiet           only output stderr\n"
        "    -x, --halt            halt on failure\n"
        "    -i, --interval <n>    interval in seconds or ms defaulting to 1\n"
        "    -v, --version         output version number\n"
        "    -h, --help            output this help information\n"
        "\n");
    exit(1);
}

int option(char *small, char *large, const char *arg)
{
    if (!strcmp(small, arg) || !strcmp(large, arg))
    {
        return 1;
    }
    return 0;
}

int main(int argc, const char **argv)
{
    if (argc == 1)
    {
        help();
    }

    int interval = DEFAULT_INTERVAL;
    int len = 0;
    int interpret = 1;

    char *args[128] = {0};

    for (int i = 1; i < argc; ++i)
    {
        const char *arg = argv[i];
        if (!interpret)
            goto arg;

        // -h, --help
        if (option("-h", "--help", arg))
            help();

        // -i, --interval <n>
        if (option("-i", "--interval", arg))
        {
            if (argc - 1 == i)
            {
                fprintf(stderr, "\n  --interval requires an argument\n\n");
                exit(1);
            }

            arg = argv[++i];
        }

        // cmd args
        if (len == 128)
        {
            fprintf(stderr, "number of arguments exceeded %d\n", len);
            exit(1);
        }
-
    arg:
        args[len++] = (char *)arg;
        interpret = 0;
    }

    return 0;
}