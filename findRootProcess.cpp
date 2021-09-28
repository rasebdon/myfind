#include "findRootProcess.h"

namespace myFind {

    findRootProcess::findRootProcess(myFind::findAttributes attributes) : _msgQueue(KEY, PERM)
    {
        this->_attributes = attributes;
        this->currentDirectory = fileSystemHelper::getWorkingDirectory();
        this->msgQueueId = _msgQueue.createQueue();
    }

    // Starts the processes that should find the files
    void findRootProcess::startChildrenProcesses() {
        for (auto file : _attributes.getFilesToFind())
        {
            hasChildProcesses = true;
            forkHelper::tryFork(
                [&](){
                    findChildProcess _findChildProcess = findChildProcess(_attributes.getRootSearchPath(), _attributes, _msgQueue);
                    _findChildProcess.findFile();
                    exit(0);
                },
                nullptr
            );
            _attributes.fileToSearchIndex++;
        }
    }

    void findRootProcess::receiveMessages(){
        // Recieves findings for as long as the child processes are searching
        while (hasChildProcesses)
        {
            // Recieve base message
            _msgQueue.receiveMessage(msgBuffer);
            
            // Cast message via the message type
            switch (msgBuffer.messageType)
            {
            // Process status has been changed
            case queueMessageType::LiveStatus:
                processLiveStatusMessage(msgBuffer);
                break;
            // File has been found by a child process
            case queueMessageType::FoundFileData:
                processFoundFileDataMessage(msgBuffer);
                break;
            default:
                break;
            }
        }
    }

    // Message handling for starting/stopping processes
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

    // Prints out the found file
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

