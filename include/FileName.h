#ifndef FILENAME_H
#define FILENAME_H

#include <string>

class FileName
{

    public:
        FileName(std::string path, std::string name) : path(path), name(name) {}
        virtual ~FileName();

        inline std::string getNameWav() { return name; }
        inline std::string getNameWavWithPath() { return path + "/" + name; };
         std::string getNameMp3WithPath() ;
    private:
        std::string path;
        std::string name;
};
#endif // FILENAME_H
