
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
ord__min_n( size_t const n,
            ord const * const xs )
{ ASSERT( n != 0, xs != NULL );
    ord min = ord__normalize( xs[ 0 ] );
    for ( size_t i = 1; i < n; i++ ) {
        min = ord__min2( min, ord__normalize( xs[ i ] ) );
    }
    return min;
}


ord
ord__max_n( size_t const n,
            ord const * const xs )
{ ASSERT( n != 0, xs != NULL );
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



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


ord
ord__succ( ord const x )
{ ord const nx = ord__normalize( x );
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
{ ord const nx = ord__normalize( x );
  ASSERT( nx != ord__min_bound() );
    return nx - 1;
}


ord
ord__pred_b( ord const x )
{
    return ( x <= ord__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


ord
ord__from_str( char const * str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return EQ;
    }
    errno = 0;
    while ( isspace( *str ) ) { str++; }
    ord r;
    if ( strncmp( str, "LT", 2 ) == 0 ) {
        r = LT;
    } else if ( strncmp( str, "EQ", 2 ) == 0 ) {
        r = EQ;
    } else if ( strncmp( str, "GT", 2 ) == 0 ) {
        r = GT;
    } else {
        errno = EBADMSG;
        return EQ;
    }
    str += 2;
    while ( isspace( *str ) ) { str++; }
    if ( *str != '\0' ) {
        errno = EBADMSG;
        return EQ;
    }
    return r;
}



///////////////////////////////////
/// TYPECLASS: TO_CONSTSTR
///////////////////////////////////


char const *
ord__to_conststr( ord const x )
{
    return ( x <= LT )  ? "LT"
         : ( x == EQ )  ? "EQ"
          /* x >= GT */ : "GT";
}

