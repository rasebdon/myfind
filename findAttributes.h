#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <vector>

namespace myFind {

    class findAttributes
    {
    private:
        std::string programName;
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
        std::vector<std::string> getFilesToFind();
    };
}

#endif // HEADER_H_