/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 */

#pragma once

#include <string>
#include "FileNameStore.h"
#include "FileName.h"

namespace mp3encoder
{
    class WavFinder
    {
        public:
            unsigned int findWavInDir( std::string directory );
            unsigned int getAvailableFileNumber();
            inline FileName* getNextWavFilePtr() { return fileStore.getNextFileNamePtr(); }
        private:
            bool isWav( std::string fileName );
            FileNameStore fileStore;
    };
}

