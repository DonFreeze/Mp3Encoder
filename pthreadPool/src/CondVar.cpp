/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */

#include "../include/CondVar.h"

using namespace threadpool;

CondVar::CondVar()
{
    pthread_cond_init( &condVar, NULL );
}

CondVar::~CondVar()
{
    pthread_cond_destroy( &condVar );
}

void CondVar::wait( pthread_mutex_t* mutex )
{
    pthread_cond_wait( &condVar, mutex );
}

void CondVar::signal()
{
    pthread_cond_signal( &condVar );
}

void CondVar::broadcast()
{
    pthread_cond_broadcast( &condVar );
}
