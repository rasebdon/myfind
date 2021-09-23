#include "findRootProcess.h"

namespace myFind {

    findRootProcess::findRootProcess(myFind::findAttributes attributes) : _msgQueue(KEY, PERM)
    {
        this->_attributes = attributes;
        this->currentDirectory = fileSystemHelper::getWorkingDirectory();
        this->msgQueueId = _msgQueue.createQueue();
    }

    void findRootProcess::startChildrenProcesses() {
        for (auto file : _attributes.getFilesToFind())
        {
            hasChildProcesses = true;
            forkHelper::tryFork(
                [&](){
                    findChildProcess _findChildProcess = findChildProcess(currentDirectory, _attributes, _msgQueue);
                    _findChildProcess.findFile();
                    exit(0);
                },
                nullptr
            );
            _attributes.fileToSearchIndex++;
        }
    }

    void findRootProcess::receiveMessages(){
        while (hasChildProcesses)
        {
            _msgQueue.receiveMessage(msgBuffer);
            
            // Child process started
            if(msgBuffer.quitting) {
                this->activeClients--;
                if(this->activeClients == 0)
                    hasChildProcesses = false;
                // std::cout << "Child killed, processes left: " << this->activeClients << std::endl;
            }
            // Child process stopped
            else if(msgBuffer.starting) {
                this->activeClients++;
                // std::cout << "Child added, processes left: " << this->activeClients << std::endl;
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

