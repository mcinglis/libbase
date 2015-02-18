
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


#include "int.h"

#include <libtypes/types.h>


int int__id( int const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

int int__min_bound( void ) { return INT_MIN; }
int int__max_bound( void ) { return INT_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
int__equal(
        int const x,
        int const y )
{
    return x == y;
}


bool
int__not_equal(
        int const x,
        int const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
int__compare(
        int const x,
        int const y )
{
    return ( x > y ) - ( x < y );
}


bool
int__less_than(
        int const x,
        int const y )
{
    return x < y;
}


bool
int__less_than_or_eq(
        int const x,
        int const y )
{
    return x <= y;
}


bool
int__greater_than_or_eq(
        int const x,
        int const y )
{
    return x >= y;
}


bool
int__greater_than(
        int const x,
        int const y )
{
    return x > y;
}


int
int__min2(
        int const x,
        int const y )
{
    return ( x < y ) ? x : y;
}


int
int__max2(
        int const x,
        int const y )
{
    return ( x > y ) ? x : y;
}


int
int__min_n(
        size_t const n,
        int const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = int__min2( min, xs[ i ] );
    }
    return min;
}


int
int__max_n(
        size_t const n,
        int const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    int max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = int__max2( max, xs[ i ] );
    }
    return max;
}


int
int__clamp(
        int const lower,
        int const upper,
        int const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


int
int__succ( int const x )
{
    ASSERT( x != int__max_bound() );

    return x + 1;
}


int
int__succ_b( int const x )
{
    return ( x == int__max_bound() ) ? x : ( x + 1 );
}


int
int__pred( int const x )
{
    ASSERT( x != int__min_bound() );

    return x - 1;
}


int
int__pred_b( int const x )
{
    return ( x == int__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool int__is_signed( void ) { return true; }


bool
int__add_would_underflow(
        int const x,
        int const y )
{
    return y < 0 && x < ( int__min_bound() - y );
}


bool
int__add_would_overflow(
        int const x,
        int const y )
{
    return y > 0 && x > ( int__max_bound() - y );
}


bool
int__can_add(
        int const x,
        int const y )
{
    return !int__add_would_underflow( x, y )
        && !int__add_would_overflow( x, y );
}


bool
int__sub_would_underflow(
        int const x,
        int const y )
{
    return y > 0 && x < ( int__min_bound() + y );
}


bool
int__sub_would_overflow(
        int const x,
        int const y )
{
    return y < 0 && x > ( int__max_bound() + y );
}


bool
int__can_sub(
        int const x,
        int const y )
{
    return !int__sub_would_underflow( x, y )
        && !int__sub_would_overflow( x, y );
}


bool
int__mul_would_underflow(
        int const x,
        int const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( int__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( int__min_bound() / y ) )
                              : false;
}


bool
int__mul_would_overflow(
        int const x,
        int const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( int__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( int__max_bound() / x ) )
                              : false;
}


bool
int__can_mul(
        int const x,
        int const y )
{
    return !int__mul_would_underflow( x, y )
        && !int__mul_would_overflow( x, y );
}


bool
int__div_would_underflow(
        int const x,
        int const y )
{
    return false;
}


bool
int__div_would_overflow(
        int const x,
        int const y )
{
    return x == int__min_bound() && y == -1;
}


bool
int__can_div(
        int const x,
        int const y )
{
    return ( y != 0 && !int__div_would_overflow( x, y ) );
}


int
int__add(
        int const x,
        int const y )
{
    ASSERT( int__can_add( x, y ) );

    return x + y;
}


int
int__sub(
        int const x,
        int const y )
{
    ASSERT( int__can_sub( x, y ) );

    return x - y;
}


int
int__mul(
        int const x,
        int const y )
{
    ASSERT( int__can_mul( x, y ) );

    return x * y;
}


int
int__div(
        int const x,
        int const y )
{
    ASSERT( int__can_div( x, y ) );

    return x / y;
}


int
int__mod(
        int const x,
        int const y )
{
    ASSERT( int__can_div( x, y ) );

    return x % y;
}


int
int__negate( int const x )
{
    ASSERT( x != int__min_bound() );

    return -x;
}


int
int__abs( int const x )
{
    ASSERT( x != int__min_bound() );

    return ( x < 0 ) ? -x : x;
}


int
int__add_b(
        int const x,
        int const y )
{
    if ( int__add_would_underflow( x, y ) ) {
        return int__min_bound();
    } else if ( int__add_would_overflow( x, y ) ) {
        return int__max_bound();
    } else {
        return x + y;
    }
}


int
int__sub_b(
        int const x,
        int const y )
{
    if ( int__sub_would_underflow( x, y ) ) {
        return int__min_bound();
    } else if ( int__sub_would_overflow( x, y ) ) {
        return int__max_bound();
    } else {
        return x - y;
    }
}


int
int__mul_b(
        int const x,
        int const y )
{
    if ( int__mul_would_underflow( x, y ) ) {
        return int__min_bound();
    } else if ( int__mul_would_overflow( x, y ) ) {
        return int__max_bound();
    } else {
        return x * y;
    }
}


int
int__div_b(
        int const x,
        int const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return int__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return int__max_bound();
        }
    } else if ( int__div_would_underflow( x, y ) ) {
        return int__min_bound();
    } else if ( int__div_would_overflow( x, y ) ) {
        return int__max_bound();
    } else {
        return x / y;
    }
}


int
int__mod_b(
        int const x,
        int const y )
{
    if ( !int__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


int
int__negate_b( int const x )
{
    if ( x == int__min_bound() ) {
        return int__max_bound();
    } else {
        return -x;
    }
}


int
int__abs_b( int const x )
{
    if ( x == int__min_bound() ) {
        return int__max_bound();
    } else {
        return int__abs( x );
    }
}


bool
int__same_sign(
        int const x,
        int const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool int__is_negative   ( int const x ) { return x < 0; }
bool int__is_nonpositive( int const x ) { return x <= 0; }
bool int__is_zero       ( int const x ) { return x == 0; }
bool int__is_nonnegative( int const x ) { return x >= 0; }
bool int__is_positive   ( int const x ) { return x > 0; }


ord
int__compare_0( int const x )
{
    return int__compare( x, 0 );
}


bool int__is_even( int const x ) { return x % 2 == 0; }
bool int__is_odd ( int const x ) { return x % 2 == 1; }


int int__add_2( int const x )
        { return int__add( x, 2 ); }
int int__sub_2( int const x )
        { return int__sub( x, 2 ); }
int int__mul_2( int const x )
        { return int__mul( x, 2 ); }
int int__div_2( int const x )
        { return int__div( x, 2 ); }
int int__mod_2( int const x )
        { return int__mod( x, 2 ); }


int int__mul_10( int const x )
        { return int__mul( x, 10 ); }
int int__div_10( int const x )
        { return int__div( x, 10 ); }


int int__add_b_2( int const x )
        { return int__add_b( x, 2 ); }
int int__sub_b_2( int const x )
        { return int__sub_b( x, 2 ); }
int int__mul_b_2( int const x )
        { return int__mul_b( x, 2 ); }
int int__mul_b_10( int const x )
        { return int__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

int
int__from_str( char const * const str )
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
    } else if ( x < int__min_bound()
             || x > int__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

