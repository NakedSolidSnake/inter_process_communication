#include <syslog.h>
#include <unistd.h>

void logger (int value)
{
    openlog ("Daemon", LOG_PID | LOG_CONS, LOG_USER);
    syslog (LOG_INFO, "Counter: %d", value);
    closelog ();
}

int main (void)
{
    int i = 0;

    daemon (0, 0);

    while (1)
    {
        logger (i++);
        sleep (1);
    }

    return 0;
}