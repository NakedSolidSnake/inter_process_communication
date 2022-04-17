#include <button_process.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <button.h>

static bool button_process_init_hardware (void *object)
{
    button_process_t *process = (button_process_t *)object;
    button_t *button = (button_t *)process->data;
    return button_init (button);
}   

static bool button_process_read (void *object)
{
    button_process_t *process = (button_process_t *)object;
    button_t *button = (button_t *)process->data;

    return button_read (button) == false ? true : false;
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
