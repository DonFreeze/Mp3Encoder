cmake_minimum_required(VERSION 3.10.2)

# set the project name
project( MP3Encoder )

# specify C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory( mp3Encoder mp3Encoder )


# add the executable
add_executable( ${PROJECT_NAME} main.cpp )

# link util lib to demo executable

target_include_directories(  ${PROJECT_NAME}
                              PUBLIC 
                              ${mp3_encoder_SOURCE_DIR}
)

target_link_libraries( ${PROJECT_NAME}
                        mp3_encoder
)

# cmake .. -G "MinGW Makefiles"
# mingw32-make.exe

# Link static Lame library
#if (WIN32)
#    set(LAME_LIB "${CMAKE_SOURCE_DIR}/lame/libmp3lame.lib")
#endif (WIN32)
#if (MINGW)
#    set(LAME_LIB "${CMAKE_SOURCE_DIR}/lame/libmp3lame.lib")
#endif (MINGW)
#if (UNIX)
#    set(LAME_LIB "${CMAKE_SOURCE_DIR}/lame/libmp3lame.a")
#endif (UNIX)

