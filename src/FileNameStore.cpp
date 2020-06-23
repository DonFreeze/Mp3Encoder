#include "FileNameStore.h"
#include <iostream>
#include <string>

using namespace std;
using namespace mp3Encoder;

FileNameStore::FileNameStore()
{

}

FileNameStore::~FileNameStore()
{
    // todo clean
}


void FileNameStore::storeFileName( FileName& fileName )
{
    cout << "store: " << fileName.getNameWav() << endl;

    fileNameList.push_back(&fileName);
}



FileName* FileNameStore::getNextFileNamePtr()
{

   /* if (fileNameList.size() > 0)
    {

    }
    else
    {
        cout << "Error vector is empty: "  << endl; // todo error handling
    }*/

        FileName* ret = fileNameList.back();
        fileNameList.pop_back();
        return ret;

        // TODO exception handling
}

