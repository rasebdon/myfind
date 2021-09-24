#include "findChildProcess.h"
#include "helper/fileSystemHelper.h"

namespace myFind {

    findChildProcess::findChildProcess(
        std::string directoryToSerach, 
        myFind::findAttributes attributes, 
        msgQueue &msgQueue) : _msgQueue(msgQueue)
    {
        _attributes = attributes;
        _rootDirectoryToSearch = directoryToSerach;
    }

    void findChildProcess::findFile() {
        // Send the parent that the process has started searching
        queueMessage aliveMessage{1, queueMessageType::LiveStatus, (long)getpid(), true, false};
        _msgQueue.sendMessage(aliveMessage);

        // Search the file in the current directory
        findFile(_rootDirectoryToSearch);

        // Send the parent that the process has finished searching
        queueMessage deadMessage{1, queueMessageType::LiveStatus, (long)getpid(), false, true};
        _msgQueue.sendMessage(deadMessage);
    }

    void findChildProcess::findFile(std::string directoryToSearch) {
        std::vector<std::string> directoryContent = fileSystemHelper::getDirectoryContent(directoryToSearch);
        
        // Search for the file
        for (auto directoryEntry : directoryContent) {
            if (fileSystemHelper::fillStatInfo(directoryToSearch + "/" + directoryEntry) == 0)
            {
                if (fileSystemHelper::isDirectory())
                {
                    tryHandleFoundEntry(directoryEntry, directoryToSearch);

                    if (_attributes.isRecursive())
                        findFile(directoryToSearch + "/" + directoryEntry);
                }
                else if (fileSystemHelper::isFile())
                {
                    tryHandleFoundEntry(directoryEntry, directoryToSearch);
                }
                else
                    throw std::runtime_error("file or directory check failed");
            }
            else
                throw std::runtime_error("stat fill info failed");
        }
    }

    void findChildProcess::tryHandleFoundEntry(std::string directoryEntry, std::string directoryOfEntry) {
        auto fileToSearch = _attributes.getFileToSearch();
        std::string directoryEntryCased = directoryEntry;

        // Change strings if the search is case insensitive
        if (_attributes.isCaseInsensitive()) 
            std::transform(directoryEntry.begin(), directoryEntry.end(), directoryEntry.begin(), ::tolower);

        // Send the found entry to the parent process
        if (directoryEntry == fileToSearch)
            sendFoundFileData(directoryEntryCased, directoryOfEntry);
    }

    void findChildProcess::sendFoundFileData(std::string &foundFile, std::string &directoryOfFile) {
        queueMessage msg{2, queueMessageType::FoundFileData, getpid()}; 
        strncpy(msg.filename, foundFile.c_str(), MAX_DATA);
        strncpy(msg.absolutePath, (directoryOfFile + "/" + foundFile).c_str(), MAX_DATA);
        _msgQueue.sendMessage(msg);
    }

    findChildProcess::~findChildProcess()
    {
    }
}