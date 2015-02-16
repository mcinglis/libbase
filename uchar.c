
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


#include "uchar.h"

#include <libtypes/types.h>


uchar uchar__id( uchar const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

uchar uchar__min_bound( void ) { return 0; }
uchar uchar__max_bound( void ) { return UCHAR_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
uchar__equal(
        uchar const x,
        uchar const y )
{
    return x == y;
}


bool
uchar__not_equal(
        uchar const x,
        uchar const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
uchar__compare(
        uchar const x,
        uchar const y )
{
    return ( x > y ) - ( x < y );
}


bool
uchar__less_than(
        uchar const x,
        uchar const y )
{
    return x < y;
}


bool
uchar__less_than_or_eq(
        uchar const x,
        uchar const y )
{
    return x <= y;
}


bool
uchar__greater_than_or_eq(
        uchar const x,
        uchar const y )
{
    return x >= y;
}


bool
uchar__greater_than(
        uchar const x,
        uchar const y )
{
    return x > y;
}


uchar
uchar__min2(
        uchar const x,
        uchar const y )
{
    return ( x < y ) ? x : y;
}


uchar
uchar__max2(
        uchar const x,
        uchar const y )
{
    return ( x > y ) ? x : y;
}


uchar
uchar__min_n(
        size_t const n,
        uchar const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uchar min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = uchar__min2( min, xs[ i ] );
    }
    return min;
}


uchar
uchar__max_n(
        size_t const n,
        uchar const * const xs )
{ ASSERT( n != 0, xs != NULL );
    uchar max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = uchar__max2( max, xs[ i ] );
    }
    return max;
}


uchar
uchar__clamp(
        uchar const lower,
        uchar const upper,
        uchar const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


uchar
uchar__succ( uchar const x )
{ ASSERT( x != uchar__max_bound() );
    return x + 1;
}


uchar
uchar__succ_b( uchar const x )
{
    return ( x == uchar__max_bound() ) ? x : ( x + 1 );
}


uchar
uchar__pred( uchar const x )
{ ASSERT( x != uchar__min_bound() );
    return x - 1;
}


uchar
uchar__pred_b( uchar const x )
{
    return ( x == uchar__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool uchar__is_signed( void ) { return false; }


bool
uchar__add_would_underflow(
        uchar const x,
        uchar const y )
{
    return false;
}


bool
uchar__add_would_overflow(
        uchar const x,
        uchar const y )
{
    return ( x > ( uchar__max_bound() - y ) );
}


bool
uchar__can_add(
        uchar const x,
        uchar const y )
{
    return !uchar__add_would_overflow( x, y );
}


bool
uchar__sub_would_underflow(
        uchar const x,
        uchar const y )
{
    return ( x < y );
}


bool
uchar__sub_would_overflow(
        uchar const x,
        uchar const y )
{
    return false;
}


bool
uchar__can_sub(
        uchar const x,
        uchar const y )
{
    return !uchar__sub_would_underflow( x, y );
}


bool
uchar__mul_would_underflow(
        uchar const x,
        uchar const y )
{
    return false;
}


bool
uchar__mul_would_overflow(
        uchar const x,
        uchar const y )
{
    return ( x > ( uchar__max_bound() / y ) );
}


bool
uchar__can_mul(
        uchar const x,
        uchar const y )
{
    return !uchar__mul_would_overflow( x, y );
}


bool
uchar__div_would_underflow(
        uchar const x,
        uchar const y )
{
    return false;
}


bool
uchar__div_would_overflow(
        uchar const x,
        uchar const y )
{
    return false;
}


bool
uchar__can_div(
        uchar const x,
        uchar const y )
{
    return y != 0;
}


uchar
uchar__add(
        uchar const x,
        uchar const y )
{
    return x + y;
}


uchar
uchar__sub(
        uchar const x,
        uchar const y )
{
    return x - y;
}


uchar
uchar__mul(
        uchar const x,
        uchar const y )
{
    return x * y;
}


uchar
uchar__div(
        uchar const x,
        uchar const y )
{ ASSERT( y != 0 );
    return x / y;
}


uchar
uchar__mod(
        uchar const x,
        uchar const y )
{ ASSERT( y != 0 );
    return x % y;
}


uchar
uchar__negate( uchar const x )
{
    return -x;
}


uchar
uchar__abs( uchar const x )
{
    return x;
}


uchar
uchar__add_b(
        uchar const x,
        uchar const y )
{
    if ( uchar__add_would_overflow( x, y ) ) {
        return uchar__max_bound();
    } else {
        return x + y;
    }
}


uchar
uchar__sub_b(
        uchar const x,
        uchar const y )
{
    if ( uchar__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


uchar
uchar__mul_b(
        uchar const x,
        uchar const y )
{
    if ( uchar__mul_would_overflow( x, y ) ) {
        return uchar__max_bound();
    } else {
        return x * y;
    }
}


uchar
uchar__div_b(
        uchar const x,
        uchar const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return uchar__max_bound();
        }
    } else {
        return x / y;
    }
}


uchar
uchar__mod_b(
        uchar const x,
        uchar const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


uchar
uchar__negate_b( uchar const x )
{
    return uchar__negate( x );
}


uchar
uchar__abs_b( uchar const x )
{
    return uchar__abs( x );
}


bool
uchar__same_sign(
        uchar const x,
        uchar const y )
{
    return true;
}


bool uchar__is_negative   ( uchar const x ) { return false; }
bool uchar__is_nonpositive( uchar const x ) { return x == 0; }
bool uchar__is_zero       ( uchar const x ) { return x == 0; }
bool uchar__is_nonnegative( uchar const x ) { return true; }
bool uchar__is_positive   ( uchar const x ) { return x != 0; }


ord
uchar__compare_0( uchar const x )
{
    return uchar__compare( x, 0 );
}


bool uchar__is_even( uchar const x ) { return x % 2 == 0; }
bool uchar__is_odd ( uchar const x ) { return x % 2 == 1; }


uchar uchar__add_2( uchar const x )
        { return uchar__add( x, 2 ); }
uchar uchar__sub_2( uchar const x )
        { return uchar__sub( x, 2 ); }
uchar uchar__mul_2( uchar const x )
        { return uchar__mul( x, 2 ); }
uchar uchar__div_2( uchar const x )
        { return uchar__div( x, 2 ); }
uchar uchar__mod_2( uchar const x )
        { return uchar__mod( x, 2 ); }


uchar uchar__mul_10( uchar const x )
        { return uchar__mul( x, 10 ); }
uchar uchar__div_10( uchar const x )
        { return uchar__div( x, 10 ); }


uchar uchar__add_b_2( uchar const x )
        { return uchar__add_b( x, 2 ); }
uchar uchar__sub_b_2( uchar const x )
        { return uchar__sub_b( x, 2 ); }
uchar uchar__mul_b_2( uchar const x )
        { return uchar__mul_b( x, 2 ); }
uchar uchar__mul_b_10( uchar const x )
        { return uchar__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

uchar
uchar__from_str( char const * const str )
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
    } else if ( x < uchar__min_bound()
             || x > uchar__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

