/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2020                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  Copyright (c) 2014-2015                                                **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/


#include "config.h"
#include "ThreadPool.h"
#include <functional>

using namespace cube;

#include <iostream>
using namespace std;

cube::ThreadPool::ThreadPool( int threads )
{
    isStopped = false;
    for ( int i = 0; i < threads; ++i )
    {
        threadVector.push_back( new std::thread( &ThreadPool::startWork, this ) );
    }
}

cube::ThreadPool::~ThreadPool()
{
    mutex.lock();
    isStopped = true;
    mutex.unlock();

    condition.notify_all();
    for ( std::thread* worker : threadVector )
    {
        worker->join();
    }
}

void
cube::ThreadPool::startWork()
{
    std::function<void()> task;  // next task to be executed

    while ( !isStopped )
    {
        {   // wait for a task to execute
            std::unique_lock<std::mutex> lock( mutex );
            while ( tasks.empty() && !isStopped )
            {
                this->condition.wait( lock );
            }
            if ( isStopped )
            {
                return;
            }

            task = this->tasks.front();
            this->tasks.pop();
        }
        task();
    }
}

void
cube::ThreadPool::addTask( std::function<void()> func )
{
    std::unique_lock<std::mutex> lock( mutex );
    tasks.push( func );
    condition.notify_one();
}
