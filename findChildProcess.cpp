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
        _msgQueue.sendMessage(
            {
                .mType = 1,
                .childPId = (long)getpid(),
                .quitting = false,
                .starting = true
            }
        );

        findFile(_rootDirectoryToSearch);

        _msgQueue.sendMessage(
            {
                .mType = 1,
                .childPId = (long)getpid(),
                .quitting = true,
                .starting = false
            }
        );
    }

    void findChildProcess::findFile(std::string directoryToSearch) {
        std::vector<std::string> directoryContent = fileSystemHelper::getDirectoryContent(directoryToSearch);
        
        for (auto directoryEntry : directoryContent) {
            if (fileSystemHelper::fillStatInfo(directoryToSearch + "/" + directoryEntry) == 0)
            {
                if (fileSystemHelper::isDirectory())
                {
                    auto fileToSearch = _attributes.getFileToSearch();
                    if (directoryEntry == fileToSearch)
                    {
                        message_t msg = {
                            .mType = (long)1,
                            .childPId = (long)getpid(),
                            .quitting = false,
                            .starting = false
                        };
                        strncpy(msg.filename, fileToSearch.c_str(), MAX_DATA);
                        strncpy(msg.absolutePath, (directoryToSearch + "/" + fileToSearch).c_str(), MAX_DATA);
                        _msgQueue.sendMessage(msg);
                    }

                    if (_attributes.isRecursive())
                        findFile(directoryToSearch + "/" + directoryEntry);
                }
                else if (fileSystemHelper::isFile())
                {
                    //it's a file
                    auto fileToSearch = _attributes.getFileToSearch();

                    if (_attributes.isCaseInsensitive())
                        std::transform(directoryEntry.begin(), directoryEntry.end(), directoryEntry.begin(), ::tolower);

                    if (directoryEntry == fileToSearch)
                    {
                        message_t msg = {
                            .mType = (long)1,
                            .childPId = (long)getpid(),
                            .quitting = false,
                            .starting = false
                        };
                        strncpy(msg.filename, fileToSearch.c_str(), MAX_DATA);
                        strncpy(msg.absolutePath, (directoryToSearch + "/" + fileToSearch).c_str(), MAX_DATA);
                        _msgQueue.sendMessage(msg);
                    }
                }
                else
                {
                    std::cout << "file or directory check failed" << std::endl;
                    exit(1);
                }
            }
            else
            {
                std::cout << "stat info fill failed" << std::endl;
                exit(1);
            }
        }
    }

    findChildProcess::~findChildProcess()
    {
    }
}