/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <dirent.h>
#include <locale.h>
#include <fstream>

#include "../include/FileName.h"
#include "../include/FileNameStore.h"
#include "../include/WavFinder.h"

using namespace mp3encoder;
using namespace std;


unsigned int WavFinder::findWavInDir( const string directory )
{
    DIR *d;
    struct dirent *dir;
    cout << "- Search directory: " << directory << endl;

    d = opendir( directory.c_str() );

    if( !d )
    {
        throw runtime_error("Unable to open directory.");
    }    

    while( (dir = readdir(d)) != NULL )
    {
        if( isWav( static_cast<string>(dir->d_name) ) )
        {
            FileName *fileNamePtr = new FileName( directory , static_cast<string>(dir->d_name) );
            fileStore.storeFileName( *fileNamePtr );
        }
    }
   
    if( closedir(d) != 0 )
    {
        throw runtime_error("Unable to close directory.");
    }

    cout << "- Found " << getAvailableFileNumber() << " wav files" << endl;
    return getAvailableFileNumber();
}


bool WavFinder::isWav( const string fileName )
{
    size_t size = fileName.size();

    if( size >= 4 &&
        fileName.at( size-4 ) == '.' &&
        fileName.at( size-3 ) == 'w' &&
        fileName.at( size-2 ) == 'a' &&
        fileName.at( size-1 ) == 'v' )
    {
      return true;
    }

   return false;
}

unsigned int WavFinder::getAvailableFileNumber()
{
    return fileStore.getNumberOfFiles();
}

