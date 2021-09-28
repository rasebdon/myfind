#ifndef _FINDATTRIBUTES_H_
#define _FINDATTRIBUTES_H_
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>
#include <iostream>
#include <vector>

namespace myFind {

    class findAttributes
    {
    private:
        std::string programName;
        std::string rootSearchPath;
        std::vector<std::string> files;
        bool caseInsensitive;
        bool recursive;

        void printUsage();
    public:
        int fileToSearchIndex = 0;
        findAttributes(int argc, char* argv[]);
        findAttributes();
        ~findAttributes();
        
        void printAttributes();
        bool isRecursive();
        bool isCaseInsensitive();
        std::string getFileToSearch();
        std::string getRootSearchPath();
        std::vector<std::string> getFilesToFind();
    };
}

#endif // HEADER_H_