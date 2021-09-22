#ifndef _FORKHELPER_H_
#define _FORKHELPER_H_

#include <iostream>
#include <functional>
#include <unistd.h>

class forkHelper
{
private:
    static pid_t lastPid;
public:
    static void tryFork(std::function<void()>childCallback, std::function<void()>parentCallback);
    static pid_t getLastPid();
};



#endif