#include "findRootProcess.h"

namespace myFind {

    findRootProcess::findRootProcess(myFind::findAttributes attributes)
    {
        this->_attributes = attributes;
        this->currentDirectory = fileSystemHelper::getWorkingDirectory();
        this->msgQueueId = msgQueue::createQueue();
    }

    void findRootProcess::startChildrenProcesses() {
        for (auto file:_attributes.getFilesToFind())
        {
            this->activeClients++;
            forkHelper::tryFork(
                [&](){myFind::findChildProcess(currentDirectory, _attributes);exit(0);},
                nullptr
            );
            _attributes.fileToSearchIndex++;
        }
    }

    void findRootProcess::receiveMessages(){
        while (this->activeClients > 0)
        {
            std::cout << activeClients<<std::endl;
            if (msgrcv(msgQueueId, &msgBuffer, sizeof(msgBuffer) - sizeof(long), 0, 0) == -1)
            {
                std::cout << "Can't receive from message queue" << std::endl;
                break;
            }
            // Child process started
            if(msgBuffer.quitting) {
                this->activeClients--;
                //std::cout << "Child killed, processes left: " << this->activeClients << std::endl;
            }
            // Child process stopped
            else if(msgBuffer.starting) {
                this->activeClients++;
                //std::cout << "Child added, processes left: " << this->activeClients << std::endl;
            }
            // A file has been found!
            else if(((std::string)(msgBuffer.absolutePath)).size() > 0 || ((std::string)(msgBuffer.filename)).size() > 0) {
                // <pid>: <filename>: <complete-path-to-found-file>\n
                std::cout << msgBuffer.childPId << ": " << msgBuffer.filename << ": " << msgBuffer.absolutePath << std::endl;
            }
        }
    }

    findRootProcess::~findRootProcess()
    {
    }
}

