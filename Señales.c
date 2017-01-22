#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
 
void sigcont_handler(int);
 
int main(int argc, char **argv)
{
    pid_t pid[6];
    int status;
     
    for(int i = 0; i < 6; i++)
    {    
        pid[i] = fork();
         
        if(pid[i] >= 0)
            if(pid[i] > 0)
                switch(i)
                {
                    case 0:
                        break;
                    case 1:
                        kill(pid[i], SIGINT);
                        break;
                    case 2:
                        kill(pid[i], SIGTERM);
                        break;
                    case 3:
                        kill(pid[i], SIGQUIT);
                        break;
                    case 4:
                        kill(pid[i], SIGKILL);
                        break;
                    case 5:
                        sleep(2);
                        kill(pid[i], SIGSTOP);
                        break;
                         
                }
            else
            {
                if(i == 0)
                    exit(EXIT_SUCCESS);
                else if(i == 5)
                {
                    signal(SIGCONT, sigcont_handler);
                    sleep(4);
                }
                else
                    sleep(5);
            }
        else
        {
            //perror(program_invocation_name);
            exit(EXIT_FAILURE);
        }
    }
     
    for(int i = 0; i < 6; i++)
        printf("%d\n", pid[i]);
     
    for(int i = 0; i < 6; i++)
    {
        waitpid(pid[i], &status, WUNTRACED);
         
        if(WIFEXITED(status))
            printf("%s: %d: %s\n", pid[i], "Process terminated normally.");
        else if(WIFSIGNALED(status))
        {
            printf("%s: %d: %s\n", pid[i], strsignal(WTERMSIG(status)));
             
            if(WCOREDUMP(status))
                printf("%s: %d: %s\n", pid[i], "Process produced a core dump.");
        }
        else if(WIFSTOPPED(status))
        {
            printf("%s: %d: %s\n", pid[i], "Process is stopped.");
            printf("%s: %d: %s\n", pid[i], strsignal(WSTOPSIG(status)));
             
            kill(pid[i], SIGCONT);
        }
    }
     
    return EXIT_SUCCESS;
}
 
void sigcont_handler(int signum)
{
    printf("%s: %d: %s\n", getpid(), "Process terminated normally.");
    exit(EXIT_SUCCESS);
}
