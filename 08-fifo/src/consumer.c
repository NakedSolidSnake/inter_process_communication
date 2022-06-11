#include <consumer.h>
#include <definitions.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fifo.h>

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
        
        status = true;
    }

    return status;
}

bool consumer_run (consumer_t *consumer)
{
    bool status = false;
    int state = false;
    char buffer[2] = {0};
    uint32_t size = sizeof(buffer);
    fifo_t fifo = 
    {
        .name = FIFO_FILE,
    };

    if (consumer != NULL)
    {
        if (consumer->base->init (consumer->base->object) == false)
        {
            return EXIT_FAILURE;
        }

        if (fifo_init (&fifo) == false)
            return EXIT_FAILURE;

        while (true)
        {
            fifo_read (&fifo, buffer, &size);
            state = atoi(buffer);
            consumer->base->set (consumer->base->object, state);
        }

        fifo_destroy(&fifo);
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