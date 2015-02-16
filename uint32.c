
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


#include "uint32.h"

#include <libtypes/types.h>


uint32_t uint32__id( uint32_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

uint32_t uint32__min_bound( void ) { return 0; }
uint32_t uint32__max_bound( void ) { return UINT32_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
uint32__equal(
        uint32_t const x,
        uint32_t const y )
{
    return x == y;
}


bool
uint32__not_equal(
        uint32_t const x,
        uint32_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
uint32__compare(
        uint32_t const x,
        uint32_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
uint32__less_than(
        uint32_t const x,
        uint32_t const y )
{
    return x < y;
}


bool
uint32__less_than_or_eq(
        uint32_t const x,
        uint32_t const y )
{
    return x <= y;
}


bool
uint32__greater_than_or_eq(
        uint32_t const x,
        uint32_t const y )
{
    return x >= y;
}


bool
uint32__greater_than(
        uint32_t const x,
        uint32_t const y )
{
    return x > y;
}


uint32_t
uint32__min2(
        uint32_t const x,
        uint32_t const y )
{
    return ( x < y ) ? x : y;
}


uint32_t
uint32__max2(
        uint32_t const x,
        uint32_t const y )
{
    return ( x > y ) ? x : y;
}


uint32_t
uint32__min_n(
        size_t const n,
        uint32_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uint32_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = uint32__min2( min, xs[ i ] );
    }
    return min;
}


uint32_t
uint32__max_n(
        size_t const n,
        uint32_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uint32_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = uint32__max2( max, xs[ i ] );
    }
    return max;
}


uint32_t
uint32__clamp(
        uint32_t const lower,
        uint32_t const upper,
        uint32_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


uint32_t
uint32__succ( uint32_t const x )
{ ASSERT( x != uint32__max_bound() );
    return x + 1;
}


uint32_t
uint32__succ_b( uint32_t const x )
{
    return ( x == uint32__max_bound() ) ? x : ( x + 1 );
}


uint32_t
uint32__pred( uint32_t const x )
{ ASSERT( x != uint32__min_bound() );
    return x - 1;
}


uint32_t
uint32__pred_b( uint32_t const x )
{
    return ( x == uint32__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool uint32__is_signed( void ) { return false; }


bool
uint32__add_would_underflow(
        uint32_t const x,
        uint32_t const y )
{
    return false;
}


bool
uint32__add_would_overflow(
        uint32_t const x,
        uint32_t const y )
{
    return ( x > ( uint32__max_bound() - y ) );
}


bool
uint32__can_add(
        uint32_t const x,
        uint32_t const y )
{
    return !uint32__add_would_overflow( x, y );
}


bool
uint32__sub_would_underflow(
        uint32_t const x,
        uint32_t const y )
{
    return ( x < y );
}


bool
uint32__sub_would_overflow(
        uint32_t const x,
        uint32_t const y )
{
    return false;
}


bool
uint32__can_sub(
        uint32_t const x,
        uint32_t const y )
{
    return !uint32__sub_would_underflow( x, y );
}


bool
uint32__mul_would_underflow(
        uint32_t const x,
        uint32_t const y )
{
    return false;
}


bool
uint32__mul_would_overflow(
        uint32_t const x,
        uint32_t const y )
{
    return ( x > ( uint32__max_bound() / y ) );
}


bool
uint32__can_mul(
        uint32_t const x,
        uint32_t const y )
{
    return !uint32__mul_would_overflow( x, y );
}


bool
uint32__div_would_underflow(
        uint32_t const x,
        uint32_t const y )
{
    return false;
}


bool
uint32__div_would_overflow(
        uint32_t const x,
        uint32_t const y )
{
    return false;
}


bool
uint32__can_div(
        uint32_t const x,
        uint32_t const y )
{
    return y != 0;
}


uint32_t
uint32__add(
        uint32_t const x,
        uint32_t const y )
{
    return x + y;
}


uint32_t
uint32__sub(
        uint32_t const x,
        uint32_t const y )
{
    return x - y;
}


uint32_t
uint32__mul(
        uint32_t const x,
        uint32_t const y )
{
    return x * y;
}


uint32_t
uint32__div(
        uint32_t const x,
        uint32_t const y )
{ ASSERT( y != 0 );
    return x / y;
}


uint32_t
uint32__mod(
        uint32_t const x,
        uint32_t const y )
{ ASSERT( y != 0 );
    return x % y;
}


uint32_t
uint32__negate( uint32_t const x )
{
    return -x;
}


uint32_t
uint32__abs( uint32_t const x )
{
    return x;
}


uint32_t
uint32__add_b(
        uint32_t const x,
        uint32_t const y )
{
    if ( uint32__add_would_overflow( x, y ) ) {
        return uint32__max_bound();
    } else {
        return x + y;
    }
}


uint32_t
uint32__sub_b(
        uint32_t const x,
        uint32_t const y )
{
    if ( uint32__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


uint32_t
uint32__mul_b(
        uint32_t const x,
        uint32_t const y )
{
    if ( uint32__mul_would_overflow( x, y ) ) {
        return uint32__max_bound();
    } else {
        return x * y;
    }
}


uint32_t
uint32__div_b(
        uint32_t const x,
        uint32_t const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return uint32__max_bound();
        }
    } else {
        return x / y;
    }
}


uint32_t
uint32__mod_b(
        uint32_t const x,
        uint32_t const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


uint32_t
uint32__negate_b( uint32_t const x )
{
    return uint32__negate( x );
}


uint32_t
uint32__abs_b( uint32_t const x )
{
    return uint32__abs( x );
}


bool
uint32__same_sign(
        uint32_t const x,
        uint32_t const y )
{
    return true;
}


bool uint32__is_negative   ( uint32_t const x ) { return false; }
bool uint32__is_nonpositive( uint32_t const x ) { return x == 0; }
bool uint32__is_zero       ( uint32_t const x ) { return x == 0; }
bool uint32__is_nonnegative( uint32_t const x ) { return true; }
bool uint32__is_positive   ( uint32_t const x ) { return x != 0; }


ord
uint32__compare_0( uint32_t const x )
{
    return uint32__compare( x, 0 );
}


bool uint32__is_even( uint32_t const x ) { return x % 2 == 0; }
bool uint32__is_odd ( uint32_t const x ) { return x % 2 == 1; }


uint32_t uint32__add_2( uint32_t const x )
        { return uint32__add( x, 2 ); }
uint32_t uint32__sub_2( uint32_t const x )
        { return uint32__sub( x, 2 ); }
uint32_t uint32__mul_2( uint32_t const x )
        { return uint32__mul( x, 2 ); }
uint32_t uint32__div_2( uint32_t const x )
        { return uint32__div( x, 2 ); }
uint32_t uint32__mod_2( uint32_t const x )
        { return uint32__mod( x, 2 ); }


uint32_t uint32__mul_10( uint32_t const x )
        { return uint32__mul( x, 10 ); }
uint32_t uint32__div_10( uint32_t const x )
        { return uint32__div( x, 10 ); }


uint32_t uint32__add_b_2( uint32_t const x )
        { return uint32__add_b( x, 2 ); }
uint32_t uint32__sub_b_2( uint32_t const x )
        { return uint32__sub_b( x, 2 ); }
uint32_t uint32__mul_b_2( uint32_t const x )
        { return uint32__mul_b( x, 2 ); }
uint32_t uint32__mul_b_10( uint32_t const x )
        { return uint32__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

uint32_t
uint32__from_str( char const * const str )
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
    } else if ( x < uint32__min_bound()
             || x > uint32__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

