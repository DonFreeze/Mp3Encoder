cmake_minimum_required(Version 3.0)

project(Mp3Encoder)


# Variable for the folder folder names 
set(THREAD_POOL_DIR pthreadPool)
set(HELPER_DIR src/)

add_executable(
    Mp3Encoder
    main.cpp 
    HELPER_DIR/FileName.cpp 
    HELPER_DIR/FileNameStore.cpp 
    HELPER_DIR/Mp3Encoder.cpp
    HELPER_DIR/WavFinder.cpp
    
    
    )





#add_subdirectory(lame/libmp3lame.a)

#target_link_libraries(Mp3Encodder libmp3lame.a  )