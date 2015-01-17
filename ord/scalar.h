
// Copyright 2015  Malcolm Inglis <http://minglis.id.au>
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


#ifndef LIBBASE_ORD_SCALAR_H
#define LIBBASE_ORD_SCALAR_H


#include <libtypes/types.h>     // bool, ord
#include <libmacro/require.h>  // REQUIRE


// @public
#define DERIVING_ORD_SCALAR( T, TT, TF ) \
                                                                              \
                                                                              \
    ord                                                                       \
    TF##__compare( T const x,                                                 \
                   T const y )                                                \
    {                                                                         \
        return ( x > y ) - ( x < y );                                         \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__less_than( T const x,                                               \
                     T const y )                                              \
    {                                                                         \
        return x < y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                     \
    TF##__less_than_or_eq( T const x,                                         \
                           T const y )                                        \
    {                                                                         \
        return x <= y;                                                        \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__greater_than_or_eq( T const x,                                      \
                              T const y )                                     \
    {                                                                         \
        return x >= y;                                                        \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__greater_than( T const x,                                            \
                        T const y )                                           \
    {                                                                         \
        return x > y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__min2( T const x,                                                    \
                T const y )                                                   \
    {                                                                         \
        return ( x < y ) ? x : y;                                             \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__max2( T const x,                                                    \
                T const y )                                                   \
    {                                                                         \
        return ( x > y ) ? x : y;                                             \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__min_n( size_t const n,                                              \
                 T const * const xs )                                         \
    {                                                                         \
        REQUIRE( n > 0, xs != NULL );                                         \
                                                                              \
        T min = xs[ 0 ];                                                      \
        for ( size_t i = 1; i < n; i++ ) {                                    \
            if ( xs[ i ] < min ) {                                            \
                min = xs[ i ];                                                \
            }                                                                 \
        }                                                                     \
        return min;                                                           \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__max_n( size_t const n,                                              \
                 T const * const xs )                                         \
    {                                                                         \
        REQUIRE( n > 0, xs != NULL );                                         \
                                                                              \
        T max = xs[ 0 ];                                                      \
        for ( size_t i = 1; i < n; i++ ) {                                    \
            if ( xs[ i ] > max ) {                                            \
                max = xs[ i ];                                                \
            }                                                                 \
        }                                                                     \
        return max;                                                           \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__clamp( T const lower,                                               \
                 T const upper,                                               \
                 T const x )                                                  \
    {                                                                         \
        return ( lower >= x ) ? lower                                         \
             : ( upper <= x ) ? upper                                         \
                              : x;                                            \
    }


#endif

