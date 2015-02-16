
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


#include "uint16.h"

#include <libtypes/types.h>


uint16_t uint16__id( uint16_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

uint16_t uint16__min_bound( void ) { return 0; }
uint16_t uint16__max_bound( void ) { return UINT16_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
uint16__equal(
        uint16_t const x,
        uint16_t const y )
{
    return x == y;
}


bool
uint16__not_equal(
        uint16_t const x,
        uint16_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
uint16__compare(
        uint16_t const x,
        uint16_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
uint16__less_than(
        uint16_t const x,
        uint16_t const y )
{
    return x < y;
}


bool
uint16__less_than_or_eq(
        uint16_t const x,
        uint16_t const y )
{
    return x <= y;
}


bool
uint16__greater_than_or_eq(
        uint16_t const x,
        uint16_t const y )
{
    return x >= y;
}


bool
uint16__greater_than(
        uint16_t const x,
        uint16_t const y )
{
    return x > y;
}


uint16_t
uint16__min2(
        uint16_t const x,
        uint16_t const y )
{
    return ( x < y ) ? x : y;
}


uint16_t
uint16__max2(
        uint16_t const x,
        uint16_t const y )
{
    return ( x > y ) ? x : y;
}


uint16_t
uint16__min_n(
        size_t const n,
        uint16_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uint16_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = uint16__min2( min, xs[ i ] );
    }
    return min;
}


uint16_t
uint16__max_n(
        size_t const n,
        uint16_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uint16_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = uint16__max2( max, xs[ i ] );
    }
    return max;
}


uint16_t
uint16__clamp(
        uint16_t const lower,
        uint16_t const upper,
        uint16_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


uint16_t
uint16__succ( uint16_t const x )
{ ASSERT( x != uint16__max_bound() );
    return x + 1;
}


uint16_t
uint16__succ_b( uint16_t const x )
{
    return ( x == uint16__max_bound() ) ? x : ( x + 1 );
}


uint16_t
uint16__pred( uint16_t const x )
{ ASSERT( x != uint16__min_bound() );
    return x - 1;
}


uint16_t
uint16__pred_b( uint16_t const x )
{
    return ( x == uint16__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool uint16__is_signed( void ) { return false; }


bool
uint16__add_would_underflow(
        uint16_t const x,
        uint16_t const y )
{
    return false;
}


bool
uint16__add_would_overflow(
        uint16_t const x,
        uint16_t const y )
{
    return ( x > ( uint16__max_bound() - y ) );
}


bool
uint16__can_add(
        uint16_t const x,
        uint16_t const y )
{
    return !uint16__add_would_overflow( x, y );
}


bool
uint16__sub_would_underflow(
        uint16_t const x,
        uint16_t const y )
{
    return ( x < y );
}


bool
uint16__sub_would_overflow(
        uint16_t const x,
        uint16_t const y )
{
    return false;
}


bool
uint16__can_sub(
        uint16_t const x,
        uint16_t const y )
{
    return !uint16__sub_would_underflow( x, y );
}


bool
uint16__mul_would_underflow(
        uint16_t const x,
        uint16_t const y )
{
    return false;
}


bool
uint16__mul_would_overflow(
        uint16_t const x,
        uint16_t const y )
{
    return ( x > ( uint16__max_bound() / y ) );
}


bool
uint16__can_mul(
        uint16_t const x,
        uint16_t const y )
{
    return !uint16__mul_would_overflow( x, y );
}


bool
uint16__div_would_underflow(
        uint16_t const x,
        uint16_t const y )
{
    return false;
}


bool
uint16__div_would_overflow(
        uint16_t const x,
        uint16_t const y )
{
    return false;
}


bool
uint16__can_div(
        uint16_t const x,
        uint16_t const y )
{
    return y != 0;
}


uint16_t
uint16__add(
        uint16_t const x,
        uint16_t const y )
{
    return x + y;
}


uint16_t
uint16__sub(
        uint16_t const x,
        uint16_t const y )
{
    return x - y;
}


uint16_t
uint16__mul(
        uint16_t const x,
        uint16_t const y )
{
    return x * y;
}


uint16_t
uint16__div(
        uint16_t const x,
        uint16_t const y )
{ ASSERT( y != 0 );
    return x / y;
}


uint16_t
uint16__mod(
        uint16_t const x,
        uint16_t const y )
{ ASSERT( y != 0 );
    return x % y;
}


uint16_t
uint16__negate( uint16_t const x )
{
    return -x;
}


uint16_t
uint16__abs( uint16_t const x )
{
    return x;
}


uint16_t
uint16__add_b(
        uint16_t const x,
        uint16_t const y )
{
    if ( uint16__add_would_overflow( x, y ) ) {
        return uint16__max_bound();
    } else {
        return x + y;
    }
}


uint16_t
uint16__sub_b(
        uint16_t const x,
        uint16_t const y )
{
    if ( uint16__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


uint16_t
uint16__mul_b(
        uint16_t const x,
        uint16_t const y )
{
    if ( uint16__mul_would_overflow( x, y ) ) {
        return uint16__max_bound();
    } else {
        return x * y;
    }
}


uint16_t
uint16__div_b(
        uint16_t const x,
        uint16_t const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return uint16__max_bound();
        }
    } else {
        return x / y;
    }
}


uint16_t
uint16__mod_b(
        uint16_t const x,
        uint16_t const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


uint16_t
uint16__negate_b( uint16_t const x )
{
    return uint16__negate( x );
}


uint16_t
uint16__abs_b( uint16_t const x )
{
    return uint16__abs( x );
}


bool
uint16__same_sign(
        uint16_t const x,
        uint16_t const y )
{
    return true;
}


bool uint16__is_negative   ( uint16_t const x ) { return false; }
bool uint16__is_nonpositive( uint16_t const x ) { return x == 0; }
bool uint16__is_zero       ( uint16_t const x ) { return x == 0; }
bool uint16__is_nonnegative( uint16_t const x ) { return true; }
bool uint16__is_positive   ( uint16_t const x ) { return x != 0; }


ord
uint16__compare_0( uint16_t const x )
{
    return uint16__compare( x, 0 );
}


bool uint16__is_even( uint16_t const x ) { return x % 2 == 0; }
bool uint16__is_odd ( uint16_t const x ) { return x % 2 == 1; }


uint16_t uint16__add_2( uint16_t const x )
        { return uint16__add( x, 2 ); }
uint16_t uint16__sub_2( uint16_t const x )
        { return uint16__sub( x, 2 ); }
uint16_t uint16__mul_2( uint16_t const x )
        { return uint16__mul( x, 2 ); }
uint16_t uint16__div_2( uint16_t const x )
        { return uint16__div( x, 2 ); }
uint16_t uint16__mod_2( uint16_t const x )
        { return uint16__mod( x, 2 ); }


uint16_t uint16__mul_10( uint16_t const x )
        { return uint16__mul( x, 10 ); }
uint16_t uint16__div_10( uint16_t const x )
        { return uint16__div( x, 10 ); }


uint16_t uint16__add_b_2( uint16_t const x )
        { return uint16__add_b( x, 2 ); }
uint16_t uint16__sub_b_2( uint16_t const x )
        { return uint16__sub_b( x, 2 ); }
uint16_t uint16__mul_b_2( uint16_t const x )
        { return uint16__mul_b( x, 2 ); }
uint16_t uint16__mul_b_10( uint16_t const x )
        { return uint16__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

uint16_t
uint16__from_str( char const * const str )
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
    } else if ( x < uint16__min_bound()
             || x > uint16__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

