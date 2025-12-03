#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <cstdlib>

class FileSystem
{
public:
    static std::string getPath(const std::string& path)
    {
        // Adjust this base path if your resources are elsewhere
        // For example: return "C:/MyProject/assets/" + path;
        static std::string root = "";
        return root + path;
    }
};

#endif