#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

typedef struct 
{
    const char *name;
    const char *args;
    pid_t pid;
} process_control_t;

static process_control_t processes[] = 
{
    {.name = "./message.out", .args = "Hello World", .pid = -1},
    {.name = "./message.out", .args = "Hallo Welt", .pid = -1}
};

static int processes_amount = sizeof (processes) / sizeof (processes[0]);

pid_t process_control_launch (int index)
{
    pid_t pid = fork ();
    if (pid == 0)
    {
        char *list[] = {processes[index].name, processes[index].args, NULL};
        execvp (list[0], list);
    }

    return pid;
}

void process_control_scan (pid_t pid)
{
    for (int i = 0; i < processes_amount; i++)
    {
        if (pid == processes[i].pid)
        {
            printf ("Relaunching: %s args: %s\n", processes[i].name, processes[i].args);
            processes[i].pid = process_control_launch (i);
            break;
        }
    }
}

int main (void)
{
    int state;
    pid_t pid;

    for (int i = 0; i < processes_amount; i++ )
    {
        processes[i].pid = process_control_launch (i);
    }

    while (1)
    {
        pid = wait (&state);
        process_control_scan (pid);
    }
    
    return 0;
}
