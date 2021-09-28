#include "fileSystemHelper.h"

std::string fileSystemHelper::getWorkingDirectory() {
    char buffer[512];
    if (getcwd(buffer, sizeof(buffer)) != NULL)
    {
        //std::cout << "Current working directory : " << buffer << std::endl;
        return buffer;
    }
    else
    {
        perror("getcwd() error");
        exit(1);
    }
}

std::vector<std::string> fileSystemHelper::getDirectoryContent(std::string directory){
    DIR* dir; struct dirent* diread;
        std::vector<std::string> files;

        if ((dir = opendir(directory.c_str())) != nullptr)
        {
            while ((diread = readdir(dir)) != nullptr)
            {
                if((std::string)diread->d_name != ".." && (std::string)diread->d_name != ".") {
                    files.push_back(diread->d_name);
                }
            }
            closedir(dir);
        }
        else
        {
            std::cout << "Could not open directory. Invalid search path, or missing permissions." << std::endl;
            exit(EXIT_FAILURE);
        }
        return files;
}

struct stat fileSystemHelper::s;

int fileSystemHelper::fillStatInfo(std::string path) {
    return stat((path).c_str(), &s);
}

bool fileSystemHelper::isDirectory(){
    return s.st_mode & S_IFDIR;
}

bool fileSystemHelper::isFile(){
    return s.st_mode & S_IFREG;
}