#ifndef MP3ENCODER_H
#define MP3ENCODER_H

#include <ctype.h>
#include <stdio.h>
#include <iostream>

#include "FileName.h"


#include "Mp3Encoder.h"
#include <string>
#include <fstream>

#include <thread>
#include <vector>
#include <string>
#include "WavFinder.h"



namespace mp3Encoder
{

    class Mp3Encoder
    {
        public:
            Mp3Encoder();
            virtual ~Mp3Encoder();

            void encodeFilesInDirectory( std::string directory);
        private:
            void encodeWav();

            WavFinder wavFinder;
    };

}
#endif // MP3ENCODER_H
