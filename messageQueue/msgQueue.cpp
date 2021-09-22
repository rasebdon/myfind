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