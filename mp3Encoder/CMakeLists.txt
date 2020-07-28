cmake_minimum_required(VERSION 3.10.2)

project("mp3_encoder")

add_subdirectory( ../threadPool threadPool )

add_library( mp3_encoder
            src/FileName.cpp
            src/FileNameStore.cpp
            src/Mp3Encoder.cpp
            src/WavFinder.cpp
)

target_include_directories( mp3_encoder
                        PUBLIC 
                            include
                            ${pthreadPool_SOURCE_DIR}
                            ../lib/lame
)


IF (WIN32)
    target_link_libraries( mp3_encoder
                            PRIVATE
                            thread_pool
                            ${mp3_encoder_SOURCE_DIR}/../lib/lame/libmp3lame.a
    )
ELSE()
    target_link_libraries( mp3_encoder
                    PRIVATE
                    thread_pool
                    ${mp3_encoder_SOURCE_DIR}/../lib/lame/libmp3lame_linux.a
)
ENDIF()

