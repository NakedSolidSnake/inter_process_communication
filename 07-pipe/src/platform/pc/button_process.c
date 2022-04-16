#include <button_process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

static const char *fifo = "/tmp/pipe";
static int fd;

static bool button_process_init_hardware (void *object)
{
    (void)object;
    remove (fifo);
    int ret = mkfifo (fifo, 0666);
    return ret == -1 ? false : true;
}   

static bool button_process_read (void *object)
{
    (void)object;
    int state;
    char buffer [2];
    fd = open (fifo, O_RDONLY);
    read (fd, buffer, 2);
    state = atoi (buffer);
    return state ? true : false;
}

bool button_process_init (button_process_t *button)
{
    bool status = false;
    if (button != NULL)
    {
        memset (button, 0, sizeof (button_process_t));
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
