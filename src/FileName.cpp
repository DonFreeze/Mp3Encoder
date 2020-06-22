#include "FileName.h"
#include <iostream>
#include <string>


FileName::~FileName()
{
    //dtor
}

/*
std::string FileName::getFileNameWithPath();
{
//    if( os == linux)
    {
        return path + "/" + name;
    }
 /*   else
    {
        return Path + "\" + Name;
    }
*
}
*/

std::string FileName::getNameMp3WithPath()
{
    std::string mp3Name = name;
    mp3Name.replace( mp3Name.end()-3, mp3Name.end(),"mp3");
    return path + "/" + mp3Name;

};
