#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main (int argc, char *argv[])
{
    /*
        0 - read
        1 - write
    */
    int pipes[2];

    struct 
    {
        int read;
        int write;
    } channel;

    struct 
    {
        pid_t led;
        pid_t button;
    } process;

    char args[BUFSIZ + 1];
    int state;

    // daemon (1, 1);

    if (pipe (pipes)  < 0)
        return EXIT_FAILURE;

    channel.read = pipes[0];
    channel.write = pipes[1];

    process.button = fork ();
    if (process.button == 0)
    {
        close (channel.read);
        memset (args, 0, sizeof (args));
        snprintf (args, BUFSIZ, "%d", channel.write);
        execl ("button_process", "button_process", args, NULL);
    }

    else if (process.button > 0)
    {
        process.led = fork ();
        if (process.led == 0)
        {
            close (channel.write);
            memset (args, 0, sizeof (args));
            snprintf (args, BUFSIZ, "%d", channel.read);
            execl ("led_process", "led_process", args, NULL);
        }
    }

    close (channel.read);
    close (channel.write);

    wait (&state);

    kill (process.button, SIGKILL);
    kill (process.led, SIGKILL);

    return EXIT_SUCCESS;
}