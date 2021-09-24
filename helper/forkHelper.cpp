#include "forkHelper.h"

// Tries to fork a new process with the given callbacks on the processes
void forkHelper::tryFork(std::function<void()>childCallback, std::function<void()>parentCallback) {
    lastPid = fork();
    switch (lastPid)
    {
    case 0:
        if(childCallback == nullptr)
            return;
        childCallback();
        break;
    case -1:
        throw std::runtime_error("failed to fork");
    default:
        if(parentCallback == nullptr)
            return;
        parentCallback();
        break;
    }
}

pid_t forkHelper::lastPid = 0;

pid_t forkHelper::getLastPid() {
    return lastPid;
}