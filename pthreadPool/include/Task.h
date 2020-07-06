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
    class Task
    {
    public:
        Task( void (*funcPtr)(void*), void* arg ) : funcPtr( funcPtr ), arg( arg ) {}
        void operator()();
        void run();
    private:
        void (*funcPtr)(void*);
        void* arg;
    };
}
