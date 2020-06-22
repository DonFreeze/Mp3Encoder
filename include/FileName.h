#ifndef FILENAME_H
#define FILENAME_H

#include <string>

class FileName
{
   /* public:
    enum Status
    {

    }
*/
    public:
        FileName(std::string path, std::string name) : path(path), name(name) {}
        virtual ~FileName();

        inline std::string getNameWav() { return name; }
        inline std::string getNameWavWithPath() { return path + "/" + name; };
         std::string getNameMp3WithPath() ;
        // todo get fileStatus();
    private:
        std::string name;
        std::string path;
};
#endif // FILENAME_H
