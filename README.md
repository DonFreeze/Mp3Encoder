This is a small portable Wav to MP3 encoder project based on C and C++.

The application will search wav files in a given directory, encodes these files to mp3 and stores the data into mp3 files into the same directory.

1. Prerequisite
  This project uses the Lame encoder library. 
  You need to build and link the library to your project.


2. Installation and Usage
 Compile this project using your mingw32 on Windows and GNU compiler on Linux.
  Windows:

    mkdir build
    cd build
    cmake .. -G "MinGW Makefiles"
    mingw32-make

    .\MP3Encoder.exe ..\wavFiles\

  Linux:

3. Project status 
  - Features
    - Search wav files in directory by the use of the dirent library
    - Encode wav to mp3 using lame encoder library with quality level good and 48kHz sample rate
    - Store encoded mp3 data into files with same name as wav files
    - Usage of multithreading with pthread and thread pool.
    - Maximal thread number is limited to number of CPU cores 
    - Minimal thread number depence of the amount of wav files to encode 
    - Portable and automated build using cmake
 
  - Open Points
    - Error/ exception handling is not completed