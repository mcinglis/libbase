
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


#include "ulong.h"

#include <libtypes/types.h>


ulong ulong__id( ulong const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

ulong ulong__min_bound( void ) { return 0; }
ulong ulong__max_bound( void ) { return ULONG_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
ulong__equal(
        ulong const x,
        ulong const y )
{
    return x == y;
}


bool
ulong__not_equal(
        ulong const x,
        ulong const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
ulong__compare(
        ulong const x,
        ulong const y )
{
    return ( x > y ) - ( x < y );
}


bool
ulong__less_than(
        ulong const x,
        ulong const y )
{
    return x < y;
}


bool
ulong__less_than_or_eq(
        ulong const x,
        ulong const y )
{
    return x <= y;
}


bool
ulong__greater_than_or_eq(
        ulong const x,
        ulong const y )
{
    return x >= y;
}


bool
ulong__greater_than(
        ulong const x,
        ulong const y )
{
    return x > y;
}


ulong
ulong__min2(
        ulong const x,
        ulong const y )
{
    return ( x < y ) ? x : y;
}


ulong
ulong__max2(
        ulong const x,
        ulong const y )
{
    return ( x > y ) ? x : y;
}


ulong
ulong__min_n(
        size_t const n,
        ulong const * const xs )
{ ASSERT( n != 0, xs != NULL );
    ulong min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = ulong__min2( min, xs[ i ] );
    }
    return min;
}


ulong
ulong__max_n(
        size_t const n,
        ulong const * const xs )
{ ASSERT( n != 0, xs != NULL );
    ulong max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = ulong__max2( max, xs[ i ] );
    }
    return max;
}


ulong
ulong__clamp(
        ulong const lower,
        ulong const upper,
        ulong const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


ulong
ulong__succ( ulong const x )
{ ASSERT( x != ulong__max_bound() );
    return x + 1;
}


ulong
ulong__succ_b( ulong const x )
{
    return ( x == ulong__max_bound() ) ? x : ( x + 1 );
}


ulong
ulong__pred( ulong const x )
{ ASSERT( x != ulong__min_bound() );
    return x - 1;
}


ulong
ulong__pred_b( ulong const x )
{
    return ( x == ulong__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool ulong__is_signed( void ) { return false; }


bool
ulong__add_would_underflow(
        ulong const x,
        ulong const y )
{
    return false;
}


bool
ulong__add_would_overflow(
        ulong const x,
        ulong const y )
{
    return ( x > ( ulong__max_bound() - y ) );
}


bool
ulong__can_add(
        ulong const x,
        ulong const y )
{
    return !ulong__add_would_overflow( x, y );
}


bool
ulong__sub_would_underflow(
        ulong const x,
        ulong const y )
{
    return ( x < y );
}


bool
ulong__sub_would_overflow(
        ulong const x,
        ulong const y )
{
    return false;
}


bool
ulong__can_sub(
        ulong const x,
        ulong const y )
{
    return !ulong__sub_would_underflow( x, y );
}


bool
ulong__mul_would_underflow(
        ulong const x,
        ulong const y )
{
    return false;
}


bool
ulong__mul_would_overflow(
        ulong const x,
        ulong const y )
{
    return ( x > ( ulong__max_bound() / y ) );
}


bool
ulong__can_mul(
        ulong const x,
        ulong const y )
{
    return !ulong__mul_would_overflow( x, y );
}


bool
ulong__div_would_underflow(
        ulong const x,
        ulong const y )
{
    return false;
}


bool
ulong__div_would_overflow(
        ulong const x,
        ulong const y )
{
    return false;
}


bool
ulong__can_div(
        ulong const x,
        ulong const y )
{
    return y != 0;
}


ulong
ulong__add(
        ulong const x,
        ulong const y )
{
    return x + y;
}


ulong
ulong__sub(
        ulong const x,
        ulong const y )
{
    return x - y;
}


ulong
ulong__mul(
        ulong const x,
        ulong const y )
{
    return x * y;
}


ulong
ulong__div(
        ulong const x,
        ulong const y )
{ ASSERT( y != 0 );
    return x / y;
}


ulong
ulong__mod(
        ulong const x,
        ulong const y )
{ ASSERT( y != 0 );
    return x % y;
}


ulong
ulong__negate( ulong const x )
{
    return -x;
}


ulong
ulong__abs( ulong const x )
{
    return x;
}


ulong
ulong__add_b(
        ulong const x,
        ulong const y )
{
    if ( ulong__add_would_overflow( x, y ) ) {
        return ulong__max_bound();
    } else {
        return x + y;
    }
}


ulong
ulong__sub_b(
        ulong const x,
        ulong const y )
{
    if ( ulong__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


ulong
ulong__mul_b(
        ulong const x,
        ulong const y )
{
    if ( ulong__mul_would_overflow( x, y ) ) {
        return ulong__max_bound();
    } else {
        return x * y;
    }
}


ulong
ulong__div_b(
        ulong const x,
        ulong const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return ulong__max_bound();
        }
    } else {
        return x / y;
    }
}


ulong
ulong__mod_b(
        ulong const x,
        ulong const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


ulong
ulong__negate_b( ulong const x )
{
    return ulong__negate( x );
}


ulong
ulong__abs_b( ulong const x )
{
    return ulong__abs( x );
}


bool
ulong__same_sign(
        ulong const x,
        ulong const y )
{
    return true;
}


bool ulong__is_negative   ( ulong const x ) { return false; }
bool ulong__is_nonpositive( ulong const x ) { return x == 0; }
bool ulong__is_zero       ( ulong const x ) { return x == 0; }
bool ulong__is_nonnegative( ulong const x ) { return true; }
bool ulong__is_positive   ( ulong const x ) { return x != 0; }


ord
ulong__compare_0( ulong const x )
{
    return ulong__compare( x, 0 );
}


bool ulong__is_even( ulong const x ) { return x % 2 == 0; }
bool ulong__is_odd ( ulong const x ) { return x % 2 == 1; }


ulong ulong__add_2( ulong const x )
        { return ulong__add( x, 2 ); }
ulong ulong__sub_2( ulong const x )
        { return ulong__sub( x, 2 ); }
ulong ulong__mul_2( ulong const x )
        { return ulong__mul( x, 2 ); }
ulong ulong__div_2( ulong const x )
        { return ulong__div( x, 2 ); }
ulong ulong__mod_2( ulong const x )
        { return ulong__mod( x, 2 ); }


ulong ulong__mul_10( ulong const x )
        { return ulong__mul( x, 10 ); }
ulong ulong__div_10( ulong const x )
        { return ulong__div( x, 10 ); }


ulong ulong__add_b_2( ulong const x )
        { return ulong__add_b( x, 2 ); }
ulong ulong__sub_b_2( ulong const x )
        { return ulong__sub_b( x, 2 ); }
ulong ulong__mul_b_2( ulong const x )
        { return ulong__mul_b( x, 2 ); }
ulong ulong__mul_b_10( ulong const x )
        { return ulong__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

ulong
ulong__from_str( char const * const str )
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
    } else if ( x < ulong__min_bound()
             || x > ulong__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

