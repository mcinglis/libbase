
// Copyright 2014  Malcolm Inglis <http://minglis.id.au>
//
// This file is part of Libbase.
//
// Libbase is free software: you can redistribute it and/or modify it under
// the terms of the GNU Affero General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// Libbase is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
// more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Libbase. If not, see <https://gnu.org/licenses/>.


#ifndef LIBBASE_EQ_SCALAR_H
#define LIBBASE_EQ_SCALAR_H


#include <libtypes/types.h>


// @public
#define DERIVING_EQ_SCALAR( T, TT, TF ) \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__equal( T const x,                                                   \
                 T const y )                                                  \
    {                                                                         \
        return x == y;                                                        \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__not_equal( T const x,                                               \
                     T const y )                                              \
    {                                                                         \
        return x != y;                                                        \
    }


#endif

