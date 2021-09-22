#include "findChildProcess.h"
#include "helper/fileSystemHelper.h"

namespace myFind {

    findChildProcess::findChildProcess(std::string dirToSerach, myFind::findAttributes attributes)
    {
        std::vector<std::string> files = fileSystemHelper::getDirectoryContent(dirToSerach);
        
        // Search file and fork if dir is found and -R
        for (auto file : files) {
            if (fileSystemHelper::fillStatInfo(dirToSerach + "/" + file) == 0)
            {
                if(fileSystemHelper::isDirectory() )
                {
                    if(attributes.isRecursive()) {
                        findChildProcess findChildProcess(dirToSerach + "/" + file, attributes);
                    }
                }
                else if(fileSystemHelper::isFile())
                {
                    //it's a file
                    auto fileToSearch = attributes.getFileToSearch();
                    message_t msg = {
                        .mType = (long)1,
                        .childPId = (long)getpid(),
                        .quitting = false,
                        .starting = false
                    };

                    strncpy(msg.absolutePath, fileToSearch.c_str(), MAX_DATA);
                    strncpy(msg.absolutePath, (dirToSerach + "/" + fileToSearch).c_str(), MAX_DATA);

                    if (attributes.isCaseInsensitive())
                        std::transform(file.begin(), file.end(), file.begin(), ::tolower);
                        
                    if (file == fileToSearch) 
                        msgQueue::sendMessage(msg);
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

        msgQueue::sendMessage(
            {
                .mType = 1,
                .childPId = (long)getpid(),
                .quitting = true,
                .starting = false
            }
        );
    }

    findChildProcess::~findChildProcess()
    {
    }
}