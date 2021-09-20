#include "findAttributes.h"
#include "format.h"
#include <assert.h>
#include <sys/wait.h>
#include <unistd.h>

namespace myFind {

    findAttributes::findAttributes(int argc, char* argv[])
    {
        programName = argv[0];

        // Get optional parameters
        int option;
        while ((option = getopt(argc, argv, "Ri")) != EOF)
        {
            switch (option)
            {
                case 'i':
                    caseInsensitive = true;
                    break;
                case 'R':
                    recursive = true;
                    break;
                case '?':
                    std::cerr << programName << " error: Unknown option.\n";
                    printUsage();
                    exit(1);
                default:
                    assert(0);
                    break;
            }
        }
        // Get files (required)
        std::vector<std::string> files;
        // Print files to find
        if (optind < argc)
        {
            while (optind < argc)
            {
                std::string file = argv[optind++];
                files.push_back(file);
            }
        }
        else
        {
            std::cerr << programName << " error: No files given for searching.\n";
            printUsage();
            exit(1);
        }
    }

    findAttributes ::~findAttributes()
    {
    }

    void findAttributes::printUsage() {
        std::cout << "Usage:\n\n " << programName << " [-R] [-i] filename [filename2] ... [filenameN]\n\n";
    }

    void findAttributes::printAttributes() {
        // Print options
        std::cout << "Case-Insensitive: " << format::boolToString(caseInsensitive) << std::endl;
        std::cout << "Recursive: " << format::boolToString(recursive) << std::endl;
        std::cout << "Files to find: " << std::endl;

        for (size_t i = 0; i < files.size(); i++)
        {
            std::cout << files.at(i) << std::endl;
        }
    }
}