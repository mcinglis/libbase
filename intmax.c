
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


#include "intmax.h"

#include <libtypes/types.h>


intmax_t intmax__id( intmax_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

intmax_t intmax__min_bound( void ) { return INTMAX_MIN; }
intmax_t intmax__max_bound( void ) { return INTMAX_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
intmax__equal(
        intmax_t const x,
        intmax_t const y )
{
    return x == y;
}


bool
intmax__not_equal(
        intmax_t const x,
        intmax_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
intmax__compare(
        intmax_t const x,
        intmax_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
intmax__less_than(
        intmax_t const x,
        intmax_t const y )
{
    return x < y;
}


bool
intmax__less_than_or_eq(
        intmax_t const x,
        intmax_t const y )
{
    return x <= y;
}


bool
intmax__greater_than_or_eq(
        intmax_t const x,
        intmax_t const y )
{
    return x >= y;
}


bool
intmax__greater_than(
        intmax_t const x,
        intmax_t const y )
{
    return x > y;
}


intmax_t
intmax__min2(
        intmax_t const x,
        intmax_t const y )
{
    return ( x < y ) ? x : y;
}


intmax_t
intmax__max2(
        intmax_t const x,
        intmax_t const y )
{
    return ( x > y ) ? x : y;
}


intmax_t
intmax__min_n(
        size_t const n,
        intmax_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    intmax_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = intmax__min2( min, xs[ i ] );
    }
    return min;
}


intmax_t
intmax__max_n(
        size_t const n,
        intmax_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    intmax_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = intmax__max2( max, xs[ i ] );
    }
    return max;
}


intmax_t
intmax__clamp(
        intmax_t const lower,
        intmax_t const upper,
        intmax_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
intmax__in_range(
        intmax_t const lower,
        intmax_t const upper,
        intmax_t const x )
{
    return lower <= x && x <= upper;
}


bool
intmax__in_range_x(
        intmax_t const lower,
        intmax_t const upper,
        intmax_t const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


intmax_t
intmax__succ( intmax_t const x )
{
    ASSERT( x != intmax__max_bound() );

    return x + 1;
}


intmax_t
intmax__succ_b( intmax_t const x )
{
    return ( x == intmax__max_bound() ) ? x : ( x + 1 );
}


intmax_t
intmax__pred( intmax_t const x )
{
    ASSERT( x != intmax__min_bound() );

    return x - 1;
}


intmax_t
intmax__pred_b( intmax_t const x )
{
    return ( x == intmax__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool intmax__is_signed( void ) { return true; }


bool
intmax__add_would_underflow(
        intmax_t const x,
        intmax_t const y )
{
    return y < 0 && x < ( intmax__min_bound() - y );
}


bool
intmax__add_would_overflow(
        intmax_t const x,
        intmax_t const y )
{
    return y > 0 && x > ( intmax__max_bound() - y );
}


bool
intmax__can_add(
        intmax_t const x,
        intmax_t const y )
{
    return !intmax__add_would_underflow( x, y )
        && !intmax__add_would_overflow( x, y );
}


bool
intmax__sub_would_underflow(
        intmax_t const x,
        intmax_t const y )
{
    return y > 0 && x < ( intmax__min_bound() + y );
}


bool
intmax__sub_would_overflow(
        intmax_t const x,
        intmax_t const y )
{
    return y < 0 && x > ( intmax__max_bound() + y );
}


bool
intmax__can_sub(
        intmax_t const x,
        intmax_t const y )
{
    return !intmax__sub_would_underflow( x, y )
        && !intmax__sub_would_overflow( x, y );
}


bool
intmax__mul_would_underflow(
        intmax_t const x,
        intmax_t const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( intmax__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( intmax__min_bound() / y ) )
                              : false;
}


bool
intmax__mul_would_overflow(
        intmax_t const x,
        intmax_t const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( intmax__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( intmax__max_bound() / x ) )
                              : false;
}


bool
intmax__can_mul(
        intmax_t const x,
        intmax_t const y )
{
    return !intmax__mul_would_underflow( x, y )
        && !intmax__mul_would_overflow( x, y );
}


bool
intmax__div_would_underflow(
        intmax_t const x,
        intmax_t const y )
{
    return false;
}


bool
intmax__div_would_overflow(
        intmax_t const x,
        intmax_t const y )
{
    return x == intmax__min_bound() && y == -1;
}


bool
intmax__can_div(
        intmax_t const x,
        intmax_t const y )
{
    return ( y != 0 && !intmax__div_would_overflow( x, y ) );
}


intmax_t
intmax__add(
        intmax_t const x,
        intmax_t const y )
{
    ASSERT( intmax__can_add( x, y ) );

    return x + y;
}


intmax_t
intmax__sub(
        intmax_t const x,
        intmax_t const y )
{
    ASSERT( intmax__can_sub( x, y ) );

    return x - y;
}


intmax_t
intmax__mul(
        intmax_t const x,
        intmax_t const y )
{
    ASSERT( intmax__can_mul( x, y ) );

    return x * y;
}


intmax_t
intmax__div(
        intmax_t const x,
        intmax_t const y )
{
    ASSERT( intmax__can_div( x, y ) );

    return x / y;
}


intmax_t
intmax__mod(
        intmax_t const x,
        intmax_t const y )
{
    ASSERT( intmax__can_div( x, y ) );

    return x % y;
}


intmax_t
intmax__negate( intmax_t const x )
{
    ASSERT( x != intmax__min_bound() );

    return -x;
}


intmax_t
intmax__abs( intmax_t const x )
{
    ASSERT( x != intmax__min_bound() );

    return ( x < 0 ) ? -x : x;
}


intmax_t
intmax__add_b(
        intmax_t const x,
        intmax_t const y )
{
    if ( intmax__add_would_underflow( x, y ) ) {
        return intmax__min_bound();
    } else if ( intmax__add_would_overflow( x, y ) ) {
        return intmax__max_bound();
    } else {
        return x + y;
    }
}


intmax_t
intmax__sub_b(
        intmax_t const x,
        intmax_t const y )
{
    if ( intmax__sub_would_underflow( x, y ) ) {
        return intmax__min_bound();
    } else if ( intmax__sub_would_overflow( x, y ) ) {
        return intmax__max_bound();
    } else {
        return x - y;
    }
}


intmax_t
intmax__mul_b(
        intmax_t const x,
        intmax_t const y )
{
    if ( intmax__mul_would_underflow( x, y ) ) {
        return intmax__min_bound();
    } else if ( intmax__mul_would_overflow( x, y ) ) {
        return intmax__max_bound();
    } else {
        return x * y;
    }
}


intmax_t
intmax__div_b(
        intmax_t const x,
        intmax_t const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return intmax__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return intmax__max_bound();
        }
    } else if ( intmax__div_would_underflow( x, y ) ) {
        return intmax__min_bound();
    } else if ( intmax__div_would_overflow( x, y ) ) {
        return intmax__max_bound();
    } else {
        return x / y;
    }
}


intmax_t
intmax__mod_b(
        intmax_t const x,
        intmax_t const y )
{
    if ( !intmax__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


intmax_t
intmax__negate_b( intmax_t const x )
{
    if ( x == intmax__min_bound() ) {
        return intmax__max_bound();
    } else {
        return -x;
    }
}


intmax_t
intmax__abs_b( intmax_t const x )
{
    if ( x == intmax__min_bound() ) {
        return intmax__max_bound();
    } else {
        return intmax__abs( x );
    }
}


bool
intmax__same_sign(
        intmax_t const x,
        intmax_t const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
intmax__in_delta(
        intmax_t const x,
        intmax_t const delta,
        intmax_t const y )
{
    return intmax__sub_b( x, delta ) <= y
        && y <= intmax__add_b( x, delta );
}


bool
intmax__in_delta_x(
        intmax_t const x,
        intmax_t const delta,
        intmax_t const y )
{
    return intmax__sub_b( x, delta ) < y
        && y < intmax__add_b( x, delta );
}


bool intmax__is_negative   ( intmax_t const x ) { return x < 0; }
bool intmax__is_nonpositive( intmax_t const x ) { return x <= 0; }
bool intmax__is_zero       ( intmax_t const x ) { return x == 0; }
bool intmax__is_nonzero    ( intmax_t const x ) { return x != 0; }
bool intmax__is_nonnegative( intmax_t const x ) { return x >= 0; }
bool intmax__is_positive   ( intmax_t const x ) { return x > 0; }


ord
intmax__compare_0( intmax_t const x )
{
    return intmax__compare( x, 0 );
}


bool intmax__is_even( intmax_t const x ) { return x % 2 == 0; }
bool intmax__is_odd ( intmax_t const x ) { return x % 2 == 1; }


intmax_t intmax__add_2( intmax_t const x )
        { return intmax__add( x, 2 ); }
intmax_t intmax__sub_2( intmax_t const x )
        { return intmax__sub( x, 2 ); }
intmax_t intmax__mul_2( intmax_t const x )
        { return intmax__mul( x, 2 ); }
intmax_t intmax__div_2( intmax_t const x )
        { return intmax__div( x, 2 ); }
intmax_t intmax__mod_2( intmax_t const x )
        { return intmax__mod( x, 2 ); }


intmax_t intmax__mul_10( intmax_t const x )
        { return intmax__mul( x, 10 ); }
intmax_t intmax__div_10( intmax_t const x )
        { return intmax__div( x, 10 ); }


intmax_t intmax__add_b_2( intmax_t const x )
        { return intmax__add_b( x, 2 ); }
intmax_t intmax__sub_b_2( intmax_t const x )
        { return intmax__sub_b( x, 2 ); }
intmax_t intmax__mul_b_2( intmax_t const x )
        { return intmax__mul_b( x, 2 ); }
intmax_t intmax__mul_b_10( intmax_t const x )
        { return intmax__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

intmax_t
intmax__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    intmax_t const x = strtoimax( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < intmax__min_bound()
             || x > intmax__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

