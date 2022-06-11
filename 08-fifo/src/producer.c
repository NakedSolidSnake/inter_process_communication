#include <producer.h>
#include <definitions.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fifo.h>

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
    int state = false;
    char buffer[2] = {0};
    fifo_t fifo = 
    {
        .name = FIFO_FILE,
    };
    

    if (producer != NULL)
    {
        if (producer->base->init (producer->base->object) == false)
            return EXIT_FAILURE;

        if (fifo_init (&fifo) == false)
            return EXIT_FAILURE;

        while (true)
        {
            producer_wait (producer);
            state ^= 0x01;
            snprintf(buffer, 2, "%d", state);
            fifo_write (&fifo, buffer, 2);
            
        }

        fifo_destroy (&fifo);
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