/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2021                                                **
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
 *
 * \file CubeSignedShortValue.h
 * \brief   Provides the "signed short" (16bit) build-in type as "Value"
 ************************************************/
#ifndef CUBELIB_SIGNED_SHORT_VALUE_H
#define CUBELIB_SIGNED_SHORT_VALUE_H

#include <istream>
#include "CubeValue.h"

#include <iostream>

namespace cube
{
class Connection;

/**
 * Value works with 2 bytes of the signed sort as teh whole int value, and as 2 bytes (endianess). Therefore it
 * defined a union.
 */
typedef union
{
    int16_t isValue;
    char    aValue[ sizeof( int16_t ) ];
} is_value_t;

class SignedShortValue : public Value
{
protected:
    is_value_t value;                        // / "heart" of the value.
public:
    SignedShortValue();
    SignedShortValue( int16_t );

    virtual
    ~SignedShortValue()
    {
    };

    inline
    virtual unsigned
    getSize() const
    {
        return sizeof( int16_t );
    }

    inline
    virtual double
    getDouble() const
    {
        return ( double )value.isValue;
    };
    virtual uint16_t
    getUnsignedShort() const;
    virtual int16_t
    getSignedShort() const;
    virtual uint32_t
    getUnsignedInt() const;
    virtual int32_t
    getSignedInt() const;
    virtual uint64_t
    getUnsignedLong() const;
    virtual int64_t
    getSignedLong() const;
    virtual char
    getChar() const;
    virtual std::string
    getString() const;

    virtual const char*
    fromStream( const char* );
    virtual const double*
    fromStreamOfDoubles( const double* stream );
    virtual char*
    toStream( char* ) const;

    /**
     * Assign value from a Cube connection.
     * @param connection Cube connection stream.
     */
    virtual void
    fromStream( Connection& connection );

    /**
     * Send value through a Cube connection.
     * @param connection Cube connection stream.
     */
    virtual void
    toStream( Connection& connection ) const;

    inline
    virtual Value*
    clone() const
    {
        return new SignedShortValue( 0 );
    }
    inline
    virtual Value*
    copy() const
    {
        return new SignedShortValue( value.isValue );
    }

    inline
    virtual void
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.isValue += ( ( SignedShortValue* )chval )->value.isValue;
    }

    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        value.isValue -= ( ( SignedShortValue* )chval )->value.isValue;
    }

    inline
    virtual void
    operator*=( double dval )
    {
        value.isValue *= dval;
    }                                 // needed by algebra tools

    inline
    virtual void
    operator/=( double dval )
    {
        if ( dval == 0. )
        {
            std::cerr << "ERROR: DEVISION BY ZERO!" << std::endl;
        }
        value.isValue /= dval;
    }

    virtual void
    operator=( double );

    virtual void
    operator=( Value* );


    virtual bool
    isZero() const
    {
        return value.isValue == 0;
    };

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_INT16;
    };
    virtual void
        normalizeWithClusterCount( uint64_t );

    virtual
    void
    init_new()
    {
    };

    virtual
    void
    clone_new( const Value* )
    {
    };
};
}
#endif
