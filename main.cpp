/*
    VERTS MyFind:
    Finds specific files in the current directory and returns their absoute path
    Usage:
    ./myfind [-R] [-i] searchpath filename1 [filename2] ...[filenameN]
    -R: 
        should switch myfind in recursive mode 
        (else the files should only be search in the defined folder) 
    -i: 
        case in-sensitive search 
    searchpath:
        can be an absolute or a relative path. 
    filename:
        only filenames as plain string 
        no support for paths, subpaths, wildcards required. 
    @file main.cpp
    @author Michael Duskanich and Raphael Dohnalek
    @version 1.0
*/
#include "messageQueue/msgQueue.h"
#include "findAttributes.h"
#include "findRootProcess.h"
#include <signal.h>
#include <sys/wait.h>

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
