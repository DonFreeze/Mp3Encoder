#include "FileName.h"
#include <iostream>
#include <string>


FileName::~FileName()
{
    //dtor
}


std::string FileName::getNameWavWithPath()
{
#ifdef _WIN32
   return path + "\\" + name;
#else
    return path + "/" + name;
#endif // _WIN32

}


std::string FileName::getNameMp3WithPath()
{
    std::string mp3Name = name;
    mp3Name.replace( mp3Name.end()-3, mp3Name.end(),"mp3");


#ifdef _WIN32
    return path + "\\" + mp3Name;
#else
    return path + "/" + mp3Name;
#endif // _WIN32



};
