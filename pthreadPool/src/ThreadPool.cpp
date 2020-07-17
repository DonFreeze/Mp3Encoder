/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */

#include "../include/ThreadPool.h"
#include <iostream>

using namespace std;
using namespace threadpool;

ThreadPool::ThreadPool( size_t MaxThreads,  size_t numTasks )
{

    numThreads = MaxThreads > numTasks ? numTasks : MaxThreads;
    cout << "- Create ThreadPool of size " << numThreads << endl;
    try
    {
      start();
    }
    catch( std::exception e )
    {
        std::cout << e.what() << "\n";
    }

}

ThreadPool::~ThreadPool()
{
    stop();
}


extern "C"
void* start_thread( void* arg )
{
    ThreadPool* threadPool = (ThreadPool*) arg;
    threadPool->executeThread();
    return NULL;
}

int ThreadPool::start()
{
    PoolState = STARTED;
    ThreadPool::finished = 0;
    int ret = -1;
    for (auto i = 0u; i < numThreads; ++i)
    {
        pthread_t tid;
        ret = pthread_create(&tid, NULL, start_thread, (void*) this);
        if (ret != 0)
        {
            cerr << "pthread_create() failed: " << ret << endl;
            return -1;
        }
        Threads.push_back(tid);
    }

    return 0;
}

void ThreadPool::stop()
{
    TaskMutex.lock();
    PoolState = STOPPED;
    TaskMutex.unlock();

    TaskCondVar.broadcast();

    for( pthread_t thread : Threads )
    {
        void* result;
        pthread_join(thread, &result);
        TaskCondVar.broadcast();
    }
}

void ThreadPool::waitForThreads()
{
    while( true )
    {
        if ( finished == Threads.size() )
        {
            cout << endl <<"- All threads have finished their work" << endl;
            cout.flush();
            break;
        }
    }
}


void ThreadPool::executeThread()
{
    Task* task = NULL;
    bool alternate = false;

    while( true )
    {
        TaskMutex.lock();
        while( ( PoolState != STOPPED ) && ( Tasks.empty() ) )
        {
            if( !alternate )
            {
                alternate = true;
                ++finished;
            }
            TaskCondVar.wait( TaskMutex.getMutexPtr() );
        }

        if( PoolState == STOPPED )
        {
            TaskMutex.unlock();
            pthread_exit(NULL);
        }

        if( alternate )
        {
            alternate = false;
            --finished;
        }

        task = Tasks.front();
        Tasks.pop_front();
        TaskMutex.unlock();

        (*task)();

        delete task;
    }

}

void ThreadPool::enqueue( Task* task )
{
  TaskMutex.lock();

  Tasks.push_back( task );
  TaskCondVar.signal();

  TaskMutex.unlock();
}
