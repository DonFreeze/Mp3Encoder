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
    mp3Name.replace( mp3Name.end()-3, mp3Name.end(), "mp3" );

#ifdef _WIN32
    return path + "\\" + mp3Name;
#else
    return path + "/" + mp3Name;
#endif // _WIN32
}

const char* FileName::getCharNameMp3WithPath()
{
    return getNameMp3WithPath().c_str();
}

const char* FileName::getCharNameWavWithPath()
{
    return getNameWavWithPath().c_str();
}