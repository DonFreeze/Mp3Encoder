#pragma once

#include "FileName.h"
#include "WavFinder.h"
#include "../lame/lame.h"
#include "../pthreadPool/include/ThreadPool.h"

using namespace threadpool;


namespace mp3encoder
{
    typedef struct
    {
        string wav;
        string mp3;
        int fileNum;
    } Argument;

    class Mp3Encoder
    {
        public:
            void startEncoding(string path, size_t numCpu  );
        protected:
            static void encodeWav( void* arg );
        private:

        WavFinder wavFinder;
        FileNameStore fileNameStore;

    };
}

