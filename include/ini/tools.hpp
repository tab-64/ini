#ifndef __TOOLS_HPP__
#define __TOOLS_HPP__

#include <fstream>
#include <string>
#include <sys/stat.h>

namespace tab{

class Tools{
public:
    static bool isFileExist(const std::string& filename){
        struct stat filestat;
        return stat(filename.c_str(), &filestat) == 0;
    }

    static bool isFileExist(const char* filename){
        struct stat filestat;
        return stat(filename, &filestat) == 0;
    }

    static void createFile(const std::string& filename){
        std::ofstream tmp(filename);
    }

};

} // namespace tab;

#endif // __TOOLS_HPP__