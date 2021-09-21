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
        findAttributes(int argc, char* argv[]);
        findAttributes();
        ~findAttributes();
        
        void printAttributes();
        bool isRecursive();
        bool isCaseInsensitive();
        std::vector<std::string> getFilesToSearch();
    };
}

#endif // HEADER_H_