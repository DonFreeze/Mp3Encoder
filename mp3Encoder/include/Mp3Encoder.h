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
#include "FileNameStore.h"

namespace mp3encoder
{
    class Mp3Encoder
    {
        public:
            void startEncoding( string path );

        private:
            WavFinder wavFinder;
            FileNameStore fileNameStore;

            static bool encodeWav(const string& input );
    };
}

