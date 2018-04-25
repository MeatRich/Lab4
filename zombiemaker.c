#include <sys/types.h>

int main(int argc, char **argv) 
{
       pid_t child_pid = fork();
       if (child_pid > 0)
       {
           sleep(60);
       }
}