
#include <iostream>
#include "Mp3Encoder.h"

#define multithread
#define linux

using namespace std;
using namespace mp3Encoder;



int main( int argc, char const *argv[] )
{


    if( argc < 2 )
    {
        printf( "Please set a directory when starting the app  \n" );
        return 0;
    }

    Mp3Encoder mp3Encoder;

    mp3Encoder.encodeFilesInDirectory( static_cast<string>(argv[1]) );


    return 0;

  /*
    int numCPU = thread::hardware_concurrency();

    WavFinder wavFinder(*fileStore);

    wavFinder.findWavInDir(static_cast<string>(argv[1]));

    // Create a vector of threads
    std::vector<std::thread> vecOfThreads;

    cout << "Start to encode " << wavFinder.getAvailableFileNumber() << " files " << endl;

    for( int i = 0; i < wavFinder.getAvailableFileNumber(); i++)
    {
#ifdef multithread
         FileName filename = wavFinder.getNextWavFile();

         std::thread th1( encodeWav, filename.);
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
    end = clock();
*/
}
