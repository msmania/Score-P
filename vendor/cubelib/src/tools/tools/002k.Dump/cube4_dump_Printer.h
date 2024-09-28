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



#ifndef CUBELIB_DUMP_PRINTER
#define CUBELIB_DUMP_PRINTER

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>

#include "Cube.h"
#include "CubeCnode.h"
/*
 * Cube3 compatibility mode , should be reconsidered
 */
#include "CubeSystemTreeNode.h"
#include "CubeMetric.h"
#include "CubeRegion.h"
#include "CubeServices.h"
#include "CubeTypes.h"
#include "algebra4.h"


#include "cube4_dump_CommandOption.h"


typedef std::vector<uint64_t> bitstring_t;





class Printer
{
private:
    void
        plain_dump_cnode(
        cube::Cnode*,
        int,
        bitstring_t  ) const;

protected:
    std::ostream& fout;
    cube::Cube*   cube;

    void
    dump_cube_attributes( const std::map<std::string, std::string>&  ) const;

    void
    dump_cube_mirrors( const std::vector<std::string>&  ) const;

    void
    dump_metric_dimension( const std::vector<cube::Metric*>&  );

    void
    dump_calltree_dimension( const std::vector<cube::Region*>&,
                             const std::vector<cube::Cnode*>&,
                             const std::vector<cube::Cnode*>& );

    void
    dump_system_dimension( const std::vector<cube::SystemTreeNode*>&  );

    void
    dump_topologies( const std::vector<cube::Cartesian*>&,
                     bool                                  ) const;
    void
    dump_topology( cube::Cartesian*,
                   bool              ) const;

    void
    dump_misc_data( std::string,
                    bool         ) const;


    void
        dump_metric( cube::Metric*,
                     int,
                     bitstring_t    );

    void
    dump_region( cube::Region* region ) const;

    void
        dump_cnode( cube::Cnode*,
                    int,
                    bitstring_t   );
    void
        dump_tasks( cube::Cnode*,
                    int,
                    bitstring_t   );
    void
        dump_location( cube::Location*,
                       int,
                       bitstring_t      ) const;

    void
        dump_location_group( cube::LocationGroup*,
                             int,
                             bitstring_t           );

    void
        dump_stn( cube::SystemTreeNode*,
                  int,
                  bitstring_t            );

    void
    dump_cubepl_memory() const;

public:
    Printer( std::ostream& _out,
             cube::Cube*   _cube ) : fout( _out ), cube( _cube )
    {
    }
    virtual
    ~Printer()
    {
    };

    void
    print_header_metric_dimension( const bool show_ghost );

    void
    print_header_calltree_dimension();

    void
    print_header_system_dimension();

    void
    print_header_topologies( const bool show_coords ) const;

    void
    print_header_cube_attributes() const;

    void
    print_header_cube_mirrors() const;

    void
    print_header_files( const std::string& data,
                        const bool         selected_data ) const;

    void
    print_header( const std::string& data,
                  const bool         show_ghost,
                  const bool         selected_data,
                  const bool         show_coords );


    void
    prepare(    std::vector < cube::Metric* >& _metrics,
                std::vector < cube::Cnode* >&  _cnodes,
                std::vector < cube::Thread* >& _threads ) const;


    virtual
    void
    dump_data( std::vector < cube::Metric* >& _metrics,
               std::vector < cube::Cnode* >&  _cnodes,
               std::vector < cube::Thread* >& _threads,
               cube::CalculationFlavour       _mf,
               cube::CalculationFlavour       _cf,
               bool                           stored,
               ThreadSelection                selected_threads ) const;

    virtual
    void
    dump_flat_profile(  std::vector < cube::Metric* >& _metrics,
                        std::vector < cube::Region* >& regions,
                        std::vector < cube::Thread* >& _threads,
                        cube::CalculationFlavour       _mf,
                        ThreadSelection                selected_threads ) const;
};

#endif
