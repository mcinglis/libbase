
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


#include "bool.h"

#include <libtypes/types.h>


bool bool__id( bool const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


bool bool__min_bound( void ) { return false; }
bool bool__max_bound( void ) { return true; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
bool__equal(
        bool const x,
        bool const y )
{
    return x == y;
}


bool
bool__not_equal(
        bool const x,
        bool const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
bool__compare(
        bool const x,
        bool const y )
{
    return ( x > y ) - ( x < y );
}


bool
bool__less_than(
        bool const x,
        bool const y )
{
    return x < y;
}


bool
bool__less_than_or_eq(
        bool const x,
        bool const y )
{
    return x <= y;
}


bool
bool__greater_than_or_eq(
        bool const x,
        bool const y )
{
    return x >= y;
}


bool
bool__greater_than(
        bool const x,
        bool const y )
{
    return x > y;
}


bool
bool__min2(
        bool const x,
        bool const y )
{
    return ( x < y ) ? x : y;
}


bool
bool__max2(
        bool const x,
        bool const y )
{
    return ( x > y ) ? x : y;
}


bool
bool__min_n(
        size_t const n,
        bool const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    bool min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = bool__min2( min, xs[ i ] );
    }
    return min;
}


bool
bool__max_n(
        size_t const n,
        bool const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    bool max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = bool__max2( max, xs[ i ] );
    }
    return max;
}


bool
bool__clamp(
        bool const lower,
        bool const upper,
        bool const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


bool
bool__succ( bool const x )
{
    ASSERT( x != bool__max_bound() );

    return x + 1;
}


bool
bool__succ_b( bool const x )
{
    return ( x == bool__max_bound() ) ? x : ( x + 1 );
}


bool
bool__pred( bool const x )
{
    ASSERT( x != bool__min_bound() );

    return x - 1;
}


bool
bool__pred_b( bool const x )
{
    return ( x == bool__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <ctype.h>
#include <errno.h>
#include <string.h>

bool
bool__from_str( char const * str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return false;
    }
    errno = 0;
    while ( isspace( *str ) ) {
        str++;
    }
    bool r;
    static char const true_str[] = "true";
    static char const false_str[] = "false";
    if ( strncmp( str, true_str, sizeof true_str - 1 ) == 0 ) {
        r = true;
        str += sizeof true_str - 1;
    } else if ( strncmp( str, false_str, sizeof false_str - 1 ) == 0 ) {
        r = false;
        str += sizeof false_str - 1;
    } else {
        errno = EBADMSG;
        return false;
    }
    while ( isspace( *str ) ) {
        str++;
    }
    if ( *str != '\0' ) {
        errno = EBADMSG;
        return false;
    }
    return r;
}



///////////////////////////////////
/// TYPECLASS: TO_CONSTSTR
///////////////////////////////////


char const *
bool__to_conststr( bool const x )
{
    return x ? "true" : "false";
}

