#include <consumer.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

bool consumer_init (consumer_t *consumer)
{
    bool status = false;

    if (consumer != NULL)
    {
        memset (consumer, 0, sizeof (consumer_t));
        status = true;
    }

    return status;
}

bool consumer_open (consumer_t *consumer, consumer_args_t *args)
{
    bool status = false;

    if (consumer != NULL)
    {
        consumer->base = args->base;
        
        status = true;
    }

    return status;
}

bool consumer_run (consumer_t *consumer)
{
    bool status = false;
    

    if (consumer != NULL)
    {
        if (consumer->base->init (consumer->base->object) == false)
        {
            return EXIT_FAILURE;
        }

        while (true)
        {
            // consumer->base->set (consumer->base->object, state);
        }

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