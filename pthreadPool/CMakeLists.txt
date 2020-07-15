cmake_minimum_required(VERSION 3.10.2)

# set the project name
project(MP3Encoder)

target_sources(MP3Encoder
    PRIVATE
        src/CondVar.cpp
        src/Mutex.cpp
        src/Task.h
        src/ThreadPool.cpp
        include/CondVar.cpp
        include/Mutex.cpp
        include/Task.h
    PUBLIC
        include/ThreadPool.cpp
)