#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main (int argc, char *argv[])
{
    struct 
    {
        pid_t led;
        pid_t button;
    } process;

    int state;

    daemon (1, 1);

    process.button = fork ();
    if (process.button == 0)
    {
        execl ("button_process", "button_process", NULL);
    }

    else if (process.button > 0)
    {
        process.led = fork ();
        if (process.led == 0)
        {
            execl ("led_process", "led_process", NULL);
        }
    }

    wait (&state);

    kill (process.button, SIGKILL);
    kill (process.led, SIGKILL);

    return EXIT_SUCCESS;
}