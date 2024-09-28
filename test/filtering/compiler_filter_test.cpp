/*
 * This file is part of the Score-P software (http://www.score-p.org)
 *
 * Copyright (c) 2021,
 * Technische Universitaet Dresden, Germany
 *
 * This software may be modified and distributed under the terms of
 * a BSD-style license.  See the COPYING file in the package base
 * directory for details.
 */

#include <iostream>

using std::cout;
using std::endl;

namespace Kokkos
{
namespace Tools
{
void
hidden()
{
    cout << "H";
}
}

namespace Profiling
{
void
hidden()
{
    cout << "H";
}
}

void
visible()
{
    cout << "V";
}
}

extern "C" {
void
pomp_hidden()
{
    cout << "H";
}

void
Pomp_hidden()
{
    cout << "H";
}

void
POMP_hidden()
{
    cout << "H";
}

void
visible_pomp()
{
    cout << "V";
}
};
