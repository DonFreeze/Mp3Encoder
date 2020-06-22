#include <string>
#include <iostream>
#include <string>
#include <dirent.h>

#include "FileName.h"
#include "FileNameStore.h"
#include "WavFinder.h"

using namespace mp3Encoder;
using namespace std;


int WavFinder::findWavInDir(std::string directory)
{
    DIR *d;
    struct dirent *dir;
    int foundWavNumber = 0;
    cout << "WavFinder search directory: " << directory << endl;
    d = opendir( directory.c_str() );
    if( d )
    {
        while( (dir = readdir(d))!= NULL )
        {
            if( isWav( static_cast<string>(dir->d_name) ) )
            {
                FileName *fileNamePtr = new FileName( directory , static_cast<string>(dir->d_name) );
                fileStore.storeFileName( *fileNamePtr );
                foundWavNumber++;
            }
        }
    }
    return foundWavNumber;
}


bool WavFinder::isWav( string fileName )
{
    bool ret = false;

    size_t size = fileName.size();

    if (size >= 4 &&
        fileName.at( size-4 ) == '.' &&
        fileName.at( size-3 ) == 'w' &&
        fileName.at( size-2 ) == 'a' &&
        fileName.at( size-1 ) == 'v')
    {
      ret = true;
    }

   return ret;
}

int WavFinder::getAvailableFileNumber()
{
    return fileStore.getNumberOfFiles();
}

