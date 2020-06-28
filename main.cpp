#include <ctype.h>
#include <stdio.h>
#include <iostream>

#include <string>
#include <fstream>

//#include <vector>
//#include <algorithm>

#include "FileName.h"
#include "WavFinder.h"
#include "lame/lame.h"
#include "pthreadPool/include/ThreadPool.h"


#define Windows
#define POOL

using namespace std;
using namespace mp3Encoder;
using namespace threadpool;

struct argument
{
    string wav;
    string mp3;
};


void encodeWav( void* arg  )
{
    argument *fileNames = (argument*) arg;

    int read, write;

    ifstream wavSource( fileNames->wav, ios::binary);

    const char* wavFileNameChar= fileNames->wav.c_str();
    const char* mp3FileNameChar= fileNames->mp3.c_str();

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
#ifdef _WIN32
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    size_t numCPU = sysinfo.dwNumberOfProcessors;
#endif // _WIN64

#ifdef __linux
    size_t numCPU = sysconf(_SC_NPROCESSORS_ONLN);
#endif // __linux



    if( argc < 2 )
    {
        printf( "Please set a directory when starting the app  \n" );
        return 0;
    }

    WavFinder wavFinder;
    wavFinder.findWavInDir(static_cast<string>(argv[1]));

    cout << "Start to encode " << wavFinder.getAvailableFileNumber() << " files " << endl;
 #ifdef POOL
    cout << "Instantiate thread pool with  " << numCPU << "threads" <<  endl;
    ThreadPool threadPool( numCPU );
#endif // POOL

    while( wavFinder.getAvailableFileNumber() )
    {
        FileName filename = *wavFinder.getNextWavFilePtr();
        argument* argu;
        argu->wav = filename.getNameWavWithPath();
        argu->mp3 = filename.getNameMp3WithPath();

 #ifdef POOL

        Task* task = new Task(&encodeWav,(void*) argu);
        threadPool.enqueue(task);
#else
        sthread th1( encodeWav, filename.getNameWavWithPath(), filename.getNameMp3WithPath() );

        if (th1.joinable())
        {
            th1.join();
        }
#endif // NO
    }

#ifdef POOL
    while( threadPool.isRunning() )
    {
    }
#endif

    return 0;
}
