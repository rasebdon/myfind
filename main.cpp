#include "messageQueue/msgQueue.h"
#include "findBehaviour/findAttributes.h"
#include "findServer.h"
#include <signal.h>
#include <sys/wait.h>
// Plan:
// Start server (reciever for findings)
// Start client for every folder
// Send path to server if found
// Start new client in clients if program was run with -R and new folder found
//      => Tell server that new clients have been started
// Stop clients if folder is fully searched
//      => Tell server that this process has stopped
// Stop server when all processes (count == 0) have been stopped 

int main(int argc, char* argv[]) {
    // Get attributes
    myFind::findAttributes attributes = myFind::findAttributes(argc, argv);

    attributes.printAttributes();

    // Start server with attributes
    myFind::findServer server = myFind::findServer(attributes);
    wait(nullptr);
    server.removeQueue();
    return 0;
}
