/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */

#include "Mutex.h"

using namespace threadpool;

Mutex::Mutex()
{
    pthread_mutex_init(&m_lock, NULL);
    is_locked = false;
}

Mutex::~Mutex()
{
    while(is_locked);
    unlock(); // Unlock Mutex after shared resource is safe
    pthread_mutex_destroy(&m_lock);
}

void Mutex::lock()
{
    pthread_mutex_lock(&m_lock);
    is_locked = true;
}

void Mutex::unlock()
{
    is_locked = false; // do it BEFORE unlocking to avoid race condition
    pthread_mutex_unlock(&m_lock);
}

pthread_mutex_t* Mutex::get_mutex_ptr()
{
    return &m_lock;
}
