
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


#include "int16.h"

#include <libtypes/types.h>


int16_t int16__id( int16_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

int16_t int16__min_bound( void ) { return INT16_MIN; }
int16_t int16__max_bound( void ) { return INT16_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
int16__equal(
        int16_t const x,
        int16_t const y )
{
    return x == y;
}


bool
int16__not_equal(
        int16_t const x,
        int16_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
int16__compare(
        int16_t const x,
        int16_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
int16__less_than(
        int16_t const x,
        int16_t const y )
{
    return x < y;
}


bool
int16__less_than_or_eq(
        int16_t const x,
        int16_t const y )
{
    return x <= y;
}


bool
int16__greater_than_or_eq(
        int16_t const x,
        int16_t const y )
{
    return x >= y;
}


bool
int16__greater_than(
        int16_t const x,
        int16_t const y )
{
    return x > y;
}


int16_t
int16__min2(
        int16_t const x,
        int16_t const y )
{
    return ( x < y ) ? x : y;
}


int16_t
int16__max2(
        int16_t const x,
        int16_t const y )
{
    return ( x > y ) ? x : y;
}


int16_t
int16__min_n(
        size_t const n,
        int16_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int16_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = int16__min2( min, xs[ i ] );
    }
    return min;
}


int16_t
int16__max_n(
        size_t const n,
        int16_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int16_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = int16__max2( max, xs[ i ] );
    }
    return max;
}


int16_t
int16__clamp(
        int16_t const lower,
        int16_t const upper,
        int16_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


int16_t
int16__succ( int16_t const x )
{
    ASSERT( x != int16__max_bound() );

    return x + 1;
}


int16_t
int16__succ_b( int16_t const x )
{
    return ( x == int16__max_bound() ) ? x : ( x + 1 );
}


int16_t
int16__pred( int16_t const x )
{
    ASSERT( x != int16__min_bound() );

    return x - 1;
}


int16_t
int16__pred_b( int16_t const x )
{
    return ( x == int16__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool int16__is_signed( void ) { return true; }


bool
int16__add_would_underflow(
        int16_t const x,
        int16_t const y )
{
    return y < 0 && x < ( int16__min_bound() - y );
}


bool
int16__add_would_overflow(
        int16_t const x,
        int16_t const y )
{
    return y > 0 && x > ( int16__max_bound() - y );
}


bool
int16__can_add(
        int16_t const x,
        int16_t const y )
{
    return !int16__add_would_underflow( x, y )
        && !int16__add_would_overflow( x, y );
}


bool
int16__sub_would_underflow(
        int16_t const x,
        int16_t const y )
{
    return y > 0 && x < ( int16__min_bound() + y );
}


bool
int16__sub_would_overflow(
        int16_t const x,
        int16_t const y )
{
    return y < 0 && x > ( int16__max_bound() + y );
}


bool
int16__can_sub(
        int16_t const x,
        int16_t const y )
{
    return !int16__sub_would_underflow( x, y )
        && !int16__sub_would_overflow( x, y );
}


bool
int16__mul_would_underflow(
        int16_t const x,
        int16_t const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( int16__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( int16__min_bound() / y ) )
                              : false;
}


bool
int16__mul_would_overflow(
        int16_t const x,
        int16_t const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( int16__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( int16__max_bound() / x ) )
                              : false;
}


bool
int16__can_mul(
        int16_t const x,
        int16_t const y )
{
    return !int16__mul_would_underflow( x, y )
        && !int16__mul_would_overflow( x, y );
}


bool
int16__div_would_underflow(
        int16_t const x,
        int16_t const y )
{
    return false;
}


bool
int16__div_would_overflow(
        int16_t const x,
        int16_t const y )
{
    return x == int16__min_bound() && y == -1;
}


bool
int16__can_div(
        int16_t const x,
        int16_t const y )
{
    return ( y != 0 && !int16__div_would_overflow( x, y ) );
}


int16_t
int16__add(
        int16_t const x,
        int16_t const y )
{
    ASSERT( int16__can_add( x, y ) );

    return x + y;
}


int16_t
int16__sub(
        int16_t const x,
        int16_t const y )
{
    ASSERT( int16__can_sub( x, y ) );

    return x - y;
}


int16_t
int16__mul(
        int16_t const x,
        int16_t const y )
{
    ASSERT( int16__can_mul( x, y ) );

    return x * y;
}


int16_t
int16__div(
        int16_t const x,
        int16_t const y )
{
    ASSERT( int16__can_div( x, y ) );

    return x / y;
}


int16_t
int16__mod(
        int16_t const x,
        int16_t const y )
{
    ASSERT( int16__can_div( x, y ) );

    return x % y;
}


int16_t
int16__negate( int16_t const x )
{
    ASSERT( x != int16__min_bound() );

    return -x;
}


int16_t
int16__abs( int16_t const x )
{
    ASSERT( x != int16__min_bound() );

    return ( x < 0 ) ? -x : x;
}


int16_t
int16__add_b(
        int16_t const x,
        int16_t const y )
{
    if ( int16__add_would_underflow( x, y ) ) {
        return int16__min_bound();
    } else if ( int16__add_would_overflow( x, y ) ) {
        return int16__max_bound();
    } else {
        return x + y;
    }
}


int16_t
int16__sub_b(
        int16_t const x,
        int16_t const y )
{
    if ( int16__sub_would_underflow( x, y ) ) {
        return int16__min_bound();
    } else if ( int16__sub_would_overflow( x, y ) ) {
        return int16__max_bound();
    } else {
        return x - y;
    }
}


int16_t
int16__mul_b(
        int16_t const x,
        int16_t const y )
{
    if ( int16__mul_would_underflow( x, y ) ) {
        return int16__min_bound();
    } else if ( int16__mul_would_overflow( x, y ) ) {
        return int16__max_bound();
    } else {
        return x * y;
    }
}


int16_t
int16__div_b(
        int16_t const x,
        int16_t const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return int16__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return int16__max_bound();
        }
    } else if ( int16__div_would_underflow( x, y ) ) {
        return int16__min_bound();
    } else if ( int16__div_would_overflow( x, y ) ) {
        return int16__max_bound();
    } else {
        return x / y;
    }
}


int16_t
int16__mod_b(
        int16_t const x,
        int16_t const y )
{
    if ( !int16__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


int16_t
int16__negate_b( int16_t const x )
{
    if ( x == int16__min_bound() ) {
        return int16__max_bound();
    } else {
        return -x;
    }
}


int16_t
int16__abs_b( int16_t const x )
{
    if ( x == int16__min_bound() ) {
        return int16__max_bound();
    } else {
        return int16__abs( x );
    }
}


bool
int16__same_sign(
        int16_t const x,
        int16_t const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool int16__is_negative   ( int16_t const x ) { return x < 0; }
bool int16__is_nonpositive( int16_t const x ) { return x <= 0; }
bool int16__is_zero       ( int16_t const x ) { return x == 0; }
bool int16__is_nonzero    ( int16_t const x ) { return x != 0; }
bool int16__is_nonnegative( int16_t const x ) { return x >= 0; }
bool int16__is_positive   ( int16_t const x ) { return x > 0; }


ord
int16__compare_0( int16_t const x )
{
    return int16__compare( x, 0 );
}


bool int16__is_even( int16_t const x ) { return x % 2 == 0; }
bool int16__is_odd ( int16_t const x ) { return x % 2 == 1; }


int16_t int16__add_2( int16_t const x )
        { return int16__add( x, 2 ); }
int16_t int16__sub_2( int16_t const x )
        { return int16__sub( x, 2 ); }
int16_t int16__mul_2( int16_t const x )
        { return int16__mul( x, 2 ); }
int16_t int16__div_2( int16_t const x )
        { return int16__div( x, 2 ); }
int16_t int16__mod_2( int16_t const x )
        { return int16__mod( x, 2 ); }


int16_t int16__mul_10( int16_t const x )
        { return int16__mul( x, 10 ); }
int16_t int16__div_10( int16_t const x )
        { return int16__div( x, 10 ); }


int16_t int16__add_b_2( int16_t const x )
        { return int16__add_b( x, 2 ); }
int16_t int16__sub_b_2( int16_t const x )
        { return int16__sub_b( x, 2 ); }
int16_t int16__mul_b_2( int16_t const x )
        { return int16__mul_b( x, 2 ); }
int16_t int16__mul_b_10( int16_t const x )
        { return int16__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

int16_t
int16__from_str( char const * const str )
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
    } else if ( x < int16__min_bound()
             || x > int16__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

