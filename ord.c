
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


#include "ord.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <libtypes/types.h>
#include <libmacro/assert.h>


ord ord__id( ord const x ) { return x; }


ord ord__normalize( ord const x ) { return ord__clamp( LT, GT, x ); }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


ord ord__min_bound( void ) { return LT; }
ord ord__max_bound( void ) { return GT; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
ord__equal( ord const x,
            ord const y )
{
    return ord__normalize( x ) == ord__normalize( y );
}


bool
ord__not_equal( ord const x,
                ord const y )
{
    return ord__normalize( x ) != ord__normalize( y );
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


ord
ord__compare( ord const x,
              ord const y )
{
    ord const nx = ord__normalize( x );
    ord const ny = ord__normalize( y );
    return ( nx > ny ) - ( nx < ny );
}


bool
ord__less_than( ord const x,
                ord const y )
{
    return ord__normalize( x ) < ord__normalize( y );
}


bool
ord__less_than_or_eq( ord const x,
                      ord const y )
{
    return ord__normalize( x ) <= ord__normalize( y );
}


bool
ord__greater_than_or_eq( ord const x,
                         ord const y )
{
    return ord__normalize( x ) >= ord__normalize( y );
}


bool
ord__greater_than( ord const x,
                   ord const y )
{
    return ord__normalize( x ) > ord__normalize( y );
}


ord
ord__min2( ord const x,
           ord const y )
{
    ord const nx = ord__normalize( x );
    ord const ny = ord__normalize( y );
    return ( nx < ny ) ? nx : ny;
}


ord
ord__max2( ord const x,
           ord const y )
{
    ord const nx = ord__normalize( x );
    ord const ny = ord__normalize( y );
    return ( nx > ny ) ? nx : ny;
}


ord
ord__min_n( ord const * const xs,
            size_t const n )
{
    ASSERT( xs != NULL, n != 0 );

    ord min = ord__normalize( xs[ 0 ] );
    for ( size_t i = 1; i < n; i++ ) {
        min = ord__min2( min, ord__normalize( xs[ i ] ) );
    }
    return min;
}


ord
ord__max_n( ord const * const xs,
            size_t const n )
{
    ASSERT( xs != NULL, n != 0 );

    ord max = ord__normalize( xs[ 0 ] );
    for ( size_t i = 1; i < n; i++ ) {
        max = ord__max2( max, ord__normalize( xs[ i ] ) );
    }
    return max;
}


ord
ord__clamp( ord const lower,
            ord const upper,
            ord const x )
{
    ord const nlower = ord__normalize( lower );
    ord const nupper = ord__normalize( upper );
    ord const nx = ord__normalize( x );
    return ( nlower >= nx ) ? nlower
         : ( nupper <= nx ) ? nupper
                            : nx;
}


ord
ord__in_range( ord const lower,
               ord const upper,
               ord const x )
{
    ord const nx = ord__normalize( x );
    return ord__normalize( lower ) <= nx && nx <= ord__normalize( upper );
}


ord
ord__in_xrange( ord const lower,
                ord const upper,
                ord const x )
{
    ord const nx = ord__normalize( x );
    return ord__normalize( lower ) < nx && nx < ord__normalize( upper );
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


ord
ord__succ( ord const x )
{
    ord const nx = ord__normalize( x );
    ASSERT( nx != ord__max_bound() );

    return nx + 1;
}


ord
ord__succ_b( ord const x )
{
    return ( x >= ord__max_bound() ) ? x : ( x + 1 );
}


ord
ord__pred( ord const x )
{
    ord const nx = ord__normalize( x );
    ASSERT( nx != ord__min_bound() );

    return nx - 1;
}


ord
ord__pred_b( ord const x )
{
    return ( x <= ord__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: FROM_STR
///////////////////////////////////


static
bool
prefixi(
        char const * const xs,
        char const * const ys )
{
    ASSERT( xs != NULL, ys != NULL );

    for ( size_t i = 0; xs[ i ] != '\0'; i++ ) {
        if ( tolower( ( uchar ) xs[ i ] ) != tolower( ( uchar ) ys[ i ] ) ) {
            return false;
        }
    }
    return true;
}


ord
ord__from_str(
        char const * str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return EQ;
    }
    errno = 0;
    char const * p = str;
    while ( isspace( *p ) ) {
        p++;
    }
    ord r;
    if ( prefixi( p, "LT" ) ) {
        r = LT;
    } else if ( prefixi( p, "EQ" ) ) {
        r = EQ;
    } else if ( prefixi( p, "GT" ) ) {
        r = GT;
    } else {
        errno = EBADMSG;
        return EQ;
    }
    p += 2;
    while ( isspace( *p ) ) {
        p++;
    }
    if ( *p != '\0' ) {
        errno = EBADMSG;
        return EQ;
    }
    return r;
}


void
ord__arg_parse(
        char const * const arg_name,
        char const * const arg_value,
        void * const ordvp )
{
    ASSERT( arg_value != NULL, ordvp != NULL );

    ord * const ordp = ordvp;
    *ordp = ord__from_str( arg_value );
}



///////////////////////////////////
/// TYPECLASS: TO_STR
///////////////////////////////////


char const *
ord__to_str(
        ord const x )
{
    return ( x <= LT )  ? "LT"
         : ( x == EQ )  ? "EQ"
          /* x >= GT */ : "GT";
}

