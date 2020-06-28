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
     //  std::vector<std::thread*> threadList;

    //   void eraseFromThreadList( std::thread* threadToErase  );


    /*class Mp3Encoder
    {
        public:
            Mp3Encoder();
            virtual ~Mp3Encoder();

            void encodeFilesInDirectory( std::string directory);
             static void encodeWav(std::string wavFileName, std::string mp3FileName );
        private:
            std::vector<std::thread*> threadList;
            WavFinder wavFinder;

            void eraseFromThreadList( std::thread* threadToErase  );
    };*/

}
#endif // MP3ENCODER_H
