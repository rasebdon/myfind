#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

void print_usage(std::string program_name) {
    cout << "Usage:\n\n " << program_name << " [-R] [-i] filename [filename2] ... [filenameN]\n\n";
}

string BoolToString(bool b) {
    return b ? "true" : "false";
}

int main(int argc, char* argv[]) {
    string program_name = argv[0];

    // Get the optional parameters
    bool recursive = false;
    bool caseInsensitive = false;

    int optionCount = 0;
    int option;
    while ((option = getopt(argc, argv, "Ri")) != EOF)
    {
        switch (option)
        {
            case 'i':
                caseInsensitive = true;
                optionCount++;
                break;
            case 'R':
                recursive = true;
                optionCount++;
                break;
            case '?':
                cerr << program_name << " error: Unknown option.\n";
                print_usage(program_name);
                exit(1);
            default:
                assert(0);
                break;
        }
    }
    // Print options
    cout << "Case-Insensitive: " << BoolToString(caseInsensitive) << endl;
    cout << "Recursive: " << BoolToString(recursive) << endl;
    cout << "Files to find: " << endl;
    
    vector<string> files;
    // Print files to find
    if ( optind < argc ) {
        while ( optind < argc ) {
            string file = argv[optind++];
            files.push_back(file);
            cout << file << endl;
        }
    }
    else {
        cerr << program_name << " error: No files given for searching.\n";
        print_usage(program_name);
        exit(1);
    }

    cout << endl;

    // const int childAmount = 5;
    // pid_t childs[5];
    // const long parentPId = (long)getpid();

    // for (int i = 0; i < 5; i++)
    // {
    //     childs[i] = fork();

    //     if (childs[i] == -1)
    //     {
    //         perror("Failed to fork");
    //         return 1;
    //     }

    //     if (childs[i] == 0)
    //     {
    //         printf("I am child %ld \n", (long)getpid());
    //         break;
    //     }
    // }

    // sleep(4);

    // if ((long)getpid() == parentPId)
    //     printf("Parent done!\n");
    return 0;
}