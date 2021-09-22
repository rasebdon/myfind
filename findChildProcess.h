#ifndef _FINDCHILDPROCESS_H_
#define _FINDCHILDPROCESS_H_

#include "findAttributes.h"
#include "messageQueue/msgQueue.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include <algorithm>

namespace myFind
{
    class findChildProcess
    {
    private:
        std::string myDir;
    public:
        findChildProcess(std::string dirToSerach, myFind::findAttributes attributes);
        ~findChildProcess();
    };
}

#endif