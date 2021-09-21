#include "findAttributes.h"
#include "format.h"
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

namespace myFind {

    findAttributes::findAttributes() {
        
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
                    std::cerr << this->programName << " error: Unknown option.\n";
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
                this->files.push_back(file);
            }
        }
        else
        {
            std::cerr << this->programName << " error: No files given for searching.\n";
            printUsage();
            exit(1);
        }
    }

    findAttributes ::~findAttributes()
    {
    }

    void findAttributes::printUsage() {
        std::cout << "Usage:\n\n " << this->programName << " [-R] [-i] filename [filename2] ... [filenameN]\n\n";
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