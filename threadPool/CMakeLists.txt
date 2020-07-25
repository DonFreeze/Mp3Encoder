cmake_minimum_required(VERSION 3.10.2)

project("thread_pool")

add_library ( thread_pool 
              src/ThreadPool.cpp
)

target_include_directories( thread_pool
                          PUBLIC
                              include 
)

