/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */


#include "../include/FileNameStore.h"
#include <iostream>
#include <string>

using namespace std;
using namespace mp3encoder;


void FileNameStore::storeFileName( FileName& fileName )
{
    fileNameList.push_back(&fileName);
}

FileName* FileNameStore::getNextFileNamePtr()
{
    FileName* ret = fileNameList.back();
    fileNameList.pop_back();

    return ret;
}

