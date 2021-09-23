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
        myFind::findAttributes _attributes;
        std::string _rootDirectoryToSearch;
        void findFile(std::string directoryToSearch);
        msgQueue &_msgQueue;
    public:
        findChildProcess(std::string directoryToSerach, myFind::findAttributes attributes, msgQueue &msgQueue);
        void findFile();
        void tryHandleFoundEntry(std::string directoryEntry, std::string directoryOfEntry);
        void sendFoundFileData(std::string &foundFile, std::string &directoryOfFile);
        ~findChildProcess();
    };
}

#endif