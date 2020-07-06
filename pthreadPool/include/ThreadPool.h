#pragma once

#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <iostream>
#include <vector>
#include <errno.h>
#include <string.h>

/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */
#pragma once

#include "Mutex.h"
#include "Task.h"
#include "CondVar.h"
#include "Global.h"

using namespace std;

namespace threadpool
{
    class ThreadPool
    {
    public:
        ThreadPool( size_t MaxThreads, size_t numTasks);
        ~ThreadPool();
        void enqueue(Task* task);
        void executeThread();
        bool isRunning();

    private:
        int start();
        void stop();

        size_t numThreads;
        Mutex mTaskMutex;
        CondVar mTaskCondVar;
        vector<pthread_t> mThreads;
        deque<Task*> mTasks;
        volatile int mPoolState;
    };

}

