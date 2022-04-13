#include <led_process.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

bool led_process_init (led_process_t *led)
{
    bool status = false;

    if (led != NULL)
    {
        memset (led, 0, sizeof (led_process_t));
        status = true;
    }

    return status;
}

bool led_process_open (led_process_t *led, led_process_args_t *args)
{
    bool status = false;

    if (led != NULL)
    {
        led->base = args->base;
        led->descriptor = atoi (args->argv[1]);
        status = true;
    }

    return status;
}

bool led_process_run (led_process_t *led)
{
    bool status = false;
    char buffer [BUFSIZ + 1];
    int current_state;
    int old_state;

    if (led != NULL)
    {
        if (led->base->init (led->base->object) == false)
        {
            return EXIT_FAILURE;
        }

        while (true)
        {
            memset (buffer, 0, sizeof (buffer));
            read (led->descriptor, buffer, BUFSIZ);
            sscanf (buffer, "state = %d", &current_state);

            if (current_state != old_state)
            {
                old_state = current_state;
                led->base->set (led->base->object, current_state);
            }

            usleep (1);
        }

        close (led->descriptor);
        status = true;
    }

    return status;
}

bool led_process_close (led_process_t *led)
{
    bool status = false;

    if (led != NULL)
    {
        memset (led, 0, sizeof (led_process_t));
        status = true;
    }

    return status;
}