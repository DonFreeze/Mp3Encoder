cmake_minimum_required(VERSION 3.10.2)

# set the project name
project( MP3Encoder )

# specify C++ Standard
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 --std=c++14 -Wall " )
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package (Threads REQUIRED)

add_subdirectory( mp3Encoder mp3Encoder )

# add the executable
add_executable( ${PROJECT_NAME} main.cpp )

# link util lib to executable

target_include_directories(  ${PROJECT_NAME}
                              PUBLIC 
                              ${mp3_encoder_SOURCE_DIR}
)

target_link_libraries( ${PROJECT_NAME}
                        mp3_encoder
                        Threads::Threads
)
