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
    };
}