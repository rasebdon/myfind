#include "findClient.h"
#include "findBehaviour/findAttributes.h"
#include "messageQueue/msgQueue.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <dirent.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sys/stat.h>
#include <algorithm>

namespace myFind {

    findClient::findClient(std::string dirToSerach, myFind::findAttributes attributes)
    {
        DIR* dir; struct dirent* diread;
        std::vector<std::string> files;

        // Read directory content
        if ((dir = opendir(dirToSerach.c_str())) != nullptr)
        {
            while ((diread = readdir(dir)) != nullptr)
            {
                if((std::string)diread->d_name != ".." && (std::string)diread->d_name != ".") {
                    files.push_back(diread->d_name);
                }
            }
            closedir(dir);
        }
        else
        {
            std::cout << "opendir" << std::endl;
            exit(EXIT_FAILURE);
        }

        long oldPid = (long)getpid();
        std::string brokenOutFolder = "";

        struct stat s;
        // Search file and fork if dir is found and -R
        for (auto file : files) {
            if( stat((dirToSerach + "/" + file).c_str(), &s) == 0 )
            {
                if( s.st_mode & S_IFDIR )
                {
                    //it's a directory
                    if(attributes.isRecursive()) {
                        // Start new subprocess
                        pid_t pid = fork();

                        // New client
                        if (pid == 0)
                        {
                            brokenOutFolder = file;
                                msgQueue::sendMessage(
                                    {
                                        .mType = 2,
                                        .childPId = (long)getpid(),
                                        .quitting = false,
                                        .starting = true
                                    }
                                );
                            break;
                        }
                        else if (pid == -1)
                        {
                            std::cout << "Fatal error, stopping program" << std::endl;
                            exit(1);
                        }
                    }
                }
                else if( s.st_mode & S_IFREG )
                {
                    //it's a file
                    for (auto fileToSearch : attributes.getFilesToSearch())
                    {
                        message_t msg = {
                            .mType = (long)1,
                            .childPId = (long)getpid(),
                            .quitting = false,
                            .starting = false
                        };

                        strncpy(msg.absolutePath, fileToSearch.c_str(), MAX_DATA);
                        strncpy(msg.absolutePath, (dirToSerach + "/" + fileToSearch).c_str(), MAX_DATA);

                        if (attributes.isCaseInsensitive())
                        {
                            std::transform(file.begin(), file.end(), file.begin(), ::tolower);
                            if(file == fileToSearch) {
                                // Write to msg queue
                                msgQueue::sendMessage(msg);
                            }
                        }
                        else
                        {
                            if(file == fileToSearch) {
                                // Write to msg queue
                                msgQueue::sendMessage(msg);
                            }
                        }
                    }
                }
                else
                {
                    //something else
                    std::cout << "What did you bring upon this cursed land???" << std::endl;
                    exit(1);
                }
            }
            else
            {
                //error
                exit(1);
            }
        }

        if(oldPid != (long)getpid()) {
            // std::cout << "Searching " << brokenOutFolder << " oldPid: " << oldPid << " newPid: " << (long)getpid() << std::endl;
            myFind::findClient client = myFind::findClient(dirToSerach + "/" + brokenOutFolder, attributes);
        }
        
        // Wait for child processes
        wait(NULL);

        msgQueue::sendMessage(
            {
                .mType = 1,
                .childPId = oldPid,
                .quitting = true,
                .starting = false
            }
        );

        exit(0);
    }

    findClient::~findClient()
    {
    }
}