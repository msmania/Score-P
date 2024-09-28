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


#include "config.h"

#include "CowTree.h"
using namespace std;
using namespace cube;

template < typename T >
map<const CowNode<T>*, typename CowNode<T>::MetaTree*>
CowNode<T>::root_to_meta_node;


template < typename T >
const typename CowNode<T>::preorder_iterator&
CowNode<T>::end_iterator
    = typename
      CowNode<T>::preorder_iterator::preorder_iterator();
