/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  Copyright (c) 2009-2015                                                **
**  German Research School for Simulation Sciences GmbH,                   **
**  Laboratory for Parallel Programming                                    **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



/**
 * \file
 * \brief Provides an interface for simple caching mechanisms in metrics, using three maps
 */

#ifndef CUBELIB_SIMPLE_CACHE_H
#define CUBELIB_SIMPLE_CACHE_H

#include <map>
#include <stdint.h>
#include <limits>
#include <mutex>
#include <condition_variable>

#include "CubeCache.h"
#include "CubeCnode.h"
#include "CubeValue.h"
#include "CubeSysres.h"

namespace cube
{
/**
 * Class "SimpleCache" is a class, which stores all values without any evaluation of probability
 * Drawback: memory footprint is too big. But this simple realization allows to test another functionalities
 */
template<class T>
class SimpleCache :
    public Cache
{
private:
    // how to make cache threadsafe and reentrant:
    // dirty values/raws is a hash for keys, wich are being calculated by some thread
    // once a threads is looking for a value, which is not in cache, but should be (not key == -1)
    // it is about to calculate it.
    // for that it marks it as a "dirty". other threads, if they need this value, get into lock and wait
    // once first thread has calcuated this value, it notifies all via condition_variable value_ready
    // then other threds do wake up and proceed. Then they get a cached value.

    // we track values and rows separately
    // access to the dirty_values and dirty_rows as locked using value_key_calc_mutex and row_key_calc_mutex
    // other mutexes are regulating general access and modification access to the values.
    typedef std::map<const simple_cache_key_t, bool>          dirty_values_map;

    typedef std::map<const simple_cache_key_t, Value*>        cache_map;
    typedef typename std::map<const simple_cache_key_t, char*>row_cache_map;
    typedef typename std::map<const simple_cache_key_t, T>    t_cache_map;

    dirty_values_map dirty_values;
    dirty_values_map dirty_rows;
    cache_map        stn_container;
    cache_map        sum_container;
    t_cache_map      t_stn_container;
    t_cache_map      t_sum_container;
    row_cache_map    row_container;

    std::mutex              access_mutex;
    std::condition_variable value_ready;
    std::mutex              value_key_calc_mutex;
    std::mutex              row_key_calc_mutex;
    std::mutex              value_key_mod_mutex;
    std::mutex              row_key_mod_mutex;

protected:

    cnode_id_t  number_cnodes;
    sysres_id_t number_loc;
    size_t      loc_size;

    CalculationFlavour myf;
    TypeOfMetric       type_of_metric;

    simple_cache_key_t threshold;



    simple_cache_key_t
    get_key( const Cnode*,
             const CalculationFlavour,
             const Sysres*            sysres,
             const CalculationFlavour sf,
             bool                     setting  = false  );

    simple_cache_key_t
    get_key( const Cnode*             c,
             const CalculationFlavour cf,
             bool                     setting  = false  )
    {
        return get_key( c, cf, nullptr, CUBE_CALCULATE_INCLUSIVE, setting );
    }
    simple_cache_key_t
    get_key_for_row( const Cnode*             c,
                     const CalculationFlavour cf,
                     bool                     setting  = false  )
    {
        // misusing  pointer c as sysres pointer, to signalize that we are looking for key for a row
        return get_key( c, cf, ( Sysres* )c, cf, setting );
    }


    void
    empty();


public:

    SimpleCache( cnode_id_t         _n_cnode,
                 sysres_id_t        _n_loc,
                 size_t             _loc_size,
                 CalculationFlavour metric_flavor = CUBE_CALCULATE_EXCLUSIVE,
                 TypeOfMetric       _type_of_metric = CUBE_METRIC_EXCLUSIVE
                 )
        : number_cnodes( _n_cnode ), number_loc( _n_loc ), loc_size( _loc_size ),
        myf( metric_flavor ), type_of_metric( _type_of_metric ), threshold( 0.7 * number_cnodes )
    {
        dirty_values.clear();
        dirty_rows.clear();
    }

    virtual
    ~SimpleCache()
    {
        empty();
    };

    virtual Value*
    getCachedValue( const Cnode*             cnode,
                    const CalculationFlavour cf,
                    const Sysres*            sysres = nullptr,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );                                                                                    // /< Returns Value or nullptr, if not present

    virtual void
    setCachedValue( Value*,
                    const Cnode*             cnode,
                    const CalculationFlavour cf,
                    const Sysres*            sysres = nullptr,
                    const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );


    bool
    testAndGetTCachedValue( T&,
                            const Cnode*             cnode,
                            const CalculationFlavour cf,
                            const Sysres*            sysres = nullptr,
                            const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE
                            );                                                                         // /< Returns Value or nullptr, if not present

    void
    setTCachedValue( T                        value,
                     const Cnode*             cnode,
                     const CalculationFlavour cf,
                     const Sysres*            sysres = nullptr,
                     const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );

    char*
    getCachedRow( const Cnode*             cnode,
                  const CalculationFlavour cf );                                                                                     // /< Returns Value or nullptr, if not present

    void
    setCachedRow( char*                    value,
                  const Cnode*             cnode,
                  const CalculationFlavour cf );

    // /< Stores or not (if not needed) a Value.

    virtual void
    invalidateCachedValue( const Cnode*             cnode,
                           const CalculationFlavour cf,
                           const Sysres*            sysres = nullptr,
                           const CalculationFlavour sf = CUBE_CALCULATE_INCLUSIVE );


    virtual void
    invalidate();
};



template<class T>
bool
SimpleCache<T>::testAndGetTCachedValue( T&                       value,
                                        const Cnode*             cnode,
                                        const CalculationFlavour cf,
                                        const Sysres*            sysres,
                                        const CalculationFlavour sf
                                        )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return false;
    }
    access_mutex.lock();
    if ( sysres )
    {
        typename t_cache_map::const_iterator iter = t_stn_container.find( key );
        if ( iter != t_stn_container.end() )
        {
            value =  iter->second;
            access_mutex.unlock();
            return true;
        }
    }
    else
    {
        typename t_cache_map::const_iterator iter = t_sum_container.find( key );
        if ( iter != t_sum_container.end() )
        {
            value =  iter->second;
            access_mutex.unlock();
            return true;
        }
    }
    access_mutex.unlock();
    return false;
}


template<class T>
void
SimpleCache<T>::setTCachedValue( T                        value,
                                 const Cnode*             cnode,
                                 const CalculationFlavour cf,
                                 const Sysres*            sysres,
                                 const CalculationFlavour sf )
{
    const simple_cache_key_t key = get_key( cnode, cf, sysres, sf, true );
    if ( key < 0 ) // do not cache ...
    {
        return;
    }
    // efficient "add if not yet in map" (S. Meyers, "Efficient STL", Item 24)
    access_mutex.lock();
    if ( sysres )
    {
        typename t_cache_map::const_iterator iter = t_stn_container.lower_bound( key );
        if ( iter == t_stn_container.end() || t_stn_container.key_comp() ( key, iter->first ) )
        {
            t_stn_container.insert( typename t_cache_map::value_type( key, value ) );
        }
    }
    else
    {
        typename t_cache_map::const_iterator iter = t_sum_container.lower_bound( key );
        if ( iter == t_sum_container.end() || t_sum_container.key_comp() ( key, iter->first ) )
        {
            t_sum_container.insert( typename t_cache_map::value_type( key, value ) );
        }
    }

    value_key_calc_mutex.lock();
    dirty_values[ key ] = false;
    value_key_calc_mutex.unlock();
    value_ready.notify_all();
    access_mutex.unlock();
}

template<class T>
void
SimpleCache<T>::empty()
{
    // use Free call from Value to remove items "from memory" -> place them back to pool
    for ( cache_map::iterator iter = stn_container.begin(); iter != stn_container.end(); ++iter )
    {
        delete iter->second;
    }
    for ( cache_map::iterator iter = sum_container.begin(); iter != sum_container.end(); ++iter )
    {
        delete iter->second;
    }
    for ( row_cache_map::iterator iter = row_container.begin(); iter != row_container.end(); ++iter )
    {
        delete[] iter->second;
    }
    sum_container.clear();
    stn_container.clear();
    t_sum_container.clear();
    t_stn_container.clear();
    row_container.clear();
    dirty_values.clear();
    dirty_rows.clear();
}

template<class T>
Value*
SimpleCache<T>::getCachedValue( const Cnode*             cnode,
                                const CalculationFlavour cf,
                                const Sysres*            sysres,
                                const CalculationFlavour sf )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf );
    if ( key < 0 ) // do not cache ...
    {
        return nullptr;
    }

    Value* _value = nullptr;
    if ( sysres )
    {
        cache_map::const_iterator iter = stn_container.find( key );
        if ( iter != stn_container.end() )
        {
            _value = iter->second;
        }
    }
    else
    {
        cache_map::const_iterator iter = sum_container.find( key );
        if ( iter != sum_container.end() )
        {
            _value = iter->second;
        }
    }
    return _value ? _value->copy() : nullptr;     // pretend we do not
}

template<class T>
void
SimpleCache<T>::setCachedValue( Value*                   value,
                                const Cnode*             cnode,
                                const CalculationFlavour cf,
                                const Sysres*            sysres,
                                const CalculationFlavour sf )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf, true );
    if ( key < 0 ) // do not cache ...
    {
        return;
    }
    access_mutex.lock();
    // efficient "add if not yet in map" (S. Meyers, "Efficient STL", Item 24)
    if ( sysres )
    {
        cache_map::iterator iter = stn_container.lower_bound( key );
        if ( iter == stn_container.end() || stn_container.key_comp() ( key, iter->first ) )
        {
            stn_container.insert( cache_map::value_type( key, value->copy() ) );
        }
    }
    else
    {
        cache_map::iterator iter = sum_container.lower_bound( key );
        if ( iter == sum_container.end() || sum_container.key_comp() ( key, iter->first ) )
        {
            sum_container.insert(  cache_map::value_type( key, value->copy() ) );
        }
    }
    value_key_calc_mutex.lock();
    dirty_values[ key ] = false;
    value_key_calc_mutex.unlock();
    value_ready.notify_all();
    access_mutex.unlock();
}


template<class T>
simple_cache_key_t
SimpleCache<T>::get_key( const Cnode*             cnode,
                         const CalculationFlavour cf,
                         const Sysres*            sysres,
                         const CalculationFlavour sf,
                         bool                     setting
                         )
{
#ifndef HAVE_INTERNAL_CACHE
    ( void )cnode;
    ( void )cf;
    ( void )sysres;
    ( void )sf;
    ( void )setting;
    return ( simple_cache_key_t )( -1 );
#else
    simple_cache_key_t key;
    // either it is an aggregated value or a row. Both cases -> cache
    if ( sysres == nullptr
         ||
         (
             (
                 type_of_metric != CUBE_METRIC_SIMPLE
             )
             &&
             ( ( void* )cnode == ( void* )sysres )
             &&
             ( cf != myf  )
         )
         )
    {
        key =  2 * cnode->get_id() + cf;
    }
    else
    {
        if ( cf == myf )
        {
            return ( simple_cache_key_t )( -1 );
        }
        if ( !sysres->isSystemTreeNode() )
        {
            return ( simple_cache_key_t )( -1 );
        }

        simple_cache_key_t Nc;
        if ( myf == CUBE_CALCULATE_EXCLUSIVE )
        {
            Nc = cnode->total_num_children();
        }
        else     // myf == CUBE_CALCULATE_INCLUSIVE
        {
            Nc = cnode->num_children();
        }
        if ( Nc <= threshold )
        {
            return ( simple_cache_key_t )( -1 );
        }
        key = 2 * number_loc * ( 2 * cnode->get_id() + cf ) +  2 * sysres->get_id() + sf;
    }
    if ( ( void* )cnode != ( void* )sysres ) // not row
    {
        if ( !setting )
        {
            std::unique_lock<std::mutex>     lock_( value_key_calc_mutex );
            dirty_values_map::const_iterator iter = dirty_values.find( key );

            if ( iter == dirty_values.end() )
            {
                dirty_values[ key ] = true;
                lock_.unlock();
                return key;
            }
            while ( true )
            {
                if ( !dirty_values[ key ] )
                {
                    lock_.unlock();
                    break;
                }
                // loop to avoid spurious wakeups
                value_ready.wait( lock_ );
            }
        }
    }
    else     // row call
    {
        if ( !setting )
        {
            std::unique_lock<std::mutex>     lock_( row_key_calc_mutex );
            dirty_values_map::const_iterator iter = dirty_rows.find( key );
            if ( iter == dirty_rows.end() )
            {
                dirty_rows[ key ] = true;
                lock_.unlock();
                return key;
            }
            while ( true )
            {
                if ( !dirty_rows[ key ] )
                {
                    lock_.unlock();
                    break;
                }
                // loop to avoid spurious wakeups
                value_ready.wait( lock_ );
            }
        }
    }
    return key;
#endif
}


template<class T>
void
SimpleCache<T>::invalidateCachedValue( const Cnode*             cnode,
                                       const CalculationFlavour cf,
                                       const Sysres*            sysres,
                                       const CalculationFlavour sf )
{
    simple_cache_key_t key = get_key( cnode, cf, sysres, sf, true );

    access_mutex.lock();
    cache_map::iterator iter = stn_container.find( key );
    if ( iter != stn_container.end() )
    {
        delete iter->second;
    }
    iter = sum_container.find( key );
    if ( iter != sum_container.end() )
    {
        delete iter->second;
    }
    row_cache_map::iterator r_iter = row_container.find( key );
    if ( r_iter != row_container.end() )
    {
        delete[] r_iter->second;
    }
    sum_container.erase( key );
    stn_container.erase( key );
    t_sum_container.erase( key );
    t_stn_container.erase( key );
    row_container.erase( key );
    access_mutex.unlock();
    value_key_mod_mutex.lock();
    dirty_values.erase( key );
    value_key_mod_mutex.unlock();
    row_key_mod_mutex.lock();
    dirty_rows.erase( key );
    row_key_mod_mutex.unlock();
}


template<class T>
char*
SimpleCache<T>::getCachedRow( const Cnode*             cnode,
                              const CalculationFlavour cf )
{
    simple_cache_key_t key = get_key_for_row( cnode, cf );
    if ( key < 0 ) // do not cache ...
    {
        return nullptr;
    }

    char*                         _value = nullptr;
    row_cache_map::const_iterator iter   = row_container.find( key );
    if ( iter != row_container.end() )
    {
        _value = new char[ number_loc * loc_size ];
        memcpy( _value, iter->second, number_loc * loc_size  );
    }
    return _value;
}



template<class T>
void
SimpleCache<T>::setCachedRow( char*                    value,
                              const Cnode*             cnode,
                              const CalculationFlavour cf )
{
    simple_cache_key_t key = get_key_for_row( cnode, cf, true );
    if ( key < 0 ) // do not cache ...
    {
        return;
    }
    access_mutex.lock();
    // efficient "add if not yet in map" (S. Meyers, "Efficient STL", Item 24)
    row_cache_map::iterator iter = row_container.lower_bound( key );
    if ( iter == row_container.end() || row_container.key_comp() ( key, iter->first ) )
    {
        char* _tmp =  new char[ number_loc * loc_size ];
        memcpy( _tmp, value, number_loc * loc_size  );
        row_container.insert( row_cache_map::value_type( key, _tmp ) );
    }
    row_key_calc_mutex.lock();
    dirty_rows[ key ] =  false;
    row_key_calc_mutex.unlock();
    value_ready.notify_all();
    access_mutex.unlock();
}


template<class T>
void
SimpleCache<T>::invalidate()
{
    empty();
}
}

#endif
