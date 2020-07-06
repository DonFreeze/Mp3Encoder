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

#include <pthread.h>
#include <unistd.h>
#include <deque>
#include <iostream>
#include <vector>
#include <errno.h>
#include <string.h>

#include "Global.h"

using namespace std;

namespace threadpool
{
    class Mutex
    {
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
        pthread_mutex_t* get_mutex_ptr();

    private:
        pthread_mutex_t m_lock;
        volatile bool is_locked;
    };
}
