/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */


#include <ctype.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Mp3Encoder.h"

using namespace std;
using namespace mp3encoder;


int main( int argc, char const *argv[] )
{
    #ifdef _WIN32
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        size_t numCPU = sysinfo.dwNumberOfProcessors;
    #else
        size_t numCPU = sysconf(_SC_NPROCESSORS_ONLN);
    #endif // _WIN32


    cout << "------------------------------------------------------- " << endl;
    cout << "                     WAV TO MP3 Encoder                 " << endl;
    cout << "------------------------------------------------------- " << endl;

    if( argc < 2 )
    {
        cout << "Please set a directory when starting the app " << endl;
        return 0;
    }

    Mp3Encoder encoder;
    encoder.startEncoding( static_cast<string>( argv[1] ), numCPU ) ;

    return 0;
}
