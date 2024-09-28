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
**  Copyright (c) 2015                                                     **
**  RWTH Aachen University, JARA-HPC                                       **
**                                                                         **
**  This software may be modified and distributed under the terms of       **
**  a BSD-style license.  See the COPYING file in the package base         **
**  directory for details.                                                 **
****************************************************************************/



/**
 * \file CubeSystemTreeNode.h
 * \brief Provides a relevant description of a general system tree node.
 */

#ifndef CUBELIB_SYSTEM_TREE_NODE_H
#define CUBELIB_SYSTEM_TREE_NODE_H

#include "CubeSysres.h"
#include "CubeTypes.h"
/*
 *----------------------------------------------------------------------------
 *
 * class Thread
 *
 */


namespace cube
{
// class Process;
class Connection;
class CubeProxy;
class SystemTreeNode;
class LocationGroup;

inline bool
operator==( const SystemTreeNode& a,
            const SystemTreeNode& b );

/**
 * Thread is a basics kind of system resources. It doesn't return any "children"
 */
class SystemTreeNode : public Sysres
{
public:

    SystemTreeNode( const std::string& name,
                    const std::string& desc,
                    const std::string& stn_class,
                    SystemTreeNode*    proc = NULL,
                    uint32_t           id = 0,
                    uint32_t           sysid = 0 )
        : Sysres( ( Sysres* )proc, name, id, sysid ), desc( desc ), stn_class( stn_class )
    {
        kind = CUBE_SYSTEM_TREE_NODE;
        groups.clear();
    };

    virtual
    ~SystemTreeNode();

    /// @brief
    ///     Create a location group object via Cube connection
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    static Serializable*
    create( Connection&      connection,
            const CubeProxy& cubeProxy );

    /// @copydoc Serializable::pack
    void
    pack( Connection& connection ) const;

    /// @copydoc Serializable::get_serialization_key
    ///
    virtual std::string
    get_serialization_key() const;

    /// @copydoc Serializable::get_serialization_key
    ///
    static std::string
    get_static_serialization_key();

    ///< Thread does have a rank.
    SystemTreeNode*
    get_parent() const
    {
        return ( SystemTreeNode* )Vertex::get_parent();
    }


    inline
    std::string
    get_desc() const
    {
        return desc;
    }       // /< Gets a description of this machine.

    inline
    void
    set_desc( std::string newDesc )
    {
        desc = newDesc;
    }

    inline
    std::string
    get_class() const
    {
        return stn_class;
    }

    void
    writeXML( std::ostream& out,
              bool          cube3export = false  ) const;    // /< Writes a xml-representation of a thread in a .cube file.

/**
 * Get i-th Thread of this Thread.
 */
    inline
    SystemTreeNode*
    get_child( unsigned int i ) const
    {
        return ( SystemTreeNode* )Vertex::get_child( i );
    }


    inline
    void
    add_location_group( LocationGroup* _lg )
    {
        groups.push_back( _lg );
    };

    inline
    LocationGroup*
    get_location_group( unsigned int i ) const
    {
        return ( groups.size() > i ) ? groups[ i ] : NULL;
    }

    inline
    const std::vector<LocationGroup*>&
    get_groups()
    {
        return groups;
    }

    std::vector<Sysres*>&
    get_all_locations()
    {
        return get_sub_tree_vector();
    }


    inline
    size_t
    num_groups() const
    {
        return groups.size();
    }

    inline
    bool
    isWeakEqual( const SystemTreeNode* another )
    {
        std::string a = get_class();
        std::string b = another->get_class();
        return a == b;
    }

protected:

    /// @brief
    ///     Constructs a SystemTreeNode object via a Cube connection.
    /// @param connection
    ///     Active Cube connection.
    /// @param cubeProxy
    ///     Cube proxy for internal cross-referencing.
    ///
    /// @note
    ///     This constructor is called by the factory method.
    ///
    SystemTreeNode( Connection&      connection,
                    const CubeProxy& cubeProxy );

    virtual
    std::vector<cube::Sysres*>&
    get_sub_tree_vector();

private:
    std::string                   desc;
    std::string                   stn_class;
    std::vector< LocationGroup* > groups;
};






inline bool
operator==( const SystemTreeNode& a, const SystemTreeNode& b )
{
    std::string a1 = a.get_class();
    std::string b1 = b.get_class();
    std::string a2 = a.get_name();
    std::string b2 = b.get_name();

    return ( a1 == b1 ) && ( a2 == b2 );
}




inline bool
operator<( const SystemTreeNode& a, const SystemTreeNode& b )
{
    int a1 = a.get_id();
    int b1 = b.get_id();
    return a1 < b1;
}
}



#endif
