#ifndef WAVFINDER_H
#define WAVFINDER_H

#include "FileNameStore.h"
#include "FileName.h"
#include <string>
#include "lame/lame.h"

namespace mp3Encoder
{
    class WavFinder
    {
        public:
            WavFinder( ){}
            int findWavInDir(std::string directory);
            inline FileName* getNextWavFilePtr() { return fileStore.getNextFileNamePtr();}

            int getAvailableFileNumber();

        private:
            bool isWav( std::string fileName );
            FileNameStore fileStore;
    };
}
#endif // WAVFINDER_H
