#include <button_process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUTTON_1ms 1000

static bool button_process_wait (button_process_t *button);

bool button_process_init (button_process_t *button)
{
    bool status = false;

    if (button != NULL)
    {
        memset (button, 0, sizeof (button_process_t));
        status = true;
    }

    return status;
}

bool button_process_open (button_process_t *button, button_process_args_t *args)
{
    bool status = false;

    if (button != NULL && args != NULL)
    {
        button->base = args->base;
        button->descriptor = atoi (args->argv[1]);
        status = true;
    }

    return status;
}

bool button_process_run (button_process_t *button)
{
    bool status = false;
    char buffer [BUFSIZ + 1];
    int state = 0;

    if (button != NULL)
    {
        if (button->base->init (button->base->object) == false)
            return EXIT_FAILURE;

        while (true)
        {
            button_process_wait (button);

            state ^= 0x01;
            memset (buffer, 0, sizeof (BUFSIZ));
            snprintf (buffer, BUFSIZ, "state = %d", state);
            write (button->descriptor, buffer, strlen (buffer));
            usleep (500 * BUTTON_1ms);
        }

        close (button->descriptor);
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

static bool button_process_wait (button_process_t *button)
{
    while (true)
    {
        if (button->base->read (button->base->object) == true)
        {
            usleep (BUTTON_1ms * 100);
            break;
        }

        usleep (BUTTON_1ms);
    }
}