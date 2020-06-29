#include "FileNameStore.h"
#include <iostream>
#include <string>

using namespace std;
using namespace mp3Encoder;



void FileNameStore::storeFileName( FileName& fileName )
{
    fileNameList.push_back(&fileName);
}


FileName* FileNameStore::getNextFileNamePtr()
{
    FileName* ret = fileNameList.back();
    fileNameList.pop_back();
    return ret;

    // TODO exception handling
}

