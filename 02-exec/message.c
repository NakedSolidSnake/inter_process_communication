#include <stdio.h>

int main (int argc, char *argv[])
{
    char *message = "Default Text";

    if (argc > 1)
    {
        message = argv[1];
    }

    printf ("%s\n", message);
    return 0;
}