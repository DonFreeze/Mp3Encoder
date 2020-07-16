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

#include "mp3Encoder/include/Mp3Encoder.h"

using namespace std;
using namespace mp3encoder;


int main( int argc, char const *argv[] )
{

    cout << "------------------------------------------------------- " << endl;
    cout << "                     WAV TO MP3 Encoder                 " << endl;
    cout << "------------------------------------------------------- " << endl;

    if( argc < 2 )
    {
        cout << "Please set a directory when starting the app " << endl;
        return -1;
    }

    Mp3Encoder encoder;
    try
    {
        encoder.startEncoding( static_cast<string>( argv[1] ) ) ;
    }
    catch( exception e )
    {
        cout << e.what() << "\n";
    }
    catch( const char* e )
    {
        cout << e << "\n";
    }
    return 0;
}
