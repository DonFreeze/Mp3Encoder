/*
 *	Copyright (c) 2020 Lukas Becker
 *
 *  This file is subject to the terms and conditions defined in
 *  file 'LICENSE.txt', which is part of this source code package.
 *
 *  origin: https://github.com/bilash/threadpool
 *
 */

#include "CondVar.h"

using namespace threadpool;

CondVar::CondVar()
{
    pthread_cond_init(&m_cond_var, NULL);
}

CondVar::~CondVar()
{
    pthread_cond_destroy(&m_cond_var);
}

void CondVar::wait(pthread_mutex_t* mutex)
{
    pthread_cond_wait(&m_cond_var, mutex);
}

void CondVar::signal()
{
    pthread_cond_signal(&m_cond_var);
}

void CondVar::broadcast()
{
    pthread_cond_broadcast(&m_cond_var);
}
