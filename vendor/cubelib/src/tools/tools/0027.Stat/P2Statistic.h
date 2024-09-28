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




#ifndef P2STATISTIC_H
#define P2STATISTIC_H

#include <string>

/*
 *
 * class P2Statistic
 *
 * This class performs the dynmaic calculations of quantiles for large data
 * sets without storing the individual values from the set.
 *
 * based on: Raj Jain, Imrich Chlamtac
 *           "The P2 Algorithm for Dynamic Calculation of Quantiles
 *            and Histograms Without Storing Observations"
 *           in: Communcations of the ACM, Oct 1985, Vol. 28, No. 10
 *
 */

namespace stats
{
class StatsError : std::exception
{
public:

    explicit
    StatsError( std::string message ) : message( message )
    {
    }
    virtual std::string
    get_msg() const
    {
        return "STATS: " + message;
    }
    virtual
    ~StatsError()
    {
    }

protected:

    std::string message;
};

class P2Statistic
{
public:

    P2Statistic();

    void
    add( double val );
    void
    reset();

    long
    count() const;
    double
    mean() const;
    double
    med() const;
    double
    min() const;
    double
    max() const;
    double
    q25() const;
    double
    q75() const;
    double
    sum() const;
    double
    var() const;

private:

    double q[ 5 ];  // quantile values  (0,min) (1,q25) (2,med) (3,q75) (4,max)
    long   n[ 5 ];  // horizontal positions of the quantiles
    double nx[ 5 ]; // desired horizontal positions of the quantiles (n')

    double s;       // sum of values
    double s2;      // sum of sqr(values)

    long counter;   // number of values
};
}
#endif
