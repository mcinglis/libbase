
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


#include "uintmax.h"

#include <libtypes/types.h>


uintmax_t uintmax__id( uintmax_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

uintmax_t uintmax__min_bound( void ) { return 0; }
uintmax_t uintmax__max_bound( void ) { return UINTMAX_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
uintmax__equal(
        uintmax_t const x,
        uintmax_t const y )
{
    return x == y;
}


bool
uintmax__not_equal(
        uintmax_t const x,
        uintmax_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
uintmax__compare(
        uintmax_t const x,
        uintmax_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
uintmax__less_than(
        uintmax_t const x,
        uintmax_t const y )
{
    return x < y;
}


bool
uintmax__less_than_or_eq(
        uintmax_t const x,
        uintmax_t const y )
{
    return x <= y;
}


bool
uintmax__greater_than_or_eq(
        uintmax_t const x,
        uintmax_t const y )
{
    return x >= y;
}


bool
uintmax__greater_than(
        uintmax_t const x,
        uintmax_t const y )
{
    return x > y;
}


uintmax_t
uintmax__min2(
        uintmax_t const x,
        uintmax_t const y )
{
    return ( x < y ) ? x : y;
}


uintmax_t
uintmax__max2(
        uintmax_t const x,
        uintmax_t const y )
{
    return ( x > y ) ? x : y;
}


uintmax_t
uintmax__min_n(
        size_t const n,
        uintmax_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uintmax_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = uintmax__min2( min, xs[ i ] );
    }
    return min;
}


uintmax_t
uintmax__max_n(
        size_t const n,
        uintmax_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uintmax_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = uintmax__max2( max, xs[ i ] );
    }
    return max;
}


uintmax_t
uintmax__clamp(
        uintmax_t const lower,
        uintmax_t const upper,
        uintmax_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


uintmax_t
uintmax__succ( uintmax_t const x )
{ ASSERT( x != uintmax__max_bound() );
    return x + 1;
}


uintmax_t
uintmax__succ_b( uintmax_t const x )
{
    return ( x == uintmax__max_bound() ) ? x : ( x + 1 );
}


uintmax_t
uintmax__pred( uintmax_t const x )
{ ASSERT( x != uintmax__min_bound() );
    return x - 1;
}


uintmax_t
uintmax__pred_b( uintmax_t const x )
{
    return ( x == uintmax__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool uintmax__is_signed( void ) { return false; }


bool
uintmax__add_would_underflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return false;
}


bool
uintmax__add_would_overflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return ( x > ( uintmax__max_bound() - y ) );
}


bool
uintmax__can_add(
        uintmax_t const x,
        uintmax_t const y )
{
    return !uintmax__add_would_overflow( x, y );
}


bool
uintmax__sub_would_underflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return ( x < y );
}


bool
uintmax__sub_would_overflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return false;
}


bool
uintmax__can_sub(
        uintmax_t const x,
        uintmax_t const y )
{
    return !uintmax__sub_would_underflow( x, y );
}


bool
uintmax__mul_would_underflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return false;
}


bool
uintmax__mul_would_overflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return ( x > ( uintmax__max_bound() / y ) );
}


bool
uintmax__can_mul(
        uintmax_t const x,
        uintmax_t const y )
{
    return !uintmax__mul_would_overflow( x, y );
}


bool
uintmax__div_would_underflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return false;
}


bool
uintmax__div_would_overflow(
        uintmax_t const x,
        uintmax_t const y )
{
    return false;
}


bool
uintmax__can_div(
        uintmax_t const x,
        uintmax_t const y )
{
    return y != 0;
}


uintmax_t
uintmax__add(
        uintmax_t const x,
        uintmax_t const y )
{
    return x + y;
}


uintmax_t
uintmax__sub(
        uintmax_t const x,
        uintmax_t const y )
{
    return x - y;
}


uintmax_t
uintmax__mul(
        uintmax_t const x,
        uintmax_t const y )
{
    return x * y;
}


uintmax_t
uintmax__div(
        uintmax_t const x,
        uintmax_t const y )
{ ASSERT( y != 0 );
    return x / y;
}


uintmax_t
uintmax__mod(
        uintmax_t const x,
        uintmax_t const y )
{ ASSERT( y != 0 );
    return x % y;
}


uintmax_t
uintmax__negate( uintmax_t const x )
{
    return -x;
}


uintmax_t
uintmax__abs( uintmax_t const x )
{
    return x;
}


uintmax_t
uintmax__add_b(
        uintmax_t const x,
        uintmax_t const y )
{
    if ( uintmax__add_would_overflow( x, y ) ) {
        return uintmax__max_bound();
    } else {
        return x + y;
    }
}


uintmax_t
uintmax__sub_b(
        uintmax_t const x,
        uintmax_t const y )
{
    if ( uintmax__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


uintmax_t
uintmax__mul_b(
        uintmax_t const x,
        uintmax_t const y )
{
    if ( uintmax__mul_would_overflow( x, y ) ) {
        return uintmax__max_bound();
    } else {
        return x * y;
    }
}


uintmax_t
uintmax__div_b(
        uintmax_t const x,
        uintmax_t const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return uintmax__max_bound();
        }
    } else {
        return x / y;
    }
}


uintmax_t
uintmax__mod_b(
        uintmax_t const x,
        uintmax_t const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


uintmax_t
uintmax__negate_b( uintmax_t const x )
{
    return uintmax__negate( x );
}


uintmax_t
uintmax__abs_b( uintmax_t const x )
{
    return uintmax__abs( x );
}


bool
uintmax__same_sign(
        uintmax_t const x,
        uintmax_t const y )
{
    return true;
}


bool uintmax__is_negative   ( uintmax_t const x ) { return false; }
bool uintmax__is_nonpositive( uintmax_t const x ) { return x == 0; }
bool uintmax__is_zero       ( uintmax_t const x ) { return x == 0; }
bool uintmax__is_nonnegative( uintmax_t const x ) { return true; }
bool uintmax__is_positive   ( uintmax_t const x ) { return x != 0; }


ord
uintmax__compare_0( uintmax_t const x )
{
    return uintmax__compare( x, 0 );
}


bool uintmax__is_even( uintmax_t const x ) { return x % 2 == 0; }
bool uintmax__is_odd ( uintmax_t const x ) { return x % 2 == 1; }


uintmax_t uintmax__add_2( uintmax_t const x )
        { return uintmax__add( x, 2 ); }
uintmax_t uintmax__sub_2( uintmax_t const x )
        { return uintmax__sub( x, 2 ); }
uintmax_t uintmax__mul_2( uintmax_t const x )
        { return uintmax__mul( x, 2 ); }
uintmax_t uintmax__div_2( uintmax_t const x )
        { return uintmax__div( x, 2 ); }
uintmax_t uintmax__mod_2( uintmax_t const x )
        { return uintmax__mod( x, 2 ); }


uintmax_t uintmax__mul_10( uintmax_t const x )
        { return uintmax__mul( x, 10 ); }
uintmax_t uintmax__div_10( uintmax_t const x )
        { return uintmax__div( x, 10 ); }


uintmax_t uintmax__add_b_2( uintmax_t const x )
        { return uintmax__add_b( x, 2 ); }
uintmax_t uintmax__sub_b_2( uintmax_t const x )
        { return uintmax__sub_b( x, 2 ); }
uintmax_t uintmax__mul_b_2( uintmax_t const x )
        { return uintmax__mul_b( x, 2 ); }
uintmax_t uintmax__mul_b_10( uintmax_t const x )
        { return uintmax__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

uintmax_t
uintmax__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    uintmax_t const x = strtoumax( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < uintmax__min_bound()
             || x > uintmax__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

