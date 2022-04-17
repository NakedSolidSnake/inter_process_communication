#include <producer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRODUCER_1ms 1000

static bool producer_wait (producer_t *producer);

bool producer_init (producer_t *producer)
{
    bool status = false;

    if (producer != NULL)
    {
        memset (producer, 0, sizeof (producer_t));
        status = true;
    }

    return status;
}

bool producer_open (producer_t *producer, producer_args_t *args)
{
    bool status = false;

    if (producer != NULL && args != NULL)
    {
        producer->base = args->base;
        producer->descriptor = atoi (args->argv[1]);
        status = true;
    }

    return status;
}

bool producer_run (producer_t *producer)
{
    bool status = false;
    char buffer [BUFSIZ + 1];
    int state = 0;

    if (producer != NULL)
    {
        if (producer->base->init (producer->base->object) == false)
            return EXIT_FAILURE;

        while (true)
        {
            producer_wait (producer);

            state ^= 0x01;
            memset (buffer, 0, sizeof (BUFSIZ));
            snprintf (buffer, BUFSIZ, "state = %d", state);
            write (producer->descriptor, buffer, strlen (buffer));
            usleep (500 * PRODUCER_1ms);
        }

        close (producer->descriptor);
        status = true;
    }

    return status;
}

bool producer_close (producer_t *producer)
{
    bool status = false;

    if (producer != NULL)
    {
        memset (producer, 0, sizeof (producer_t));
        status = true;
    }

    return status;
}

static bool producer_wait (producer_t *producer)
{
    while (true)
    {
        if (producer->base->read (producer->base->object) == true)
        {
            usleep (PRODUCER_1ms * 100);
            break;
        }

        usleep (PRODUCER_1ms);
    }

    return true;
}