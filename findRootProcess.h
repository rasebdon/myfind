#ifndef _FINDROOTPROCESS_H_
#define _FINDROOTPROCESS_H_
#include "findAttributes.h"
#include <sys/msg.h>
#include "findChildProcess.h"
#include "messageQueue/msgQueue.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iomanip>
#include "helper/forkHelper.h"
#include "helper/fileSystemHelper.h"

namespace myFind {

    class findRootProcess
    {
    private:
        bool hasChildProcesses = false;
        findAttributes _attributes;
        queueMessage msgBuffer;
        msgQueue _msgQueue;
        int msgQueueId;
        std::string currentDirectory;
    public:
        int activeClients = 0;
        
        findRootProcess();
        findRootProcess(myFind::findAttributes attributes);
        ~findRootProcess();

        void processLiveStatusMessage(queueMessage &liveStatusMessage);
        void processFoundFileDataMessage(queueMessage &foundFileDataMessage);
        void receiveMessages();
        void startChildrenProcesses();
    };
}
#endif