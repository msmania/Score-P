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


#ifndef ThreadPool_H
#define ThreadPool_H

#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>

namespace cube
{
class ThreadPool
{
public:
    /**
     * @brief ThreadPool::ThreadPool
     * @param threads number of threads hat the pool will create
     */
    ThreadPool( int );
    ~ThreadPool();
    int
    size()
    {
        return tasks.size();
    }
    /** appends a task to the queue */
    void
    addTask( std::function<void()> func );

private:
    void
    startWork();

    std::vector< std::thread*>          threadVector;
    std::queue< std::function<void()> > tasks;
    std::mutex                          mutex;
    std::condition_variable             condition;
    bool                                isStopped;
};
}
#endif
