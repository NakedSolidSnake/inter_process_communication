#include <consumer.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <definition.h>
#include <shared_file.h>

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
    char buffer [2] = {0};
    int state_old = 0;
    int state_current;
    uint32_t size;
    shared_file_t sf = 
    {
        .filename = FILENAME,
        .timeout = 1000
    };
    

    if (consumer != NULL)
    {
        if (consumer->base->init (consumer->base->object) == false)
            return false;

        if (shared_file_init (&sf) == false)
            return false;

        while (true)
        {
            size = sizeof (buffer);
            shared_file_read (&sf, buffer, &size);
            state_current = atoi (buffer);

            if (state_current != state_old)
            {
                state_old = state_current;
                consumer->base->set (consumer->base->object, state_current);
            }

            usleep (1000);
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