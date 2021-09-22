#include "msgQueue.h"

int msgQueue::sendMessage(message_t msg) {
    int msgid = -1;	/* Message Queue ID */

    /* Message Queue oeffnen */
    if ((msgid = msgget(KEY, PERM)) == -1)
    {
        /* error handling */
        std::cout << "Can't access message queue" << std::endl;
        return EXIT_FAILURE;
    }

    /* Nachricht verschicken */
    if (msgsnd(msgid, &msg, sizeof(msg) - sizeof(long), 0) == -1)
    {
        /* error handling */
        std::cout << "Can't send message" << std::endl;
        return EXIT_FAILURE;
    }
    //std::cout << "\nMsg Sent: pid=" << msg.childPId << " absolutePath=" << msg.absolutePath << std::endl;
    return 0;
}

void msgQueue::removeQueue() {
    std::cout << "Trying to remove queue..." << std::endl;
    std::stringstream stream;
    stream << "0x" << std::hex << (int)KEY;
    std::cout << stream.str().c_str() << std::endl; 

    forkHelper::tryFork(
                [&stream](){ 
                    execl("/bin/ipcrm", "ipcrm", "-Q", stream.str().c_str(), (char *)0); 
                    throw std::runtime_error("ipcrm failed!");}, 
                nullptr);
    wait(NULL);
}

int msgQueue::createQueue() {
    /* Message Queue neu anlegen */
    int msgid;
    if ((msgid = msgget(KEY, PERM | IPC_CREAT | IPC_EXCL)) == -1)
    {
        std::cout << "Error creating message queue" << std::endl;
        msgQueue::removeQueue();
        
        if ((msgid = msgget(KEY, PERM | IPC_CREAT | IPC_EXCL)) == -1)
        {
            std::cout << "Error creating message queue" << std::endl;
            exit(1);
        }
        else
            std::cout << "Message queue created!" << std::endl; 
    }
    else
        std::cout << "Message queue created!" << std::endl; 
    
    return msgid;
}