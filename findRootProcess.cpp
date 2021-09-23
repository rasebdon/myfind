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
            
            switch (msgBuffer.messageType)
            {
            case queueMessageType::LiveStatus:
                processLiveStatusMessage(msgBuffer);
                break;
            case queueMessageType::FoundFileData:
                processFoundFileDataMessage(msgBuffer);
                break;
            default:
                break;
            }
        }
    }

    void findRootProcess::processLiveStatusMessage(queueMessage &liveStatusMessage) {
        if(liveStatusMessage.quitting) {
            this->activeClients--;
            if(this->activeClients == 0)
                hasChildProcesses = false;
            // std::cout << "Child killed, processes left: " << this->activeClients << std::endl;
        }
        else if(liveStatusMessage.starting) {
            this->activeClients++;
            // std::cout << "Child added, processes left: " << this->activeClients << std::endl;
        }
    }

    void findRootProcess::processFoundFileDataMessage(queueMessage &foundFileDataMessage) {
        // <pid>: <filename>: <complete-path-to-found-file>\n
        std::cout << foundFileDataMessage.childPId << ": " 
            << foundFileDataMessage.filename << ": " 
            << foundFileDataMessage.absolutePath << std::endl;
    }

    findRootProcess::~findRootProcess()
    {
    }
}

