
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


#include "long.h"

#include <libtypes/types.h>


long long__id( long const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

long long__min_bound( void ) { return LONG_MIN; }
long long__max_bound( void ) { return LONG_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
long__equal(
        long const x,
        long const y )
{
    return x == y;
}


bool
long__not_equal(
        long const x,
        long const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
long__compare(
        long const x,
        long const y )
{
    return ( x > y ) - ( x < y );
}


bool
long__less_than(
        long const x,
        long const y )
{
    return x < y;
}


bool
long__less_than_or_eq(
        long const x,
        long const y )
{
    return x <= y;
}


bool
long__greater_than_or_eq(
        long const x,
        long const y )
{
    return x >= y;
}


bool
long__greater_than(
        long const x,
        long const y )
{
    return x > y;
}


long
long__min2(
        long const x,
        long const y )
{
    return ( x < y ) ? x : y;
}


long
long__max2(
        long const x,
        long const y )
{
    return ( x > y ) ? x : y;
}


long
long__min_n(
        size_t const n,
        long const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    long min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = long__min2( min, xs[ i ] );
    }
    return min;
}


long
long__max_n(
        size_t const n,
        long const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    long max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = long__max2( max, xs[ i ] );
    }
    return max;
}


long
long__clamp(
        long const lower,
        long const upper,
        long const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
long__in_range(
        long const lower,
        long const upper,
        long const x )
{
    return lower <= x && x <= upper;
}


bool
long__in_range_x(
        long const lower,
        long const upper,
        long const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


long
long__succ( long const x )
{
    ASSERT( x != long__max_bound() );

    return x + 1;
}


long
long__succ_b( long const x )
{
    return ( x == long__max_bound() ) ? x : ( x + 1 );
}


long
long__pred( long const x )
{
    ASSERT( x != long__min_bound() );

    return x - 1;
}


long
long__pred_b( long const x )
{
    return ( x == long__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool long__is_signed( void ) { return true; }


bool
long__add_would_underflow(
        long const x,
        long const y )
{
    return y < 0 && x < ( long__min_bound() - y );
}


bool
long__add_would_overflow(
        long const x,
        long const y )
{
    return y > 0 && x > ( long__max_bound() - y );
}


bool
long__can_add(
        long const x,
        long const y )
{
    return !long__add_would_underflow( x, y )
        && !long__add_would_overflow( x, y );
}


bool
long__sub_would_underflow(
        long const x,
        long const y )
{
    return y > 0 && x < ( long__min_bound() + y );
}


bool
long__sub_would_overflow(
        long const x,
        long const y )
{
    return y < 0 && x > ( long__max_bound() + y );
}


bool
long__can_sub(
        long const x,
        long const y )
{
    return !long__sub_would_underflow( x, y )
        && !long__sub_would_overflow( x, y );
}


bool
long__mul_would_underflow(
        long const x,
        long const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( long__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( long__min_bound() / y ) )
                              : false;
}


bool
long__mul_would_overflow(
        long const x,
        long const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( long__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( long__max_bound() / x ) )
                              : false;
}


bool
long__can_mul(
        long const x,
        long const y )
{
    return !long__mul_would_underflow( x, y )
        && !long__mul_would_overflow( x, y );
}


bool
long__div_would_underflow(
        long const x,
        long const y )
{
    return false;
}


bool
long__div_would_overflow(
        long const x,
        long const y )
{
    return x == long__min_bound() && y == -1;
}


bool
long__can_div(
        long const x,
        long const y )
{
    return ( y != 0 && !long__div_would_overflow( x, y ) );
}


long
long__add(
        long const x,
        long const y )
{
    ASSERT( long__can_add( x, y ) );

    return x + y;
}


long
long__sub(
        long const x,
        long const y )
{
    ASSERT( long__can_sub( x, y ) );

    return x - y;
}


long
long__mul(
        long const x,
        long const y )
{
    ASSERT( long__can_mul( x, y ) );

    return x * y;
}


long
long__div(
        long const x,
        long const y )
{
    ASSERT( long__can_div( x, y ) );

    return x / y;
}


long
long__mod(
        long const x,
        long const y )
{
    ASSERT( long__can_div( x, y ) );

    return x % y;
}


long
long__negate( long const x )
{
    ASSERT( x != long__min_bound() );

    return -x;
}


long
long__abs( long const x )
{
    ASSERT( x != long__min_bound() );

    return ( x < 0 ) ? -x : x;
}


long
long__add_b(
        long const x,
        long const y )
{
    if ( long__add_would_underflow( x, y ) ) {
        return long__min_bound();
    } else if ( long__add_would_overflow( x, y ) ) {
        return long__max_bound();
    } else {
        return x + y;
    }
}


long
long__sub_b(
        long const x,
        long const y )
{
    if ( long__sub_would_underflow( x, y ) ) {
        return long__min_bound();
    } else if ( long__sub_would_overflow( x, y ) ) {
        return long__max_bound();
    } else {
        return x - y;
    }
}


long
long__mul_b(
        long const x,
        long const y )
{
    if ( long__mul_would_underflow( x, y ) ) {
        return long__min_bound();
    } else if ( long__mul_would_overflow( x, y ) ) {
        return long__max_bound();
    } else {
        return x * y;
    }
}


long
long__div_b(
        long const x,
        long const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return long__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return long__max_bound();
        }
    } else if ( long__div_would_underflow( x, y ) ) {
        return long__min_bound();
    } else if ( long__div_would_overflow( x, y ) ) {
        return long__max_bound();
    } else {
        return x / y;
    }
}


long
long__mod_b(
        long const x,
        long const y )
{
    if ( !long__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


long
long__negate_b( long const x )
{
    if ( x == long__min_bound() ) {
        return long__max_bound();
    } else {
        return -x;
    }
}


long
long__abs_b( long const x )
{
    if ( x == long__min_bound() ) {
        return long__max_bound();
    } else {
        return long__abs( x );
    }
}


bool
long__same_sign(
        long const x,
        long const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
long__in_delta(
        long const x,
        long const delta,
        long const y )
{
    return long__sub_b( x, delta ) <= y
        && y <= long__add_b( x, delta );
}


bool
long__in_delta_x(
        long const x,
        long const delta,
        long const y )
{
    return long__sub_b( x, delta ) < y
        && y < long__add_b( x, delta );
}


bool long__is_negative   ( long const x ) { return x < 0; }
bool long__is_nonpositive( long const x ) { return x <= 0; }
bool long__is_zero       ( long const x ) { return x == 0; }
bool long__is_nonzero    ( long const x ) { return x != 0; }
bool long__is_nonnegative( long const x ) { return x >= 0; }
bool long__is_positive   ( long const x ) { return x > 0; }


ord
long__compare_0( long const x )
{
    return long__compare( x, 0 );
}


bool long__is_even( long const x ) { return x % 2 == 0; }
bool long__is_odd ( long const x ) { return x % 2 == 1; }


long long__add_2( long const x )
        { return long__add( x, 2 ); }
long long__sub_2( long const x )
        { return long__sub( x, 2 ); }
long long__mul_2( long const x )
        { return long__mul( x, 2 ); }
long long__div_2( long const x )
        { return long__div( x, 2 ); }
long long__mod_2( long const x )
        { return long__mod( x, 2 ); }


long long__mul_10( long const x )
        { return long__mul( x, 10 ); }
long long__div_10( long const x )
        { return long__div( x, 10 ); }


long long__add_b_2( long const x )
        { return long__add_b( x, 2 ); }
long long__sub_b_2( long const x )
        { return long__sub_b( x, 2 ); }
long long__mul_b_2( long const x )
        { return long__mul_b( x, 2 ); }
long long__mul_b_10( long const x )
        { return long__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

long
long__from_str( char const * const str )
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
    } else if ( x < long__min_bound()
             || x > long__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

