#include <consumer.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

bool consumer_init (consumer_t *led)
{
    bool status = false;

    if (led != NULL)
    {
        memset (led, 0, sizeof (consumer_t));
        status = true;
    }

    return status;
}

bool consumer_open (consumer_t *led, consumer_args_t *args)
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

bool consumer_run (consumer_t *consumer)
{
    bool status = false;
    char buffer [BUFSIZ + 1];
    int current_state;
    int old_state;

    if (consumer != NULL)
    {
        if (consumer->base->init (consumer->base->object) == false)
        {
            return EXIT_FAILURE;
        }

        while (true)
        {
            memset (buffer, 0, sizeof (buffer));
            read (consumer->descriptor, buffer, BUFSIZ);
            sscanf (buffer, "state = %d", &current_state);

            if (current_state != old_state)
            {
                old_state = current_state;
                consumer->base->set (consumer->base->object, current_state);
            }

            usleep (1);
        }

        close (consumer->descriptor);
        status = true;
    }

    return status;
}

bool consumer_close (consumer_t *consumer)
{
    bool status = false;

    if (consumer != NULL)
    {
        memset (consumer, 0, sizeof (consumer_t));
        status = true;
    }

    return status;
}