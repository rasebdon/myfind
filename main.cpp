#include "messageQueue/msgQueue.h"
#include "findBehaviour/findAttributes.h"
#include "findServer.h"
#include <signal.h>

// Plan:
// Start server (reciever for findings)
// Start client for every folder
// Send path to server if found
// Start new client in clients if program was run with -R and new folder found
//      => Tell server that new clients have been started
// Stop clients if folder is fully searched
//      => Tell server that this process has stopped
// Stop server when all processes (count == 0) have been stopped 

void signalHandler(int sig) {
    std::cout << "Are you sure you want to quit?\n[Y/n] ";
    char input = 'n';
    std::cin >> input;
    switch (input)
    {
    case 'y':
    case 'Y':
        std::cout << "Quitting...\n";
        exit(0);
        break;
    case 'n':
    case 'N':
        std::cout << "Continuing...\n";
        break;
    default:
        std::cout << "Invalid input, continuing...\n";
        break;
    }
}

int main(int argc, char* argv[]) {
    // Define exit signals
    (void) signal(SIGINT, signalHandler);
    (void) signal(SIGHUP, signalHandler);
    (void) signal(SIGQUIT, signalHandler);

    // Get attributes
    myFind::findAttributes attributes = myFind::findAttributes(argc, argv);

    attributes.printAttributes();

    

    // Start server with attributes
    myFind::findServer server = myFind::findServer(attributes);
    
    return 0;
}
