#pragma once

#include <string>

using namespace std;

class FileName
{
    public:
        FileName( string path, string name) : path(path), name(name) {}
        inline string getNameWav() { return this->name; }
        string getNameWavWithPath();
        string getNameMp3WithPath();
    private:
        string path;
        string name;
};

