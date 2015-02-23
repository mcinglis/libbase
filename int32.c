
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


#include "int32.h"

#include <libtypes/types.h>


int32_t int32__id( int32_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

int32_t int32__min_bound( void ) { return INT32_MIN; }
int32_t int32__max_bound( void ) { return INT32_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
int32__equal(
        int32_t const x,
        int32_t const y )
{
    return x == y;
}


bool
int32__not_equal(
        int32_t const x,
        int32_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
int32__compare(
        int32_t const x,
        int32_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
int32__less_than(
        int32_t const x,
        int32_t const y )
{
    return x < y;
}


bool
int32__less_than_or_eq(
        int32_t const x,
        int32_t const y )
{
    return x <= y;
}


bool
int32__greater_than_or_eq(
        int32_t const x,
        int32_t const y )
{
    return x >= y;
}


bool
int32__greater_than(
        int32_t const x,
        int32_t const y )
{
    return x > y;
}


int32_t
int32__min2(
        int32_t const x,
        int32_t const y )
{
    return ( x < y ) ? x : y;
}


int32_t
int32__max2(
        int32_t const x,
        int32_t const y )
{
    return ( x > y ) ? x : y;
}


int32_t
int32__min_n(
        size_t const n,
        int32_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int32_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = int32__min2( min, xs[ i ] );
    }
    return min;
}


int32_t
int32__max_n(
        size_t const n,
        int32_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int32_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = int32__max2( max, xs[ i ] );
    }
    return max;
}


int32_t
int32__clamp(
        int32_t const lower,
        int32_t const upper,
        int32_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
int32__in_range(
        int32_t const lower,
        int32_t const upper,
        int32_t const x )
{
    return lower <= x && x <= upper;
}


bool
int32__in_range_x(
        int32_t const lower,
        int32_t const upper,
        int32_t const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


int32_t
int32__succ( int32_t const x )
{
    ASSERT( x != int32__max_bound() );

    return x + 1;
}


int32_t
int32__succ_b( int32_t const x )
{
    return ( x == int32__max_bound() ) ? x : ( x + 1 );
}


int32_t
int32__pred( int32_t const x )
{
    ASSERT( x != int32__min_bound() );

    return x - 1;
}


int32_t
int32__pred_b( int32_t const x )
{
    return ( x == int32__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool int32__is_signed( void ) { return true; }


bool
int32__add_would_underflow(
        int32_t const x,
        int32_t const y )
{
    return y < 0 && x < ( int32__min_bound() - y );
}


bool
int32__add_would_overflow(
        int32_t const x,
        int32_t const y )
{
    return y > 0 && x > ( int32__max_bound() - y );
}


bool
int32__can_add(
        int32_t const x,
        int32_t const y )
{
    return !int32__add_would_underflow( x, y )
        && !int32__add_would_overflow( x, y );
}


bool
int32__sub_would_underflow(
        int32_t const x,
        int32_t const y )
{
    return y > 0 && x < ( int32__min_bound() + y );
}


bool
int32__sub_would_overflow(
        int32_t const x,
        int32_t const y )
{
    return y < 0 && x > ( int32__max_bound() + y );
}


bool
int32__can_sub(
        int32_t const x,
        int32_t const y )
{
    return !int32__sub_would_underflow( x, y )
        && !int32__sub_would_overflow( x, y );
}


bool
int32__mul_would_underflow(
        int32_t const x,
        int32_t const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( int32__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( int32__min_bound() / y ) )
                              : false;
}


bool
int32__mul_would_overflow(
        int32_t const x,
        int32_t const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( int32__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( int32__max_bound() / x ) )
                              : false;
}


bool
int32__can_mul(
        int32_t const x,
        int32_t const y )
{
    return !int32__mul_would_underflow( x, y )
        && !int32__mul_would_overflow( x, y );
}


bool
int32__div_would_underflow(
        int32_t const x,
        int32_t const y )
{
    return false;
}


bool
int32__div_would_overflow(
        int32_t const x,
        int32_t const y )
{
    return x == int32__min_bound() && y == -1;
}


bool
int32__can_div(
        int32_t const x,
        int32_t const y )
{
    return ( y != 0 && !int32__div_would_overflow( x, y ) );
}


int32_t
int32__add(
        int32_t const x,
        int32_t const y )
{
    ASSERT( int32__can_add( x, y ) );

    return x + y;
}


int32_t
int32__sub(
        int32_t const x,
        int32_t const y )
{
    ASSERT( int32__can_sub( x, y ) );

    return x - y;
}


int32_t
int32__mul(
        int32_t const x,
        int32_t const y )
{
    ASSERT( int32__can_mul( x, y ) );

    return x * y;
}


int32_t
int32__div(
        int32_t const x,
        int32_t const y )
{
    ASSERT( int32__can_div( x, y ) );

    return x / y;
}


int32_t
int32__mod(
        int32_t const x,
        int32_t const y )
{
    ASSERT( int32__can_div( x, y ) );

    return x % y;
}


int32_t
int32__negate( int32_t const x )
{
    ASSERT( x != int32__min_bound() );

    return -x;
}


int32_t
int32__abs( int32_t const x )
{
    ASSERT( x != int32__min_bound() );

    return ( x < 0 ) ? -x : x;
}


int32_t
int32__add_b(
        int32_t const x,
        int32_t const y )
{
    if ( int32__add_would_underflow( x, y ) ) {
        return int32__min_bound();
    } else if ( int32__add_would_overflow( x, y ) ) {
        return int32__max_bound();
    } else {
        return x + y;
    }
}


int32_t
int32__sub_b(
        int32_t const x,
        int32_t const y )
{
    if ( int32__sub_would_underflow( x, y ) ) {
        return int32__min_bound();
    } else if ( int32__sub_would_overflow( x, y ) ) {
        return int32__max_bound();
    } else {
        return x - y;
    }
}


int32_t
int32__mul_b(
        int32_t const x,
        int32_t const y )
{
    if ( int32__mul_would_underflow( x, y ) ) {
        return int32__min_bound();
    } else if ( int32__mul_would_overflow( x, y ) ) {
        return int32__max_bound();
    } else {
        return x * y;
    }
}


int32_t
int32__div_b(
        int32_t const x,
        int32_t const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return int32__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return int32__max_bound();
        }
    } else if ( int32__div_would_underflow( x, y ) ) {
        return int32__min_bound();
    } else if ( int32__div_would_overflow( x, y ) ) {
        return int32__max_bound();
    } else {
        return x / y;
    }
}


int32_t
int32__mod_b(
        int32_t const x,
        int32_t const y )
{
    if ( !int32__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


int32_t
int32__negate_b( int32_t const x )
{
    if ( x == int32__min_bound() ) {
        return int32__max_bound();
    } else {
        return -x;
    }
}


int32_t
int32__abs_b( int32_t const x )
{
    if ( x == int32__min_bound() ) {
        return int32__max_bound();
    } else {
        return int32__abs( x );
    }
}


bool
int32__same_sign(
        int32_t const x,
        int32_t const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
int32__in_delta(
        int32_t const x,
        int32_t const delta,
        int32_t const y )
{
    return int32__sub_b( x, delta ) <= y
        && y <= int32__add_b( x, delta );
}


bool
int32__in_delta_x(
        int32_t const x,
        int32_t const delta,
        int32_t const y )
{
    return int32__sub_b( x, delta ) < y
        && y < int32__add_b( x, delta );
}


bool int32__is_negative   ( int32_t const x ) { return x < 0; }
bool int32__is_nonpositive( int32_t const x ) { return x <= 0; }
bool int32__is_zero       ( int32_t const x ) { return x == 0; }
bool int32__is_nonzero    ( int32_t const x ) { return x != 0; }
bool int32__is_nonnegative( int32_t const x ) { return x >= 0; }
bool int32__is_positive   ( int32_t const x ) { return x > 0; }


ord
int32__compare_0( int32_t const x )
{
    return int32__compare( x, 0 );
}


bool int32__is_even( int32_t const x ) { return x % 2 == 0; }
bool int32__is_odd ( int32_t const x ) { return x % 2 == 1; }


int32_t int32__add_2( int32_t const x )
        { return int32__add( x, 2 ); }
int32_t int32__sub_2( int32_t const x )
        { return int32__sub( x, 2 ); }
int32_t int32__mul_2( int32_t const x )
        { return int32__mul( x, 2 ); }
int32_t int32__div_2( int32_t const x )
        { return int32__div( x, 2 ); }
int32_t int32__mod_2( int32_t const x )
        { return int32__mod( x, 2 ); }


int32_t int32__mul_10( int32_t const x )
        { return int32__mul( x, 10 ); }
int32_t int32__div_10( int32_t const x )
        { return int32__div( x, 10 ); }


int32_t int32__add_b_2( int32_t const x )
        { return int32__add_b( x, 2 ); }
int32_t int32__sub_b_2( int32_t const x )
        { return int32__sub_b( x, 2 ); }
int32_t int32__mul_b_2( int32_t const x )
        { return int32__mul_b( x, 2 ); }
int32_t int32__mul_b_10( int32_t const x )
        { return int32__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

int32_t
int32__from_str( char const * const str )
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
    } else if ( x < int32__min_bound()
             || x > int32__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

