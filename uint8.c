
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


#include "uint8.h"

#include <libtypes/types.h>


uint8_t uint8__id( uint8_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

uint8_t uint8__min_bound( void ) { return 0; }
uint8_t uint8__max_bound( void ) { return UINT8_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
uint8__equal(
        uint8_t const x,
        uint8_t const y )
{
    return x == y;
}


bool
uint8__not_equal(
        uint8_t const x,
        uint8_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
uint8__compare(
        uint8_t const x,
        uint8_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
uint8__less_than(
        uint8_t const x,
        uint8_t const y )
{
    return x < y;
}


bool
uint8__less_than_or_eq(
        uint8_t const x,
        uint8_t const y )
{
    return x <= y;
}


bool
uint8__greater_than_or_eq(
        uint8_t const x,
        uint8_t const y )
{
    return x >= y;
}


bool
uint8__greater_than(
        uint8_t const x,
        uint8_t const y )
{
    return x > y;
}


uint8_t
uint8__min2(
        uint8_t const x,
        uint8_t const y )
{
    return ( x < y ) ? x : y;
}


uint8_t
uint8__max2(
        uint8_t const x,
        uint8_t const y )
{
    return ( x > y ) ? x : y;
}


uint8_t
uint8__min_n(
        size_t const n,
        uint8_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    uint8_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = uint8__min2( min, xs[ i ] );
    }
    return min;
}


uint8_t
uint8__max_n(
        size_t const n,
        uint8_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    uint8_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = uint8__max2( max, xs[ i ] );
    }
    return max;
}


uint8_t
uint8__clamp(
        uint8_t const lower,
        uint8_t const upper,
        uint8_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
uint8__in_range(
        uint8_t const lower,
        uint8_t const upper,
        uint8_t const x )
{
    return lower <= x && x <= upper;
}


bool
uint8__in_range_x(
        uint8_t const lower,
        uint8_t const upper,
        uint8_t const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


uint8_t
uint8__succ( uint8_t const x )
{
    ASSERT( x != uint8__max_bound() );

    return x + 1;
}


uint8_t
uint8__succ_b( uint8_t const x )
{
    return ( x == uint8__max_bound() ) ? x : ( x + 1 );
}


uint8_t
uint8__pred( uint8_t const x )
{
    ASSERT( x != uint8__min_bound() );

    return x - 1;
}


uint8_t
uint8__pred_b( uint8_t const x )
{
    return ( x == uint8__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool uint8__is_signed( void ) { return false; }


bool
uint8__add_would_underflow(
        uint8_t const x,
        uint8_t const y )
{
    return false;
}


bool
uint8__add_would_overflow(
        uint8_t const x,
        uint8_t const y )
{
    return ( x > ( uint8__max_bound() - y ) );
}


bool
uint8__can_add(
        uint8_t const x,
        uint8_t const y )
{
    return !uint8__add_would_overflow( x, y );
}


bool
uint8__sub_would_underflow(
        uint8_t const x,
        uint8_t const y )
{
    return ( x < y );
}


bool
uint8__sub_would_overflow(
        uint8_t const x,
        uint8_t const y )
{
    return false;
}


bool
uint8__can_sub(
        uint8_t const x,
        uint8_t const y )
{
    return !uint8__sub_would_underflow( x, y );
}


bool
uint8__mul_would_underflow(
        uint8_t const x,
        uint8_t const y )
{
    return false;
}


bool
uint8__mul_would_overflow(
        uint8_t const x,
        uint8_t const y )
{
    return ( x > ( uint8__max_bound() / y ) );
}


bool
uint8__can_mul(
        uint8_t const x,
        uint8_t const y )
{
    return !uint8__mul_would_overflow( x, y );
}


bool
uint8__div_would_underflow(
        uint8_t const x,
        uint8_t const y )
{
    return false;
}


bool
uint8__div_would_overflow(
        uint8_t const x,
        uint8_t const y )
{
    return false;
}


bool
uint8__can_div(
        uint8_t const x,
        uint8_t const y )
{
    return y != 0;
}


uint8_t
uint8__add(
        uint8_t const x,
        uint8_t const y )
{
    return x + y;
}


uint8_t
uint8__sub(
        uint8_t const x,
        uint8_t const y )
{
    return x - y;
}


uint8_t
uint8__mul(
        uint8_t const x,
        uint8_t const y )
{
    return x * y;
}


uint8_t
uint8__div(
        uint8_t const x,
        uint8_t const y )
{
    ASSERT( y != 0 );

    return x / y;
}


uint8_t
uint8__mod(
        uint8_t const x,
        uint8_t const y )
{
    ASSERT( y != 0 );

    return x % y;
}


uint8_t
uint8__negate( uint8_t const x )
{
    return -x;
}


uint8_t
uint8__abs( uint8_t const x )
{
    return x;
}


uint8_t
uint8__add_b(
        uint8_t const x,
        uint8_t const y )
{
    if ( uint8__add_would_overflow( x, y ) ) {
        return uint8__max_bound();
    } else {
        return x + y;
    }
}


uint8_t
uint8__sub_b(
        uint8_t const x,
        uint8_t const y )
{
    if ( uint8__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


uint8_t
uint8__mul_b(
        uint8_t const x,
        uint8_t const y )
{
    if ( uint8__mul_would_overflow( x, y ) ) {
        return uint8__max_bound();
    } else {
        return x * y;
    }
}


uint8_t
uint8__div_b(
        uint8_t const x,
        uint8_t const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return uint8__max_bound();
        }
    } else {
        return x / y;
    }
}


uint8_t
uint8__mod_b(
        uint8_t const x,
        uint8_t const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


uint8_t
uint8__negate_b( uint8_t const x )
{
    return uint8__negate( x );
}


uint8_t
uint8__abs_b( uint8_t const x )
{
    return uint8__abs( x );
}


bool
uint8__same_sign(
        uint8_t const x,
        uint8_t const y )
{
    return true;
}


bool uint8__is_negative   ( uint8_t const x ) { return false; }
bool uint8__is_nonpositive( uint8_t const x ) { return x == 0; }
bool uint8__is_zero       ( uint8_t const x ) { return x == 0; }
bool uint8__is_nonzero    ( uint8_t const x ) { return x != 0; }
bool uint8__is_nonnegative( uint8_t const x ) { return true; }
bool uint8__is_positive   ( uint8_t const x ) { return x != 0; }


ord
uint8__compare_0( uint8_t const x )
{
    return uint8__compare( x, 0 );
}


bool uint8__is_even( uint8_t const x ) { return x % 2 == 0; }
bool uint8__is_odd ( uint8_t const x ) { return x % 2 == 1; }


uint8_t uint8__add_2( uint8_t const x )
        { return uint8__add( x, 2 ); }
uint8_t uint8__sub_2( uint8_t const x )
        { return uint8__sub( x, 2 ); }
uint8_t uint8__mul_2( uint8_t const x )
        { return uint8__mul( x, 2 ); }
uint8_t uint8__div_2( uint8_t const x )
        { return uint8__div( x, 2 ); }
uint8_t uint8__mod_2( uint8_t const x )
        { return uint8__mod( x, 2 ); }


uint8_t uint8__mul_10( uint8_t const x )
        { return uint8__mul( x, 10 ); }
uint8_t uint8__div_10( uint8_t const x )
        { return uint8__div( x, 10 ); }


uint8_t uint8__add_b_2( uint8_t const x )
        { return uint8__add_b( x, 2 ); }
uint8_t uint8__sub_b_2( uint8_t const x )
        { return uint8__sub_b( x, 2 ); }
uint8_t uint8__mul_b_2( uint8_t const x )
        { return uint8__mul_b( x, 2 ); }
uint8_t uint8__mul_b_10( uint8_t const x )
        { return uint8__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

uint8_t
uint8__from_str( char const * const str )
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
    } else if ( x < uint8__min_bound()
             || x > uint8__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

