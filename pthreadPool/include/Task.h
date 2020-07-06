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
        Task(void (*funcPtr)(void*), void* arg) : funcPtr( funcPtr ), arg( arg ) {}
        void operator()();
        void run();
    private:
        void( *funcPtr )(void*);
        void* arg;
    };
}
