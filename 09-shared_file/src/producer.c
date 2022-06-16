#include <producer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <definition.h>
#include <shared_file.h>

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
        
        status = true;
    }

    return status;
}

bool producer_run (producer_t *producer)
{
    bool status = false;
    char buffer [2] = {0};
    int state = 0;

    shared_file_t sf = 
    {
        .filename = FILENAME,
        .timeout  = 1000
    };
    

    if (producer != NULL)
    {
        if (producer->base->init (producer->base->object) == false)
            return false;

        if (shared_file_init (&sf) == false)
            return false;

        while (true)
        {
            producer_wait (producer);

            state ^= 0x01;
            snprintf (buffer, sizeof (buffer), "%d", state);
            if (shared_file_write (&sf, buffer, sizeof (buffer)) == false)
                break;
        }

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