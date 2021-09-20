#include "findBehaviour/findAttributes.h"

int main(int argc, char* argv[]) {
    // Get attributes
    myFind::findAttributes attributes = myFind::findAttributes(argc, argv);

    attributes.printAttributes();

    // const int childAmount = 5;
    // pid_t childs[5];
    // const long parentPId = (long)getpid();

    // for (int i = 0; i < 5; i++)
    // {
    //     childs[i] = fork();

    //     if (childs[i] == -1)
    //     {
    //         perror("Failed to fork");
    //         return 1;
    //     }

    //     if (childs[i] == 0)
    //     {
    //         printf("I am child %ld \n", (long)getpid());
    //         break;
    //     }
    // }

    // sleep(4);

    // if ((long)getpid() == parentPId)
    //     printf("Parent done!\n");
    return 0;
}
