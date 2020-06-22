#ifndef WAVFINDER_H
#define WAVFINDER_H

#include "FileNameStore.h"
#include "FileName.h"
#include <string>


namespace mp3Encoder
{
    class WavFinder
    {
        public:
            WavFinder( ){}
            int findWavInDir(std::string directory);
            inline FileName getNextWavFile() { return fileStore.getNextFileName();}

            int getAvailableFileNumber();

        private:
            bool isWav( std::string fileName );
            FileNameStore fileStore;
    };
}
#endif // WAVFINDER_H
