#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    const int childAmount = 5;
    pid_t childs[childAmount];
    const long parentPId = (long)getpid();

    for (int i = 0; i < childAmount; i++)
    {
        childs[i] = fork();

        if (childs[i] == -1)
        {
            perror("Failed to fork");
            return 1;
        }

        if (childs[i] == 0)
        {
            printf("I am child %ld \n", (long)getpid());
            break;
        }
    }

    sleep(4);

    if((long)getpid() == parentPId)
        printf("Parent done!\n");
    return 0;
}