This is a small portable Wav to MP3 encoder project based on C++.

The application will search for wav files in a given directory, encodes these files to mp3 and stores the data into mp3 files into the same directory.

1. Prerequisite

  - This project uses the Lame encoder library. You need to build the library and replace the lame library file in the lib folder.
  - Also this project requires C++11 or higher.

2. Installation and Usage

  - Windows:
    Compile this project using your MinGW compiler version i686-w64-mingw32.

      mkdir build
      cd build
      cmake .. -G "MinGW Makefiles"
      mingw32-make

      .\MP3Encoder.exe ..\PathToWavFiles\wavFileFolder

  - Linux:
    GNU compiler on Linux.

      mkdir build
      cd build
      cmake .. 
      make

3. Project status 
  - Features
    - Search wav files in directory by the use of the dirent library
    - Encode wav to mp3 using lame encoder library with quality level good and 41kHz sample rate
    - Store encoded mp3 data into files with same name as wav files.
    - Multithreading done with C++ std thread by utilizing a thread pool.
    - Maximal thread number is limited to number of CPU cores 
    - Portable and automated build using cmake

    - Open points
      - 

 