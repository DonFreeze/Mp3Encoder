#include <string>

#include "Mp3Encoder.h"

#define multithread

using namespace std;
using namespace mp3Encoder;

Mp3Encoder::Mp3Encoder()
{
    //ctor
}

Mp3Encoder::~Mp3Encoder()
{
    //dtor
}

void Mp3Encoder::encodeFilesInDirectory( string directory )
{
    wavFinder.findWavInDir(directory);

      // Create a vector of threads
    std::vector<std::thread> vecOfThreads;

    cout << "Start to encode " << wavFinder.getAvailableFileNumber() << " files " << endl;

    for( int i = 0; i < wavFinder.getAvailableFileNumber(); i++)
    {
#ifdef multithread
         FileName filename = wavFinder.getNextWavFile();

         std::thread th1( this->encodeWav, filename, this );
        vecOfThreads.push_back(std::move(th1));
#else
        encodeWav( wavFinder.getNextWavFile());
#endif
    }
#ifdef multithread
   for (std::thread & th : vecOfThreads)
    {
        // If thread Object is Joinable then Join that thread.
        if (th.joinable())
        {
            cout << "Join Thread ID : "<< th.get_id() << endl;
            th.join();

        }
    }
#endif

}



void Mp3Encoder::encodeWav( FileName& fileName )
{
    cout << "From Thread ID: "<< this_thread::get_id() << " encode wav " << fileName.getNameWav() << endl;
    int read, write;


    ifstream wavSource(fileName.getNameWavWithPath(), ios::binary);

    const char* wavFileNameChar= fileName.getNameWavWithPath().c_str();
    const char* mp3FileNameChar= fileName.getNameMp3WithPath().c_str();

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

        printf("\n Encoding succeeded, close files. \n" );
        fclose(mp3);
        fclose(pcm);

        lame_close(lame);
   }
}

