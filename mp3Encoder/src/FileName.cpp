/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#include "../include/FileName.h"
#include <iostream>
#include <string>

using namespace mp3encoder;

std::string FileName::getWavWithPath()
{
#ifdef _WIN32
   return path + "\\" + name;
#else
    return path + "/" + name;
#endif // _WIN32
}

std::string FileName::getMp3WithPath()
{
    std::string mp3Name = name;
    mp3Name.replace( mp3Name.end()-3, mp3Name.end(), "mp3" );

#ifdef _WIN32
    return path + "\\" + mp3Name;
#else
    return path + "/" + mp3Name;
#endif // _WIN32
}

std::string FileName::getWav()
{
   return name;
}

std::string FileName::getMp3()
{
    std::string mp3Name = name;
    mp3Name.replace( mp3Name.end()-3, mp3Name.end(), "mp3" );
    return  mp3Name;
}
