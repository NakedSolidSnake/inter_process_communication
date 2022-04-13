#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
    pid_t pid = fork();
    if (pid > 0)
    {
        printf ("I'm parent process. pid = %d\n", pid);        
    }
    else 
    {
        printf ("I'm child process pid = %d\n", pid);        
    }
    sleep (1);
    return 0;
}
