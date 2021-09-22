#include "findAttributes.h"
#include "format.h"
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>
#include <algorithm>

namespace myFind {

    findAttributes::findAttributes() {
        
    }

    bool findAttributes::isRecursive() {
        return this->recursive;
    }
    bool findAttributes::isCaseInsensitive() {
        return this->caseInsensitive;
    }
    std::vector<std::string> findAttributes::getFilesToSearch() {
        return this->files;
    }

    findAttributes::findAttributes(int argc, char* argv[])
    {
        this->programName = argv[0];

        // Set default values of optional parameters
        this->recursive = false;
        this->caseInsensitive = false;

        // Get optional parameters
        int option;
        while ((option = getopt(argc, argv, "Ri")) != EOF)
        {
            switch (option)
            {
                case 'i':
                    this->caseInsensitive = true;
                    break;
                case 'R':
                    this->recursive = true;
                    break;
                case '?':
                    std::cout << this->programName << " error: Unknown option." << std::endl;
                    printUsage();
                    exit(1);
                default:
                    assert(0);
                    break;
            }
        }
        // Print files to find
        if (optind < argc)
        {
            while (optind < argc)
            {
                std::string file = argv[optind++];
                if (this->caseInsensitive)
                {
                    std::transform(file.begin(), file.end(), file.begin(), ::tolower);
                }
                this->files.push_back(file);
            }
        }
        else
        {
            std::cout << this->programName << " error: No files given for searching." << std::endl;
            printUsage();
            exit(1);
        }
    }

    findAttributes ::~findAttributes()
    {
    }

    void findAttributes::printUsage() {
        std::cout << "Usage:\n\n " << this->programName << " [-R] [-i] filename [filename2] ... [filenameN]\n" << std::endl;
    }

    void findAttributes::printAttributes() {
        // Print options
        std::cout << "Case-Insensitive: " << format::boolToString(this->caseInsensitive) << std::endl;
        std::cout << "Recursive: " << format::boolToString(this->recursive) << std::endl;
        std::cout << "Files to find: " << std::endl;

        for (size_t i = 0; i < this->files.size(); i++)
        {
            std::cout << this->files.at(i) << std::endl;
        }
    }
}