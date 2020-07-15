cmake_minimum_required(VERSION 3.10.2)

# set the project name
project(MP3Encoder)

# specify C++ Standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(pthreadPool)

# include headers 
include_directories( include
                     lame )

file(GLOB SOURCES "src/*.cpp" )

# add the executable
add_executable(MP3Encoder main.cpp ${SOURCES})

#find_library(LAME_LIB NAMES mp3lame PATHS lame)

# Link static Lame library
if(UNIX)
    set(LAME_LIB "${CMAKE_SOURCE_DIR}/lame/libmp3lame.a")
elseif(MINGW OR WIN32)
	set(LAME_LIB "${CMAKE_SOURCE_DIR}/lame/libmp3lame.lib")
endif(UNIX)

# link util lib to demo executable
target_link_libraries(MP3Encoder ${LAME_LIB})


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

