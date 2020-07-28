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
#include <fstream>

#include <sstream>
#include <future>
#include <functional>
#include <stdexcept>

#include "../include/Mp3Encoder.h"
#include "../include/WavFinder.h"
#include "../../lib/lame/lame.h"
#include "../../threadPool/include/ThreadPool.h"

using namespace mp3encoder;
using namespace threadpool;
using namespace std;

bool Mp3Encoder::encodeWav( FileName& fileName )
{
    const size_t IN_SAMPLERATE = 44100;
    const size_t PCM_SIZE = 8192;
    const size_t MP3_SIZE = 8192;
    const size_t LAME_GOOD = 5;
    int16_t pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];
    const size_t bytes_per_sample = 2 * sizeof(int16_t); 

    std::ifstream wav;
    std::ofstream mp3;

    try 
    {   
        wav.open( fileName.getWavWithPath(), ios::in | ios::binary );
        mp3.open( fileName.getMp3WithPath(), ios::out | ios::binary );
    }
    catch( std::ifstream::failure& e )
    {
        cout << "Error opening input/output file: " << e.what()  << endl;
        return false;
    }

    lame_t lame = lame_init();
    lame_set_in_samplerate( lame, IN_SAMPLERATE );
    lame_set_VBR( lame, vbr_default );
    lame_set_VBR_q( lame, LAME_GOOD );

    if( lame_init_params(lame) < 0 ) 
    {
        wav.close();
        mp3.close();
        return false;
    }

    while ( wav.good() ) 
    {
        int write = 0u;
        wav.read( reinterpret_cast<char*>(pcm_buffer), sizeof(pcm_buffer) );
        int read = wav.gcount() / bytes_per_sample;
        if( read == 0u )
        {
            write = lame_encode_flush( lame, mp3_buffer, MP3_SIZE );
        }
        else
        {
            write = lame_encode_buffer_interleaved( lame, pcm_buffer, read, mp3_buffer, MP3_SIZE );
        }
        mp3.write( reinterpret_cast<char*>(mp3_buffer), write );
    }

    cout << "." ;
    cout.flush();

    wav.close();
    mp3.close();

    lame_close(lame);
    return true;
}

void Mp3Encoder::startEncoding( const string path )
{
    try
    {
        wavFinder.findWavInDir( path ) ;
    }
    catch( const exception& e )
    {
        cout << e.what() << endl;
        exit( 1 );
    }

    if( wavFinder.getAvailableFileNumber() > 0u )
    {  
        cout << "- Start to encode " << wavFinder.getAvailableFileNumber() << " files: ";
        ThreadPool threadPool;
        threadPool.pause(true);
        vector<tuple< string, future<bool>>> results;
    
        try 
        {
            while( wavFinder.getAvailableFileNumber() )
            {
                FileName filename = *wavFinder.getNextWavFilePtr();
                results.emplace_back( filename.getWav(), threadPool.add( encodeWav, filename ) ); 
                threadPool.pause( false );    
            }
        }           
        catch( runtime_error &e ) 
        {
            cout << e.what() << endl;
            exit( 1 );
        }

        threadPool.wait();

        for( auto& res : results )
        {
            if( get<1>(res).get() == false )
            {
                cout << "-> Failed to encode file: " << get<0>(res) << endl;
            }            
        }

        cout << endl << "- Encoding completed  " << endl;  
    } 
}
