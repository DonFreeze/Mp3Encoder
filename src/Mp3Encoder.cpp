#include "Mp3Encoder.h"

#include <string>
#include <fstream>

#include "WavFinder.h"

using namespace mp3encoder;


Mp3Encoder::Mp3Encoder()
{

}

Mp3Encoder::~Mp3Encoder()
{
    //dtor
}



void Mp3Encoder::encodeWav( void* arg )
{
    Argument *fileNames = ( Argument* ) arg;

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
            if( read == 0 )
                write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
            else
                write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
            fwrite(mp3_buffer, write, 1, mp3);
        } while ( read != 0 );
        cout << "." ;

        fclose(mp3);
        fclose(pcm);

        lame_close(lame);
   }
}

void Mp3Encoder::startEncoding( string path, size_t numCPU )
{
    try
    {
        if( wavFinder.findWavInDir( path ) > 0 )
        {

            ThreadPool threadPool( numCPU, wavFinder.getAvailableFileNumber() );
            cout << "- Start to encode files:  ";
            int i = 0;
            while( wavFinder.getAvailableFileNumber() )
            {
                FileName filename = *wavFinder.getNextWavFilePtr();
                Argument* argument = new Argument();
                argument->wav = filename.getNameWavWithPath();
                argument->mp3 = filename.getNameMp3WithPath();
                Task* task = new Task(&encodeWav,(void*) argument);

                threadPool.enqueue(task);
                ++i;
            }
            while( threadPool.isRunning() ){}

        }
    }
    catch( exception& )
    {
        cout << "Could not create wavFinder Instance" << endl;
    }
    cout << endl << "- Encoding completed  " << endl;

}
