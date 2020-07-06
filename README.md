This is a small portable Wav to MP3 encoder project based on C and C++.

The application will search wav files in a given directory, encodes these files to mp3 and stores the data into mp3 files in the same directory.

1. Prerequisite
  This project uses the Lame encoder library. 
  You need to build and link the library to your project.


2. Installation and Usage
  Compile this project using your mingw32 on Windows and GNU compiler on Linux.

  Run the program by giving the an directory as argument:
    Mp3Encoder C:\Users\XXX\Documents\WavFiles

3. Project status 
  - Features
    - Search wav files in directory by the use of the dirent library
    - Encode wav to mp3 using lame encoder library
    - Store mp3 data into files with same name as wav files
    - Usage of multithreading with pthread and thread pool.


  - Open Points
    - Portable and automated build using cmake
    - Error handling is not finished