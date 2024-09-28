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



#ifndef CUBELIB_STAT_CSV_PLAIN_PRINTER_H
#define CUBELIB_STAT_CSV_PLAIN_PRINTER_H


#include <vector>

#include "AggrCube.h"
#include "CubeMetric.h"
#include "CubeCnode.h"

#include "PlainPrinter.h"




/*-------------------------------------------------------------------------*/
/**
 * @class   CSVPlainPrinter
 * @brief   Class for printing data about severities of a metric on a chosen
 *          cnode as a comma seperated value file
 */
/*-------------------------------------------------------------------------*/
class CSVPlainPrinter : public PlainPrinter
{
public:
    // / @name Constructor & destructor
    // / @{
    CSVPlainPrinter( cube::AggrCube*                 cubeObj,
                     std::vector<std::string> const& metNames,
                     std::vector<std::string> const& cnodeNames );
    virtual
    ~CSVPlainPrinter()
    {
    }
    // / @}
    // / @name Print methods used by clients
    // / @{
    virtual void
    PrintLegend() const;
    virtual void
    GatherAndPrint( cube::Cnode* cnode ) const;

    // / @}
private:
    cube::AggrCube* cubeObject;

    // / Private helper method for gathering and printing the data
    // / (without names)
    void
    PrintValues( cube::Cnode* cnode,
                 inclmode     cnodeMode = INCL ) const;
};



/**
 * Creates a new CSVPlainPrinter instance from the given CUBE object and the
 * names of the requested metrics and cnodes.
 *
 * @param cubeObj The CUBE object used to parse the CUBE file to be analyzed.
 * @param metNames A std::vector containing all metric names for which data is to
 * be gathered and printed.
 * @param cnodeNames A std::vector containing all region names for which data is to
 * be gathered and printed.
 */
CSVPlainPrinter::CSVPlainPrinter( cube::AggrCube*                 cubeObj,
                                  std::vector<std::string> const& metNames,
                                  std::vector<std::string> const& cnodeNames )
    : PlainPrinter( cubeObj, metNames, cnodeNames ), cubeObject( cubeObj )
{
}

/**
 * Prints the legend for the statistics as a line of a comma seperated value
 * file
 */
void
CSVPlainPrinter::PrintLegend() const
{
    std::vector<cube::Metric*> const& _requestedMetricVec = GetRequestedMetrics();
    std::cout << "Routine";
    for ( std::vector<cube::Metric*>::const_iterator it = _requestedMetricVec.begin();
          it != _requestedMetricVec.end(); ++it )
    {
        std::cout << ',' << ( *it )->get_uniq_name();
    }
    std::cout << std::endl;
}

/**
 * Method for gathering and printing data about the severity of certain metrics
 * with respect to given cnodes and their children. This method gathers and
 * prints data about the requested metrics for the given cube::Cnode cnode and all
 * cnodes called by cnode.
 *
 * @param cnode The data is gathered for this cnode and all it's child cnodes.
 */
void
CSVPlainPrinter::GatherAndPrint( cube::Cnode* cnode ) const
{
    // First print data for the given cnode inclusively and
    // exclusively its children
    inclmode modes[] = { INCL, EXCL };
    for ( size_t i = 0; i < sizeof( modes ) / sizeof( inclmode ); ++i )
    {
        if ( modes[ i ] == INCL )
        {
            std::cout << ( "INCL(" + cnode->get_callee()->get_name() + ")" );
        }
        else
        {
            std::cout << ( "EXCL(" + cnode->get_callee()->get_name() + ")" );
        }
        PrintValues( cnode, modes[ i ] );
    }

    // Print data for all children of the given cnode
    for ( unsigned int i = 0; i < cnode->num_children(); ++i )
    {
        std::cout << cnode->get_child( i )->get_callee()->get_name();
        PrintValues( cnode->get_child( i ), INCL );
    }
}

/**
 * Private helper method for gathering and printing the data (without names)
 * for a given cnode
 *
 * @param cnode The data is gathered for this cnode.
 * @param cnodeMode Determines the inclusion mode. If it is INCL, the
 * severities of the child cnodes are added. If it is EXCL, they are not.
 */
void
CSVPlainPrinter::PrintValues( cube::Cnode* cnode, inclmode cnodeMode ) const
{
    std::vector<cube::Metric*> const&   _requestedMetricVec = GetRequestedMetrics();
    std::vector<cube::Location*> const& threadVec           = cubeObject->get_locationv();
    for ( std::vector<cube::Metric*>::const_iterator reqMetIT = _requestedMetricVec.begin();
          reqMetIT != _requestedMetricVec.end(); ++reqMetIT )
    {
        double severity = 0.0;
        for ( std::vector<cube::Location*>::const_iterator threadIT = threadVec.begin();
              threadIT != threadVec.end(); ++threadIT )
        {
            severity += cubeObject->get_vcsev( INCL, cnodeMode, EXCL, *reqMetIT,
                                               cnode, *threadIT );
        }
        std::cout << ',';
        if ( ( *reqMetIT )->get_dtype() == "INTEGER"
             ||
             ( *reqMetIT )->get_dtype() == "UINT64"
             ||
             ( *reqMetIT )->get_dtype() == "INT64" )
        {
            std::cout << std::fixed << std::noshowpoint << std::setprecision( 0 );
        }
        std::cout << severity;
        std::cout.setf( std::ios_base::fmtflags( 0 ), std::ios_base::floatfield );
        std::cout << std::showpoint << std::setprecision( 6 );
    }
    std::cout << std::endl;
}







#endif
