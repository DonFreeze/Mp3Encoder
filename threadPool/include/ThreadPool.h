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
#pragma once

#include <atomic>
#include <mutex>
#include <thread>
#include <future>
#include <vector>
#include <functional>
#include <condition_variable>
#include <queue>

namespace threadpool
{
    class ThreadPool
    {
    public:
        using Ids = std::vector<std::thread::id>;

        ThreadPool( std::size_t threadCount = 0 );
        ~ThreadPool();

        template<typename Func, typename... Args>
        auto add( Func&& func, Args&&... args )->std::future<typename std::result_of<Func(Args...)>::type>;

        std::size_t threadCount() const;
        std::size_t waitingJobs() const;
        Ids ids() const;
        void clear();
        void pause( bool state );
        void wait();

    private:
        using Job = std::function<void()>;   
        static void threadTask( ThreadPool* pool );

        std::queue<Job> jobs;
        mutable std::mutex jobsMutex;
        std::condition_variable jobsAvailable;
        std::vector<std::thread> threads;
        std::atomic<std::size_t> threadsWaiting;
        std::atomic<bool> terminate;
        std::atomic<bool> paused;
    };

    template<typename Func, typename... Args>
    auto ThreadPool::add(Func&& func, Args&&... args) -> std::future<typename std::result_of<Func(Args...)>::type>
    {
        using PackedTask = std::packaged_task<typename std::result_of<Func(Args...)>::type()>;

        auto task = std::make_shared<PackedTask>(std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
        auto ret = task->get_future();

        {
            std::lock_guard<std::mutex> lock{ jobsMutex };
            jobs.emplace([task]() { (*task)(); });
        }

        jobsAvailable.notify_one();

        return ret;
    }
}

