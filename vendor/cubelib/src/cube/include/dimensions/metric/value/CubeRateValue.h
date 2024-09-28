/****************************************************************************
**  CUBE        http://www.scalasca.org/                                   **
*****************************************************************************
**  Copyright (c) 1998-2023                                                **
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
 * \file CubeRateValue.h
 * \brief  Provides the value, consisting of two "Value"'s. Result value is the fraction of them. Used to
 ************************************************/
#ifndef CUBELIB_RATE_VALUE_H
#define CUBELIB_RATE_VALUE_H

#include <istream>
#include <iostream>
#include <limits>
#include "CubeDoubleValue.h"


namespace cube
{
class Connection;

typedef   struct
{
    int pivot;
}  __attribute__ ( ( __packed__ ) ) RateValueConfig;


class RateValue : public Value
{
private:
    static
    std::vector<RateValueConfig> parameters;
    size_t                       index;

protected:
    DoubleValue main_value;                      // / "heart 1" of the value.
    DoubleValue duratio_value;                   // / "heart 2" of the value.

public:
    RateValue();

    RateValue( double,
               double );

    virtual
    ~RateValue()
    {
    };
    inline
    virtual unsigned
    getSize() const
    {
        return main_value.getSize() + duratio_value.getSize();
    }

    inline
    virtual double
    getDouble() const
    {
        double m_tmp = main_value.getDouble();
        double d_tmp = duratio_value.getDouble();

        if ( d_tmp == 0. )
        {
            return std::numeric_limits<double>::quiet_NaN();
        }
        return m_tmp / d_tmp;
    }
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

    virtual DoubleValue
    getMainValue() const
    {
        return main_value;
    };
    virtual DoubleValue
    getDuratioValue() const
    {
        return duratio_value;
    };

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

    virtual char*
    transformStream( char*,
                     SingleValueTrafo* ) const;

    inline
    virtual Value*
    clone() const
    {
        return new RateValue();  // create "zero" value  0/1
    }
    inline
    virtual Value*
    copy() const
    {
        return new RateValue( main_value.getDouble(),
                              duratio_value.getDouble()
                              );
    }


    inline
    virtual void
    operator+=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        double m_tmp = main_value.getDouble();
        double d_tmp = duratio_value.getDouble();

        double cm_tmp = ( ( RateValue* )chval )->main_value.getDouble();
        double cd_tmp = ( ( RateValue* )chval )->duratio_value.getDouble();

        main_value    = ( m_tmp * cd_tmp + cm_tmp * d_tmp );
        duratio_value = d_tmp * cd_tmp;
    }

    inline
    virtual void
    operator-=( Value* chval )
    {
        if ( chval == NULL )
        {
            return;
        }
        double m_tmp = main_value.getDouble();
        double d_tmp = duratio_value.getDouble();

        double cm_tmp = ( ( RateValue* )chval )->main_value.getDouble();
        double cd_tmp = ( ( RateValue* )chval )->duratio_value.getDouble();

        main_value    = ( m_tmp * cd_tmp - cm_tmp * d_tmp );
        duratio_value = d_tmp * cd_tmp;
    }

    inline
    virtual void
    operator*=( double dval )
    {
        main_value *= dval;
    }                                 // needed by algebra tools

    inline
    virtual void
    operator/=( double dval )
    {
        if ( dval == 0. )
        {
            main_value = std::numeric_limits<double>::quiet_NaN();
        }
        else
        {
            main_value /= dval;
        }
    }

    virtual void
    operator=( double );

    virtual void
    operator=( Value* );


    virtual bool
    isZero() const
    {
        return main_value.isZero() && !duratio_value.isZero();
    };

    virtual DataType
    myDataType() const
    {
        return CUBE_DATA_TYPE_RATE;
    };                                             // not supported yet
    virtual void
        normalizeWithClusterCount( uint64_t );

    virtual
    void
    init_new();

    virtual
    void
    clone_new( const Value* );
};
}
#endif
