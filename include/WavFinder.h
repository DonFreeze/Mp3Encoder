#pragma once

#include <string>
#include "FileNameStore.h"
#include "FileName.h"
#include "lame.h"

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

