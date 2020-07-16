/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */

#include "../include/Mutex.h"

using namespace threadpool;

Mutex::Mutex()
{
    pthread_mutex_init( &ptMutex, NULL );
    isLocked = false;
}

Mutex::~Mutex()
{
    while( isLocked );
    unlock(); // Unlock Mutex after shared resource is safe
    pthread_mutex_destroy(&ptMutex);
}

void Mutex::lock()
{
    pthread_mutex_lock(&ptMutex);
    isLocked = true;
}

void Mutex::unlock()
{
    isLocked = false; // do it BEFORE unlocking to avoid race condition
    pthread_mutex_unlock( &ptMutex );
}

pthread_mutex_t* Mutex::getMutexPtr()
{
    return &ptMutex;
}
