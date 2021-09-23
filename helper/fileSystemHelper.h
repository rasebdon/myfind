#ifndef _FILESYSTEMHELPER_H_
#define _FILESYSTEMHELPER_H_

#include <iostream>
#include <vector>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

class fileSystemHelper
{
    static struct stat s;
public:
    static std::string getWorkingDirectory();
    static std::vector<std::string> getDirectoryContent(std::string directory);
    static int fillStatInfo(std::string path);
    static bool isDirectory();
    static bool isFile();
};

#endif