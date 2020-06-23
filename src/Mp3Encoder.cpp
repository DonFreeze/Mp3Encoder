#include <string>

#include "Mp3Encoder.h"
#include <algorithm>

#define MAX_THREAD_NUMBER 4

using namespace std;
using namespace mp3Encoder;
/*
Mp3Encoder::Mp3Encoder()
{
    //ctor
}

Mp3Encoder::~Mp3Encoder()
{
    //dtor
}


void Mp3Encoder::encodeWav( string wavFileName, string mp3FileName )
{

cout << "hello world "<< wavFileName << mp3FileName << endl;
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

        printf("\n Encoding succeeded, close files. \n" );
        fclose(mp3);
        fclose(pcm);

        lame_close(lame);
   }
}

*/
void eraseFromThreadList( std::thread* threadToErase  )
{
    auto iterator = find(threadList.begin(), threadList.end(), threadToErase);

    if (iterator != threadList.end())
    {
        cout << "News: Remove subscriber from observer list" << endl;
        threadList.erase(iterator);
    }
}


/*
void Mp3Encoder::encodeFilesInDirectory( string directory )
{
    wavFinder.findWavInDir(directory);

    // Create a vector of threads


    cout << "Start to encode " << wavFinder.getAvailableFileNumber() << " files " << endl;

    while( wavFinder.getAvailableFileNumber())
    {

        if( threadList.size() < MAX_THREAD_NUMBER )
        {
            FileName filename = *wavFinder.getNextWavFilePtr();
            cout << "threadList.size()  " << threadList.size()  << endl;
            string s1 = filename.getNameWavWithPath();
            string s2 =  filename.getNameMp3WithPath();

           // std::thread th1( &Mp3Encoder::encodeWav, this, s1, s2 );
           // threadList.push_back(std::move(&th1));

        }

        cout << "threadList.size() 2 " << threadList.size()  << endl;
        for (std::thread* th : threadList)
        {

        cout << "threadList.size()  inside " << threadList.size()  << endl;
            // If thread Object is Joinable then Join that thread.
            if (th->joinable())
            {
                eraseFromThreadList( th );
                cout << "Join Thread ID : "<< th->get_id() << endl;
                th->join();
            }
        }

    }

}

*/
