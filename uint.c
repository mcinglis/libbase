
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


#include "uint.h"

#include <libtypes/types.h>


uint uint__id( uint const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

uint uint__min_bound( void ) { return 0; }
uint uint__max_bound( void ) { return UINT_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
uint__equal(
        uint const x,
        uint const y )
{
    return x == y;
}


bool
uint__not_equal(
        uint const x,
        uint const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
uint__compare(
        uint const x,
        uint const y )
{
    return ( x > y ) - ( x < y );
}


bool
uint__less_than(
        uint const x,
        uint const y )
{
    return x < y;
}


bool
uint__less_than_or_eq(
        uint const x,
        uint const y )
{
    return x <= y;
}


bool
uint__greater_than_or_eq(
        uint const x,
        uint const y )
{
    return x >= y;
}


bool
uint__greater_than(
        uint const x,
        uint const y )
{
    return x > y;
}


uint
uint__min2(
        uint const x,
        uint const y )
{
    return ( x < y ) ? x : y;
}


uint
uint__max2(
        uint const x,
        uint const y )
{
    return ( x > y ) ? x : y;
}


uint
uint__min_n(
        size_t const n,
        uint const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uint min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = uint__min2( min, xs[ i ] );
    }
    return min;
}


uint
uint__max_n(
        size_t const n,
        uint const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uint max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = uint__max2( max, xs[ i ] );
    }
    return max;
}


uint
uint__clamp(
        uint const lower,
        uint const upper,
        uint const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


uint
uint__succ( uint const x )
{ ASSERT( x != uint__max_bound() );
    return x + 1;
}


uint
uint__succ_b( uint const x )
{
    return ( x == uint__max_bound() ) ? x : ( x + 1 );
}


uint
uint__pred( uint const x )
{ ASSERT( x != uint__min_bound() );
    return x - 1;
}


uint
uint__pred_b( uint const x )
{
    return ( x == uint__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool uint__is_signed( void ) { return false; }


bool
uint__add_would_underflow(
        uint const x,
        uint const y )
{
    return false;
}


bool
uint__add_would_overflow(
        uint const x,
        uint const y )
{
    return ( x > ( uint__max_bound() - y ) );
}


bool
uint__can_add(
        uint const x,
        uint const y )
{
    return !uint__add_would_overflow( x, y );
}


bool
uint__sub_would_underflow(
        uint const x,
        uint const y )
{
    return ( x < y );
}


bool
uint__sub_would_overflow(
        uint const x,
        uint const y )
{
    return false;
}


bool
uint__can_sub(
        uint const x,
        uint const y )
{
    return !uint__sub_would_underflow( x, y );
}


bool
uint__mul_would_underflow(
        uint const x,
        uint const y )
{
    return false;
}


bool
uint__mul_would_overflow(
        uint const x,
        uint const y )
{
    return ( x > ( uint__max_bound() / y ) );
}


bool
uint__can_mul(
        uint const x,
        uint const y )
{
    return !uint__mul_would_overflow( x, y );
}


bool
uint__div_would_underflow(
        uint const x,
        uint const y )
{
    return false;
}


bool
uint__div_would_overflow(
        uint const x,
        uint const y )
{
    return false;
}


bool
uint__can_div(
        uint const x,
        uint const y )
{
    return y != 0;
}


uint
uint__add(
        uint const x,
        uint const y )
{
    return x + y;
}


uint
uint__sub(
        uint const x,
        uint const y )
{
    return x - y;
}


uint
uint__mul(
        uint const x,
        uint const y )
{
    return x * y;
}


uint
uint__div(
        uint const x,
        uint const y )
{ ASSERT( y != 0 );
    return x / y;
}


uint
uint__mod(
        uint const x,
        uint const y )
{ ASSERT( y != 0 );
    return x % y;
}


uint
uint__negate( uint const x )
{
    return -x;
}


uint
uint__abs( uint const x )
{
    return x;
}


uint
uint__add_b(
        uint const x,
        uint const y )
{
    if ( uint__add_would_overflow( x, y ) ) {
        return uint__max_bound();
    } else {
        return x + y;
    }
}


uint
uint__sub_b(
        uint const x,
        uint const y )
{
    if ( uint__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


uint
uint__mul_b(
        uint const x,
        uint const y )
{
    if ( uint__mul_would_overflow( x, y ) ) {
        return uint__max_bound();
    } else {
        return x * y;
    }
}


uint
uint__div_b(
        uint const x,
        uint const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return uint__max_bound();
        }
    } else {
        return x / y;
    }
}


uint
uint__mod_b(
        uint const x,
        uint const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


uint
uint__negate_b( uint const x )
{
    return uint__negate( x );
}


uint
uint__abs_b( uint const x )
{
    return uint__abs( x );
}


bool
uint__same_sign(
        uint const x,
        uint const y )
{
    return true;
}


bool uint__is_negative   ( uint const x ) { return false; }
bool uint__is_nonpositive( uint const x ) { return x == 0; }
bool uint__is_zero       ( uint const x ) { return x == 0; }
bool uint__is_nonnegative( uint const x ) { return true; }
bool uint__is_positive   ( uint const x ) { return x != 0; }


ord
uint__compare_0( uint const x )
{
    return uint__compare( x, 0 );
}


bool uint__is_even( uint const x ) { return x % 2 == 0; }
bool uint__is_odd ( uint const x ) { return x % 2 == 1; }


uint uint__add_2( uint const x )
        { return uint__add( x, 2 ); }
uint uint__sub_2( uint const x )
        { return uint__sub( x, 2 ); }
uint uint__mul_2( uint const x )
        { return uint__mul( x, 2 ); }
uint uint__div_2( uint const x )
        { return uint__div( x, 2 ); }
uint uint__mod_2( uint const x )
        { return uint__mod( x, 2 ); }


uint uint__mul_10( uint const x )
        { return uint__mul( x, 10 ); }
uint uint__div_10( uint const x )
        { return uint__div( x, 10 ); }


uint uint__add_b_2( uint const x )
        { return uint__add_b( x, 2 ); }
uint uint__sub_b_2( uint const x )
        { return uint__sub_b( x, 2 ); }
uint uint__mul_b_2( uint const x )
        { return uint__mul_b( x, 2 ); }
uint uint__mul_b_10( uint const x )
        { return uint__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

uint
uint__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    ulong const x = strtoul( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < uint__min_bound()
             || x > uint__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

