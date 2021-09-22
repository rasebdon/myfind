#include "findServer.h"
#include "findClient.h"
#include "messageQueue/msgQueue.h"
#include <unistd.h>
#include <sys/wait.h>
#include <iomanip>

namespace myFind {

    findServer::findServer(myFind::findAttributes attributes)
    {
        this->_attributes = attributes;

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

        // Message queue printing
        message_t msg;	/* Buffer fuer Message */
        int msgid = -1;	/* Message Queue ID */

    tryCreateQueue:
        /* Message Queue neu anlegen */
        if ((msgid = msgget(KEY, PERM | IPC_CREAT | IPC_EXCL)) == -1)
        {
            pid_t queueCleanPid = fork();
            if(queueCleanPid == 0)
            {
                std::stringstream stream;
                stream << "0x" << std::hex << (int)KEY;
                std::cout << stream.str(); 
                execl("/bin/ipcrm", "ipcrm", "-Q", stream.str().c_str(), (char *)0);
            }

            /* error handling */
            std::cerr << "Error creating message queue\n";
            std::cerr << "Cleaning up message queue\n";
            wait(NULL);
            goto tryCreateQueue;
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

        
        this->activeClients = 1;

        while (this->activeClients > 0)
        {
            if (msgrcv(msgid, &msg, sizeof(msg) - sizeof(long), 0, 0) == -1)
            {
                /* error handling */
                std::cerr << "Can't receive from message queue\n";
                break;
            }
            // Child process started
            if(msg.quitting) {
                this->activeClients--;
                std::cout << "Child killed, processes left: " << this->activeClients << std::endl;
            }
            // Child process stopped
            else if(msg.starting) {
                this->activeClients++;
                std::cout << "Child added, processes left: " << this->activeClients << std::endl;
            }
            // A file has been found!
            else if(((std::string)(msg.absolutePath)).size() > 0 || ((std::string)(msg.filename)).size() > 0) {
                // <pid>: <filename>: <complete-path-to-found-file>\n
                std::cout << msg.childPId << ": " << msg.filename << ": " << msg.absolutePath << "\n";
            }
        }
    }

    findServer::~findServer()
    {
    }
}

