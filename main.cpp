#include "messageQueue/msgQueue.h"
#include "findAttributes.h"
#include "findRootProcess.h"
#include <signal.h>
#include <sys/wait.h>
// Plan:
// Start server (reciever for findings)
// Start client for every file
// Send path to server if found
// Stop server when all processes (count == 0) have been stopped 

int main(int argc, char* argv[]) {
    // Get the user given search attributes
    myFind::findAttributes attributes = myFind::findAttributes(argc, argv);
    attributes.printAttributes();
    
    myFind::findRootProcess rootProcess = myFind::findRootProcess(attributes);
    // Start the finders (one for each file)
    rootProcess.startChildrenProcesses();
    // Start the "Reciever Server" for findings
    rootProcess.receiveMessages();

    wait(nullptr);
    return 0;
}
