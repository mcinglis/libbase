
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


#include "int8.h"

#include <libtypes/types.h>


int8_t int8__id( int8_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

int8_t int8__min_bound( void ) { return INT8_MIN; }
int8_t int8__max_bound( void ) { return INT8_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
int8__equal(
        int8_t const x,
        int8_t const y )
{
    return x == y;
}


bool
int8__not_equal(
        int8_t const x,
        int8_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
int8__compare(
        int8_t const x,
        int8_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
int8__less_than(
        int8_t const x,
        int8_t const y )
{
    return x < y;
}


bool
int8__less_than_or_eq(
        int8_t const x,
        int8_t const y )
{
    return x <= y;
}


bool
int8__greater_than_or_eq(
        int8_t const x,
        int8_t const y )
{
    return x >= y;
}


bool
int8__greater_than(
        int8_t const x,
        int8_t const y )
{
    return x > y;
}


int8_t
int8__min2(
        int8_t const x,
        int8_t const y )
{
    return ( x < y ) ? x : y;
}


int8_t
int8__max2(
        int8_t const x,
        int8_t const y )
{
    return ( x > y ) ? x : y;
}


int8_t
int8__min_n(
        size_t const n,
        int8_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int8_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = int8__min2( min, xs[ i ] );
    }
    return min;
}


int8_t
int8__max_n(
        size_t const n,
        int8_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int8_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = int8__max2( max, xs[ i ] );
    }
    return max;
}


int8_t
int8__clamp(
        int8_t const lower,
        int8_t const upper,
        int8_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
int8__in_range(
        int8_t const lower,
        int8_t const upper,
        int8_t const x )
{
    return lower <= x && x <= upper;
}


bool
int8__in_range_x(
        int8_t const lower,
        int8_t const upper,
        int8_t const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


int8_t
int8__succ( int8_t const x )
{
    ASSERT( x != int8__max_bound() );

    return x + 1;
}


int8_t
int8__succ_b( int8_t const x )
{
    return ( x == int8__max_bound() ) ? x : ( x + 1 );
}


int8_t
int8__pred( int8_t const x )
{
    ASSERT( x != int8__min_bound() );

    return x - 1;
}


int8_t
int8__pred_b( int8_t const x )
{
    return ( x == int8__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool int8__is_signed( void ) { return true; }


bool
int8__add_would_underflow(
        int8_t const x,
        int8_t const y )
{
    return y < 0 && x < ( int8__min_bound() - y );
}


bool
int8__add_would_overflow(
        int8_t const x,
        int8_t const y )
{
    return y > 0 && x > ( int8__max_bound() - y );
}


bool
int8__can_add(
        int8_t const x,
        int8_t const y )
{
    return !int8__add_would_underflow( x, y )
        && !int8__add_would_overflow( x, y );
}


bool
int8__sub_would_underflow(
        int8_t const x,
        int8_t const y )
{
    return y > 0 && x < ( int8__min_bound() + y );
}


bool
int8__sub_would_overflow(
        int8_t const x,
        int8_t const y )
{
    return y < 0 && x > ( int8__max_bound() + y );
}


bool
int8__can_sub(
        int8_t const x,
        int8_t const y )
{
    return !int8__sub_would_underflow( x, y )
        && !int8__sub_would_overflow( x, y );
}


bool
int8__mul_would_underflow(
        int8_t const x,
        int8_t const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( int8__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( int8__min_bound() / y ) )
                              : false;
}


bool
int8__mul_would_overflow(
        int8_t const x,
        int8_t const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( int8__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( int8__max_bound() / x ) )
                              : false;
}


bool
int8__can_mul(
        int8_t const x,
        int8_t const y )
{
    return !int8__mul_would_underflow( x, y )
        && !int8__mul_would_overflow( x, y );
}


bool
int8__div_would_underflow(
        int8_t const x,
        int8_t const y )
{
    return false;
}


bool
int8__div_would_overflow(
        int8_t const x,
        int8_t const y )
{
    return x == int8__min_bound() && y == -1;
}


bool
int8__can_div(
        int8_t const x,
        int8_t const y )
{
    return ( y != 0 && !int8__div_would_overflow( x, y ) );
}


int8_t
int8__add(
        int8_t const x,
        int8_t const y )
{
    ASSERT( int8__can_add( x, y ) );

    return x + y;
}


int8_t
int8__sub(
        int8_t const x,
        int8_t const y )
{
    ASSERT( int8__can_sub( x, y ) );

    return x - y;
}


int8_t
int8__mul(
        int8_t const x,
        int8_t const y )
{
    ASSERT( int8__can_mul( x, y ) );

    return x * y;
}


int8_t
int8__div(
        int8_t const x,
        int8_t const y )
{
    ASSERT( int8__can_div( x, y ) );

    return x / y;
}


int8_t
int8__mod(
        int8_t const x,
        int8_t const y )
{
    ASSERT( int8__can_div( x, y ) );

    return x % y;
}


int8_t
int8__negate( int8_t const x )
{
    ASSERT( x != int8__min_bound() );

    return -x;
}


int8_t
int8__abs( int8_t const x )
{
    ASSERT( x != int8__min_bound() );

    return ( x < 0 ) ? -x : x;
}


int8_t
int8__add_b(
        int8_t const x,
        int8_t const y )
{
    if ( int8__add_would_underflow( x, y ) ) {
        return int8__min_bound();
    } else if ( int8__add_would_overflow( x, y ) ) {
        return int8__max_bound();
    } else {
        return x + y;
    }
}


int8_t
int8__sub_b(
        int8_t const x,
        int8_t const y )
{
    if ( int8__sub_would_underflow( x, y ) ) {
        return int8__min_bound();
    } else if ( int8__sub_would_overflow( x, y ) ) {
        return int8__max_bound();
    } else {
        return x - y;
    }
}


int8_t
int8__mul_b(
        int8_t const x,
        int8_t const y )
{
    if ( int8__mul_would_underflow( x, y ) ) {
        return int8__min_bound();
    } else if ( int8__mul_would_overflow( x, y ) ) {
        return int8__max_bound();
    } else {
        return x * y;
    }
}


int8_t
int8__div_b(
        int8_t const x,
        int8_t const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return int8__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return int8__max_bound();
        }
    } else if ( int8__div_would_underflow( x, y ) ) {
        return int8__min_bound();
    } else if ( int8__div_would_overflow( x, y ) ) {
        return int8__max_bound();
    } else {
        return x / y;
    }
}


int8_t
int8__mod_b(
        int8_t const x,
        int8_t const y )
{
    if ( !int8__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


int8_t
int8__negate_b( int8_t const x )
{
    if ( x == int8__min_bound() ) {
        return int8__max_bound();
    } else {
        return -x;
    }
}


int8_t
int8__abs_b( int8_t const x )
{
    if ( x == int8__min_bound() ) {
        return int8__max_bound();
    } else {
        return int8__abs( x );
    }
}


bool
int8__same_sign(
        int8_t const x,
        int8_t const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
int8__in_delta(
        int8_t const x,
        int8_t const delta,
        int8_t const y )
{
    return int8__sub_b( x, delta ) <= y
        && y <= int8__add_b( x, delta );
}


bool
int8__in_delta_x(
        int8_t const x,
        int8_t const delta,
        int8_t const y )
{
    return int8__sub_b( x, delta ) < y
        && y < int8__add_b( x, delta );
}


bool int8__is_negative   ( int8_t const x ) { return x < 0; }
bool int8__is_nonpositive( int8_t const x ) { return x <= 0; }
bool int8__is_zero       ( int8_t const x ) { return x == 0; }
bool int8__is_nonzero    ( int8_t const x ) { return x != 0; }
bool int8__is_nonnegative( int8_t const x ) { return x >= 0; }
bool int8__is_positive   ( int8_t const x ) { return x > 0; }


ord
int8__compare_0( int8_t const x )
{
    return int8__compare( x, 0 );
}


bool int8__is_even( int8_t const x ) { return x % 2 == 0; }
bool int8__is_odd ( int8_t const x ) { return x % 2 == 1; }


int8_t int8__add_2( int8_t const x )
        { return int8__add( x, 2 ); }
int8_t int8__sub_2( int8_t const x )
        { return int8__sub( x, 2 ); }
int8_t int8__mul_2( int8_t const x )
        { return int8__mul( x, 2 ); }
int8_t int8__div_2( int8_t const x )
        { return int8__div( x, 2 ); }
int8_t int8__mod_2( int8_t const x )
        { return int8__mod( x, 2 ); }


int8_t int8__mul_10( int8_t const x )
        { return int8__mul( x, 10 ); }
int8_t int8__div_10( int8_t const x )
        { return int8__div( x, 10 ); }


int8_t int8__add_b_2( int8_t const x )
        { return int8__add_b( x, 2 ); }
int8_t int8__sub_b_2( int8_t const x )
        { return int8__sub_b( x, 2 ); }
int8_t int8__mul_b_2( int8_t const x )
        { return int8__mul_b( x, 2 ); }
int8_t int8__mul_b_10( int8_t const x )
        { return int8__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

int8_t
int8__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    long const x = strtol( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < int8__min_bound()
             || x > int8__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

