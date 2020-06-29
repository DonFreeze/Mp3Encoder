#pragma once

#include <string>
#include "FileNameStore.h"
#include "FileName.h"
#include "lame.h"

namespace mp3Encoder
{
    class WavFinder
    {
        public:
            WavFinder(){}
            int findWavInDir( std::string directory );
            inline FileName* getNextWavFilePtr() { return fileStore.getNextFileNamePtr(); }
            int getAvailableFileNumber();
        private:
            bool isWav( std::string fileName );
            FileNameStore fileStore;
    };
}

