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

enum queueMessageType { LiveStatus, FoundFileData };

struct queueMessage
{
    long mType;
    queueMessageType messageType;
    long childPId;
    bool starting;
    bool quitting;
    char absolutePath[MAX_DATA];
    char filename[MAX_DATA];
};

class msgQueue
{
private:
    int _key;
    int _premissions;
    int _queueId;
public:
    msgQueue(int key, int permissions); 
    int sendMessage(queueMessage &msg);
    void removeQueue();
    int createQueue();
    void receiveMessage(queueMessage &msg);
    ~msgQueue();
};
// TODO: FIX STATIC USAGE
#endif