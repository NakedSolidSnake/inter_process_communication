#include <button_process.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "button_pc.h"

static bool button_process_init_hardware (void *object)
{
    button_process_t *button = (button_process_t *)object;
    button_pc_t *pc = (button_pc_t *)button->data;
    
    remove (pc->fifo);
    int ret = mkfifo (pc->fifo, 0666);
    return ret == -1 ? false : true;
}   

static bool button_process_read (void *object)
{
    button_process_t *button = (button_process_t *)object;
    button_pc_t *pc = (button_pc_t *)button->data;

    int state;
    char buffer [2];
    pc->fd = open (pc->fifo, O_RDONLY);
    read (pc->fd, buffer, 2);
    state = atoi (buffer);
    close (pc->fd);
    return state ? true : false;
}

bool button_process_init (button_process_t *button)
{
    bool status = false;
    if (button != NULL)
    {
        memset (button, 0, sizeof (button_process_t));
        button->base.object = button;
        button->base.init = button_process_init_hardware;
        button->base.read = button_process_read;
        status = true;
    }

    return status;
}

bool button_process_open (button_process_t *button, void *args)
{
    bool status = false;
    if (button != NULL)
    {
        button->data = args;
        status = true;        
    }

    return status;
}

bool button_process_close (button_process_t *button)
{
    bool status = false;
    if (button != NULL)
    {
        memset (button, 0, sizeof (button_process_t));
        status = true;
    }

    return status;
}
