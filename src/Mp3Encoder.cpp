/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 */

#include <iostream>
#include <string>
#include <stdio.h>

#include "Mp3Encoder.h"
#include "WavFinder.h"
#include "../lame/lame.h"
#include "../pthreadPool/include/ThreadPool.h"

using namespace mp3encoder;
using namespace threadpool;
using namespace std;

void Mp3Encoder::encodeWav( void* arg )
{
    try
    {
        FileName *fileNamePtr = ( FileName* ) arg;
        int read, write;

        FILE *wav = fopen(fileNamePtr->getCharNameWavWithPath(), "rb");
        FILE *mp3 = fopen(fileNamePtr->getCharNameMp3WithPath(), "wb");

        const int PCM_SIZE = 8192;
        const int MP3_SIZE = 8192;

        short int pcm_buffer[PCM_SIZE*2];
        unsigned char mp3_buffer[MP3_SIZE];

        lame_t lame = lame_init();
        lame_set_in_samplerate(lame, 48000);
        lame_set_VBR(lame, vbr_default);
        lame_set_quality(lame, 5);

        if (lame_init_params(lame) < 0)
        {
            fclose(mp3);
            fclose(wav);
        }
        else
        {
            do
            {
                read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, wav);
                if( read == 0 )
                    write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
                else
                    write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
                fwrite(mp3_buffer, write, 1, mp3);
            } while ( read != 0 );

            // Mutex
            cout << "." ;
            cout.flush();
            //mutex
            fclose(mp3);
            fclose(wav);
            lame_close(lame);
        }
    }
    catch( std::exception e )
    {
        std::cout << e.what() << "\n";
    }
}

void Mp3Encoder::startEncoding( string path )
{
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    size_t numCPU = sysinfo.dwNumberOfProcessors;
#else
    size_t numCPU = sysconf(_SC_NPROCESSORS_ONLN);
#endif // _WIN32

    if( wavFinder.findWavInDir( path ) > 0 )
    {
        ThreadPool threadPool( numCPU, wavFinder.getAvailableFileNumber() );
        cout << "- Start to encode files:  ";
        cout.flush();

        while( wavFinder.getAvailableFileNumber() )
        {
            FileName* filenamePtr = wavFinder.getNextWavFilePtr();
            Task* task = new Task( &encodeWav,(void*) filenamePtr );
            threadPool.enqueue(task);
        }

        threadPool.waitForThreads();

        cout << "- Encoding completed  " << endl;
        cout.flush();
    }
    else
    {
        throw "->  Error: Directory does not contain .wav files";
    }
}
