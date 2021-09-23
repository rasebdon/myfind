#include "msgQueue.h"

msgQueue::msgQueue(int key, int permissions) {
    _key = key;
    _premissions = permissions;
}

msgQueue::~msgQueue() {
    removeQueue();
}

int msgQueue::createQueue() {
    /* Message Queue neu anlegen */
    if ((_queueId = msgget(KEY, PERM | IPC_CREAT | IPC_EXCL)) == -1)
    {
        std::cout << "Queue with KEY " << (int)KEY << " already exists. Do you want to replace it? [y/N]" << std::endl;
        char replaceQueueChoice;
        std::cin >> replaceQueueChoice;
        switch (replaceQueueChoice)
        {
        case 'Y':
        case 'y':
            break;
        default:
            std::cout << "Termination program..." << std::endl;
            exit(0);
            break;
        }
        msgQueue::removeQueue();
        
        if ((_queueId = msgget(KEY, PERM | IPC_CREAT | IPC_EXCL)) == -1)
        {
            std::cout << "Error creating message queue" << std::endl;
            exit(1);
        }
    }
    
    return _queueId;
}

int msgQueue::sendMessage(message_t msg) {
    if (msgsnd(_queueId, &msg, sizeof(msg) - sizeof(long), 0) == -1)
    {
        /* error handling */
        std::cout << "Can't send message" << std::endl;
        return EXIT_FAILURE;
    }
    //std::cout << "\nMsg Sent: pid=" << msg.childPId << " absolutePath=" << msg.absolutePath << std::endl;
    return 0;
}

void msgQueue::removeQueue() {
    // std::cout << "Trying to remove queue..." << std::endl;
    std::stringstream stream;
    stream << "0x" << std::hex << (int)KEY;
    forkHelper::tryFork(
                [&stream](){ 
                    execl("/bin/ipcrm", "ipcrm", "-Q", stream.str().c_str(), (char *)0); 
                    throw std::runtime_error("ipcrm failed!");}, 
                nullptr);
    wait(NULL);
}

void msgQueue::receiveMessage(message_t &msg) {
    if (msgrcv(_queueId, &msg, sizeof(msg) - sizeof(long), 0, 0) == -1)
    {
        std::cout << "Can't receive from message queue" << std::endl;
        removeQueue();
        exit(1);
    }
}