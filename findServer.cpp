#include "findServer.h"
#include "findClient.h"
#include <unistd.h>

namespace myFind {

    findServer::findServer(myFind::findAttributes attributes)
    {
        this->_attributes = attributes;

        // Start first client
        this->activeClients = 0;

        // Get folder
        std::string curDir = "";
        char buffer[512];
        if (getcwd(buffer, sizeof(buffer)) != NULL)
        {
            std::cout << "Current working directory : " << buffer << std::endl;
            curDir = buffer;
        }
        else
        {
            perror("getcwd() error");
            exit(1);
        }

        pid_t pid = fork();



        // First client process starts
        if(pid == 0) {
            myFind::findClient client = myFind::findClient(curDir, attributes);
        }
        else if (pid == -1) {
            std::cerr << "Fatal error, stopping program";
            exit(1);
        }
        else {
            this->activeClients++;
        }

        while(this->activeClients > 0) {
            // Message queue printing
        }
    }

    findServer::~findServer()
    {
    }
}

