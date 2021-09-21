#include "findClient.h"
#include "findBehaviour/findAttributes.h"
#include <unistd.h>
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
                files.push_back(diread->d_name);
            }
            closedir(dir);
        }
        else
        {
            std::cerr << "opendir";
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
                            break;
                        }
                        else if (pid == -1)
                        {
                            std::cerr << "Fatal error, stopping program";
                            exit(1);
                        }
                    }
                }
                else if( s.st_mode & S_IFREG )
                {
                    //it's a file
                    for (auto fileToSearch : attributes.getFilesToSearch())
                    {
                        if (attributes.isCaseInsensitive())
                        {
                            std::transform(file.begin(), file.end(), file.begin(), ::tolower);
                            if(file == fileToSearch) {
                                // Write to msg queue
                                std::cout << "FOUND!";
                            }
                        }
                        else
                        {
                            if(file == fileToSearch) {
                                // Write to msg queue
                            }
                        }
                    }
                }
                else
                {
                    //something else
                    std::cout << "What did you bring upon this cursed land???";
                    exit(1);
                }
            }
            else
            {
                //error
                exit(1);
            }
        }

        if(oldPid != getpid()) {
            //myFind::findClient client = myFind::findClient(dirToSerach + "/" + brokenOutFolder, attributes);
        }
    }

    findClient::~findClient()
    {
    }
}