/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 2016-2022                                                **
**  Forschungszentrum Juelich GmbH, Juelich Supercomputing Centre          **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



#include "config.h"

#include <vector>
#include <iostream>
#include <sstream>
#include <float.h>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <string>
#include <algorithm>

#include "CubePL2LocalMemoryManager.h"
#include "CubeError.h"


using namespace std;
using namespace cube;


CubePL2LocalMemoryManager::CubePL2LocalMemoryManager()
{
    init();
};

CubePL2LocalMemoryManager::~CubePL2LocalMemoryManager()
{
//     cout << " Statistic on CubePL:" << endl;
//     cout << " Max size of used memory : " << memory.size() << endl;
//     cout << " Max size of used global memory : " << global_memory.size() << endl;
    clear_memory();
};



void
CubePL2LocalMemoryManager::clear_memory()
{
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    for ( std::vector< std::vector<CubePL2MemoryDuplet> >::iterator it = _memory.begin(); it != _memory.end(); ++it )
    {
        std::vector<CubePL2MemoryDuplet> _vec = *it;
        for ( std::vector<CubePL2MemoryDuplet>::iterator it1 = _vec.begin(); it1 != _vec.end(); ++it1 )
        {
            if ( ( *it1 ).row_value != NULL )
            {
                delete[] ( *it1 ).row_value;
                ( *it1 ).row_value = NULL;
            }
        }
        _vec.clear();
    }

    _memory.clear();
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    while ( !_memory_stack.empty() )
    {
        _memory_stack.pop();
    }
    _memory_stack.push( 0 );
}


void
CubePL2LocalMemoryManager::init()
{
    clear_memory();
//     registered_variables.clear();
//     registered_variables[ "calculation::metric::id" ]   = cubepl2::CALCULATION_METRIC_ID;
//     registered_variables[ "calculation::callpath::id" ] = cubepl2::CALCULATION_CALLPATH_ID;
//     registered_variables[ "calculation::region::id" ]   = cubepl2::CALCULATION_REGION_ID;
//     registered_variables[ "calculation::sysres::id" ]   = cubepl2::CALCULATION_SYSRES_ID;
//     registered_variables[ "calculation::sysres::kind" ] = cubepl2::CALCULATION_SYSRES_KIND;
//     page_size                                           = 5;
};


void
CubePL2LocalMemoryManager::set_page_size( uint32_t _page_size )
{
    page_size = _page_size;
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    _memory.resize( _memory_stack.top() + page_size );
};


void
CubePL2LocalMemoryManager::new_page()
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( page_size == 0 )
    {
        return;
    }
    if ( _memory_stack.top() > _memory.size() )
    {
        throw CubePLMemoryLayoutError( "Memory stack point out of memory range" );
    }
    if ( _memory.size() - _memory_stack.top() < 2 * page_size )
    {
        _memory.resize( 10 * page_size + _memory_stack.top() ); // Extend the memory for double page. Complete current and allocate new one
    }
    _memory_stack.push( _memory_stack.top() + page_size );      // move page pointer to another page;
};

void
CubePL2LocalMemoryManager::throw_page()
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();

    for ( size_t adress = 0; adress < page_size; ++adress )
    {
        _memory[ _memory_stack.top() +  adress ].clear();
    }
    if ( _memory_stack.size() > 1 )
    {
        _memory_stack.pop();
    }
    else
    {
        _memory.clear();
        _memory.resize( page_size );
    }
}




void
CubePL2LocalMemoryManager::clear_variable( MemoryAdress adress )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    for ( std::vector<CubePL2MemoryDuplet>::iterator it1 = _memory[ _memory_stack.top() +  adress ].begin(); it1 != _memory[ _memory_stack.top() +  adress ].end(); ++it1 )
    {
        delete[] ( *it1 ).row_value;
        ( *it1 ).row_value = NULL;
    }
    _memory[ _memory_stack.top() +  adress ].clear();
}

void
CubePL2LocalMemoryManager::put( MemoryAdress adress,
                                double       index,
                                double       value )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t _index = ( size_t )index;
    if ( _memory_stack.top() +  adress <= _memory.size() )
    {
        if (  _memory[ _memory_stack.top() +  adress ].size() <= _index )
        {
            _memory[ _memory_stack.top() +  adress ].resize( _index + 20 );
        }
    }
    _memory[ _memory_stack.top() +  adress ][ _index ].double_value = value;
    delete[] _memory[ _memory_stack.top() +  adress ][ _index ].row_value;
    _memory[ _memory_stack.top() +  adress ][ _index ].row_value = NULL;
    _memory[ _memory_stack.top() +  adress ][ _index ].state     = CUBEPL_VALUE_DOUBLE;
};


void
CubePL2LocalMemoryManager::put( MemoryAdress adress,
                                double       index,
                                string       value )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t _index = ( size_t )index;
    if (  _memory[ _memory_stack.top() +  adress ].size() <= _index )
    {
        _memory[ _memory_stack.top() +  adress ].resize( _index + 20 );
    }
    _memory[ _memory_stack.top() +  adress ][ _index ].state        = CUBEPL_VALUE_STRING;
    _memory[ _memory_stack.top() +  adress ][ _index ].string_value = value;
};

void
CubePL2LocalMemoryManager::put( MemoryAdress adress,
                                double       index,
                                double*      value
                                )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t       _index = ( size_t )index;
    MemoryAdress _top   = _memory_stack.top();

    if (  _memory[ _top +  adress ].size() <= _index )
    {
        _memory[ _top +  adress ].resize( _index + 20 );
    }
    _memory[ _top +  adress ][ _index ].state = CUBEPL_VALUE_ROW;
    delete[] _memory[ _top +  adress ][ _index ].row_value;
    _memory[ _top +  adress ][ _index ].row_value = value;
}




void
CubePL2LocalMemoryManager::push_back( MemoryAdress adress,
                                      double       value )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    CubePL2MemoryDuplet _t;
    _t.double_value = value;
    _t.state        = CUBEPL_VALUE_DOUBLE;

    _memory[ _memory_stack.top() +  adress ].push_back( _t );
}

void
CubePL2LocalMemoryManager::push_back( MemoryAdress adress,
                                      string       value )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    CubePL2MemoryDuplet _t;
    _t.string_value = value;
    _t.state        = CUBEPL_VALUE_STRING;
    _memory[ _memory_stack.top() +  adress ].push_back( _t );
}

double
CubePL2LocalMemoryManager::get( MemoryAdress adress,
                                double       index )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t _index = ( size_t )index;
    if ( _memory[ _memory_stack.top() +  adress ].size() <= _index )
    {
        return 0.;
    }
    CubePL2MemoryDuplet& _t =  _memory[ _memory_stack.top() +  adress ][ _index ];
    if ( _t.state == CUBEPL_VALUE_STRING )     // convert to double if possible
    {
        std::istringstream stream( _t.string_value );
        double             t;
        stream >> t;
        _t.double_value = t;
        _t.state        = CUBEPL_VALUE_EQUAL;
    }
    return _t.double_value;
}

string
CubePL2LocalMemoryManager::get_as_string( MemoryAdress adress,
                                          double       index )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t _index = ( size_t )index;
    if ( _memory[ _memory_stack.top() +  adress ].size() <= _index )
    {
        return "";
    }
    CubePL2MemoryDuplet& _t =  _memory[ _memory_stack.top() +  adress ][ _index ];
    if ( _t.state == CUBEPL_VALUE_DOUBLE )     // convert to string if possible
    {
        stringstream sstr;
        sstr <<  setprecision( 14 ) <<  _t.double_value;
        sstr >> _t.string_value;
        _t.state = CUBEPL_VALUE_EQUAL;
    }
    return _t.string_value;
}

double*
CubePL2LocalMemoryManager::get_row( MemoryAdress adress,
                                    double       index )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t _index = ( size_t )index;
    if ( _memory[ _memory_stack.top() +  adress ].size() <= _index )
    {
        return new double[ row_size ]();
    }
    CubePL2MemoryDuplet& _t =  _memory[ _memory_stack.top() +  adress ][ _index ];
    if ( _t.state != CUBEPL_VALUE_ROW && _t.row_value == NULL )     // convert to double if possible
    {
        double  value = get( adress, index );
        double* _row  = new double[ row_size ];
        std::fill_n( _row, row_size, value );
        _t.row_value = _row;
        _t.state     = CUBEPL_VALUE_ROW;
    }
    return _t.row_value;
}





size_t
CubePL2LocalMemoryManager::size_of( MemoryAdress adress )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    return _memory[ _memory_stack.top() +  adress ].size();
}

CubePL2StateOfCubePLVariable
CubePL2LocalMemoryManager::type( MemoryAdress adress,
                                 double       index )
{
    memory_mutex.lock();
    std::stack< size_t >& _memory_stack = memory_stack[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    if ( _memory_stack.empty() )
    {
        _memory_stack.push( 0 );
    }
    memory_mutex.lock();
    std::vector< std::vector<CubePL2MemoryDuplet> >& _memory = memory[ std::this_thread::get_id() ];
    memory_mutex.unlock();
    size_t _index = ( size_t )index;
    if ( _memory[ _memory_stack.top() +  adress ].size() <= _index )
    {
        return CUBEPL_VALUE_DOUBLE;
    }
    CubePL2MemoryDuplet& _t =  _memory[ _memory_stack.top() +  adress ][ _index ];
    return _t.state;
}
