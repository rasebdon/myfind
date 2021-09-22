#ifndef _MSGQUEUE_H_
#define _MSGQUEUE_H_

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "../helper/forkHelper.h"

#define KEY 13377331
#define PERM 0660

#define MAX_DATA 512

typedef struct
{
	long mType;
	char absolutePath[MAX_DATA];
	char filename[MAX_DATA];
    long childPId;
    bool quitting;
    bool starting;
} message_t;

class msgQueue
{
public:
    static int sendMessage(message_t msg);
    static void removeQueue();
    static int createQueue();
};

#endif