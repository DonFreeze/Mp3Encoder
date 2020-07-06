/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 */

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
    } FileNameArg;

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

