#include <led_process.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>

static bool led_process_init_hardware (void *object)
{
    (void)object;
    return true;
}   

static bool led_process_set (void *object, bool state)
{
    openlog ("LED PIPE", LOG_PID | LOG_CONS, LOG_USER);
    syslog (LOG_INFO, "LED Status: %s", state ? "ON" : "OFF");
    closelog ();
    return true;
}

bool led_process_init (led_process_t *led)
{
    bool status = false;
    if (led != NULL)
    {
        memset (led, 0, sizeof (led_process_t));
        led->base.object = led;
        led->base.init = led_process_init_hardware;
        led->base.set = led_process_set;
        status = true;
    }

    return status;
}

bool led_process_open (led_process_t *led, void *args)
{
    bool status = false;
    if (led != NULL)
    {
        led->data = args;
        status = true;        
    }

    return status;
}

bool led_process_close (led_process_t *led)
{
    bool status = false;
    if (led != NULL)
    {
        memset (led, 0, sizeof (led_process_t));
        status = true;
    }

    return status;
}
