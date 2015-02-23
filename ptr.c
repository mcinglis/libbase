
// This file is the result of executing `gensource.py`. You should make changes
// to this code by changing the template strings or the build process -- not
// editing this file.


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


#include "ptr.h"

#include <libtypes/types.h>


void * ptr__id( void * const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
ptr__equal(
        void * const x,
        void * const y )
{
    return x == y;
}


bool
ptr__not_equal(
        void * const x,
        void * const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
ptr__compare(
        void * const x,
        void * const y )
{
    return ( x > y ) - ( x < y );
}


bool
ptr__less_than(
        void * const x,
        void * const y )
{
    return x < y;
}


bool
ptr__less_than_or_eq(
        void * const x,
        void * const y )
{
    return x <= y;
}


bool
ptr__greater_than_or_eq(
        void * const x,
        void * const y )
{
    return x >= y;
}


bool
ptr__greater_than(
        void * const x,
        void * const y )
{
    return x > y;
}


void *
ptr__min2(
        void * const x,
        void * const y )
{
    return ( x < y ) ? x : y;
}


void *
ptr__max2(
        void * const x,
        void * const y )
{
    return ( x > y ) ? x : y;
}


void *
ptr__min_n(
        size_t const n,
        void * const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    void * min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = ptr__min2( min, xs[ i ] );
    }
    return min;
}


void *
ptr__max_n(
        size_t const n,
        void * const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    void * max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = ptr__max2( max, xs[ i ] );
    }
    return max;
}


void *
ptr__clamp(
        void * const lower,
        void * const upper,
        void * const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
ptr__in_range(
        void * const lower,
        void * const upper,
        void * const x )
{
    return lower <= x && x <= upper;
}


bool
ptr__in_range_x(
        void * const lower,
        void * const upper,
        void * const x )
{
    return lower < x && x < upper;
}

