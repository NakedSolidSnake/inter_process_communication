#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
    int state;
    pid_t pid = fork();
    if (pid > 0)
    {
        printf ("I'm parent process. pid = %d\n", pid);
        wait (&state);        
    }
    else 
    {
        // printf ("I'm child process pid = %d\n", pid);
        char *list[] = {"./message.out", "Hello World", NULL};
        execvp (list[0], list);
    }
    return 0;
}
