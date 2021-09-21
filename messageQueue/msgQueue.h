#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

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
};