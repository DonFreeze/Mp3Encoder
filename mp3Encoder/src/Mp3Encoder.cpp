/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 */

#include <iostream>

#include <stdio.h>
#include <string>
#include <sysinfoapi.h>

#include <fstream>

#include <sstream>
#include <future>
#include <functional>
#include <stdexcept>

#include "../include/Mp3Encoder.h"
#include "../include/WavFinder.h"
#include "../../lib/lame/lame.h"
#include "../../pthreadPool/include/ThreadPool.h"

using namespace mp3encoder;
using namespace threadpool;
using namespace std;

bool Mp3Encoder::encodeWav( const string& input )
{
    const size_t IN_SAMPLERATE = 44100; // default sample-rate
    const size_t PCM_SIZE = 8192;
    const size_t MP3_SIZE = 8192;
    const size_t LAME_GOOD = 5;
    int16_t pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];
    const size_t bytes_per_sample = 2 * sizeof(int16_t); // stereo signal, 16 bits
    const string ext = {"mp3"};

    string output(input);
    output.replace(output.end() - ext.length(), output.end(), ext);
    std::ifstream wav;
    std::ofstream mp3;


    try 
    {   
        wav.open( input,  ios::in | ios::binary);
        mp3.open( output,  ios::out | ios::binary);
    }
    catch (std::ifstream::failure e)
    {
        cout << "Error opening input/output file: " << e << '\n';
        return false;
    }

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, IN_SAMPLERATE);
    lame_set_VBR(lame, vbr_default);
    lame_set_VBR_q(lame, LAME_GOOD);

    if (lame_init_params(lame) < 0) 
    {
        wav.close();
        mp3.close();
        return false;
    }

    while ( wav.good() ) 
    {
        int write = 0;
        wav.read(reinterpret_cast<char*>(pcm_buffer), sizeof(pcm_buffer));
        int read = wav.gcount() / bytes_per_sample;
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        else
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);

        mp3.write(reinterpret_cast<char*>(mp3_buffer), write);
    }

    cout << "." ;
    cout.flush();


    wav.close();
    mp3.close();

    lame_close(lame);
    return true;

   
}

void Mp3Encoder::startEncoding( string path )
{
    if( wavFinder.findWavInDir( path ) > 0 )
    {
        ThreadPool threadPool;

        threadPool.pause(true);
        std::vector<std::tuple<int, std::future<bool> > > results;

        int fileNumber = wavFinder.getAvailableFileNumber();
         cout << "- Start to encode " << fileNumber <<  " files: "  ;
        try 
        {
            int i = 0;
            while ( wavFinder.getAvailableFileNumber() )
            {
                FileName filename = *wavFinder.getNextWavFilePtr();
                //  encodeWav( filename.getNameWavWithPath() );
                // threadPool.add( encodeWav, filename );
             results.emplace_back( i,  threadPool.add( encodeWav, filename.getNameWavWithPath() )); 
             ++i;
             threadPool.pause(false);    
            }
        }           
        catch (std::runtime_error &e) {
            cout << e.what();
            exit(1);
        }

        threadPool.wait();

/*
       while( threadPool.waitingJobs() != fileNumber)
        {
            cout << " Waiting jobs: "<< threadPool.waitingJobs()  <<" of " << fileNumber << endl;
        }*/


        cout << std::endl;
        for (auto& res : results)
        {
            cout << get<0>(res) << ": " << get<1>(res).get() << endl;
        }
        cout << std::endl;

        cout << "- Encoding completed  " << endl;
        cout.flush();
    }
    else
    {
        throw "->  Error: Directory does not contain .wav files";
    }
}
