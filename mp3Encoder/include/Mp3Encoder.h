/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

#pragma once

#include <iostream>
#include <string>

#include "WavFinder.h"
#include "FileName.h"

namespace mp3encoder
{
    class Mp3Encoder
    {
        public:

            ~Mp3Encoder(){  std::cout <<  "- Close Encoder " << std::endl; }
            void startEncoding( const std::string path );

        private:
            WavFinder wavFinder;

            static bool encodeWav( FileName& fileName );
    };
}

