#ifndef MP3ENCODER_H
#define MP3ENCODER_H

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
            Mp3Encoder( );
            virtual ~Mp3Encoder();
            void startEncoding(string path, size_t numCpu  );
        protected:
            static void encodeWav( void* arg );
        private:

        WavFinder wavFinder;
        FileNameStore fileNameStore;

    };
}


#endif // MP3ENCODER_H
