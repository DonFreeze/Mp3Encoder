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

#include "Global.h"

using namespace std;

namespace threadpool
{
    class CondVar
    {

    public:
        CondVar();
        ~CondVar();
        void wait( pthread_mutex_t* mutex );
        void signal();
        void broadcast();

    private:
        pthread_cond_t condVar;
    };
}
