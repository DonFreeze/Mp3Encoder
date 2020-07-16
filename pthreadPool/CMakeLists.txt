cmake_minimum_required(VERSION 3.10.2)

project("pthread_pool")

add_library ( pthread_pool 
              src/CondVar.cpp
              src/Mutex.cpp
              src/Task.cpp
              src/ThreadPool.cpp
)

target_include_directories( pthread_pool
                          PUBLIC
                              include 
                              )

