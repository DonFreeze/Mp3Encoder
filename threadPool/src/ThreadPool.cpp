/*
 *  origin: https://github.com/dabbertorres/ThreadPool/blob/master/LICENSE
 *  Copyright (c) 2015 Alec Iverson
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 * 
 * 
 */

#include "../include/ThreadPool.h"

#include <iterator>
#include <algorithm>

using namespace threadpool;
using namespace std;

ThreadPool::ThreadPool( size_t threadCount )
    : threadsWaiting(0u),
    terminate(false),
    paused(false)
{
    if( threadCount == 0u )
    {
        threadCount = thread::hardware_concurrency();
    }

    threads.reserve( threadCount );
    generate_n( back_inserter( threads ), threadCount, [this]() { return thread{ threadTask, this }; } );
}

ThreadPool::~ThreadPool()
{
    clear();
    terminate = true;
    jobsAvailable.notify_all();

    for (auto& t : threads)
    {
        if (t.joinable())
            t.join();
    }
}

size_t ThreadPool::threadCount() const
{
    return threads.size();
}

size_t ThreadPool::waitingJobs() const
{
    lock_guard<std::mutex> jobLock(jobsMutex);
    return jobs.size();
}

ThreadPool::Ids ThreadPool::ids() const
{
    Ids ret( threads.size() );

    transform( threads.begin(), threads.end(), ret.begin(), [](auto& t) { return t.get_id(); } );

    return ret;
}

void ThreadPool::clear()
{
    lock_guard<mutex> lock{ jobsMutex };

    while( !jobs.empty() )
    {
        jobs.pop();
    }
}

void ThreadPool::pause( bool state )
{
    paused = state;

    if( !paused )
    {
        jobsAvailable.notify_all();
    }
}

void ThreadPool::wait()
{
    while( threadsWaiting != threads.size() ) {}
}

void ThreadPool::threadTask( ThreadPool* pool )
{
    while( true )
    {
        if( pool->terminate )
        {
            break; 
        }

        unique_lock<mutex> jobsLock{ pool->jobsMutex };

        if( pool->jobs.empty() || pool->paused )
        {
            ++pool->threadsWaiting;
            pool->jobsAvailable.wait(jobsLock, [&]()
            {
                return pool->terminate || !( pool->jobs.empty() || pool->paused );
            });
            --pool->threadsWaiting;
        }

        if( pool->terminate )
        {
            break;
        }

        auto job = move( pool->jobs.front() );
        pool->jobs.pop();

        jobsLock.unlock();

        job();
    }
}
