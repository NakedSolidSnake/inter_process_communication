#include "fifo.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool fifo_init (fifo_t *fifo)
{
    bool status = false;

    if (fifo != NULL)
    {
        mkfifo(fifo->name, 0666);
        status = true;
    }

    return status;
}

bool fifo_write (fifo_t *fifo, const char *data, uint32_t size)
{
    bool status = false;

    if (fifo != NULL && data != NULL && size > 0)
    {
        fifo->descriptor = open (fifo->name, O_WRONLY);
        if (fifo->descriptor > 0)
        {
            write (fifo->descriptor, data, size);
            status = true;
            close (fifo->descriptor);
        }
    }

    return status;
}

bool fifo_read (fifo_t *fifo, char *data, uint32_t *size)
{
    bool status = false;

    if (fifo != NULL && data != NULL && size > 0)
    {
        fifo->descriptor = open (fifo->name, O_RDONLY);
        if (fifo->descriptor > 0)
        {
            read (fifo->descriptor, data, *size);
            status = true;
            close (fifo->descriptor);
        }
    }

    return status;
}

bool fifo_destroy (fifo_t *fifo)
{
    bool status = false;

    if (fifo != NULL)
    {

        status = true;
    }

    return status;
}