#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    char *message = "Default Text";

    if (argc > 1)
    {
        message = argv[1];
    }

    printf ("%s\n", message);

    while (1)
    {
        sleep (1);
    }
    
    
    return 0;
}