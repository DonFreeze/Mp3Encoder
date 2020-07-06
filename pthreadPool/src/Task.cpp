/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */

#include "Task.h"

using namespace threadpool;

void Task::operator()()
{
    (*funcPtr)(arg);

    if ( arg != NULL )
    {
        delete arg;
    }
}

void Task::run()
{
    (*funcPtr)(arg);
}
