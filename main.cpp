#include <ctype.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <fstream>

#include <thread>
#include <vector>

#include <algorithm>

#include "FileName.h"
#include "ThreadPool.h"
#include "WavFinder.h"
#include "lame/lame.h"

#define MAX_THREAD_NUMBER 4

using namespace std;
using namespace mp3Encoder;


void encodeWav( string wavFileName, string mp3FileName )
{
    int read, write;

    ifstream wavSource( wavFileName, ios::binary);

    const char* wavFileNameChar= wavFileName.c_str();
    const char* mp3FileNameChar= mp3FileName.c_str();

    FILE *pcm = fopen(wavFileNameChar, "rb");
    FILE *mp3 = fopen(mp3FileNameChar, "wb");

    const int PCM_SIZE = 8192;
    const int MP3_SIZE = 8192;

    short int pcm_buffer[PCM_SIZE*2];
    unsigned char mp3_buffer[MP3_SIZE];

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, 44100);
    lame_set_VBR(lame, vbr_default);

    if (lame_init_params(lame) < 0)
    {
        fclose(mp3);
        fclose(pcm);
    }
    else
    {
        do
        {
            read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
            if (read == 0)
                write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
            else
                write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
            fwrite(mp3_buffer, write, 1, mp3);
        } while (read != 0);

        printf("Encoding succeeded, close files. \n" );
        fclose(mp3);
        fclose(pcm);

        lame_close(lame);
   }
}


int main( int argc, char const *argv[] )
{


    if( argc < 2 )
    {
        printf( "Please set a directory when starting the app  \n" );
        return 0;
    }


    WavFinder wavFinder;
    wavFinder.findWavInDir(static_cast<string>(argv[1]));

    // Create a vector of threads


    cout << "Start to encode " << wavFinder.getAvailableFileNumber() << " files " << endl;

    cout << "Instantiate thread pool with  " << thread::hardware_concurrency() << "threads" <<  endl;
    ThreadPool pool(thread::hardware_concurrency());


    while( wavFinder.getAvailableFileNumber() )
    {
        FileName filename = *wavFinder.getNextWavFilePtr();
        pool.enqueue( encodeWav, filename.getNameWavWithPath(), filename.getNameMp3WithPath()  );
 #ifdef NO_POOL
        std::thread th1( encodeWav, filename.getNameWavWithPath(), filename.getNameMp3WithPath() );

        if (th1.joinable())
        {
            th1.join();
        }
#endif // NO_POOL
    }


    return 0;
}
