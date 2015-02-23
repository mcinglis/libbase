
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


#include "llong.h"

#include <libtypes/types.h>


llong llong__id( llong const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

llong llong__min_bound( void ) { return LLONG_MIN; }
llong llong__max_bound( void ) { return LLONG_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
llong__equal(
        llong const x,
        llong const y )
{
    return x == y;
}


bool
llong__not_equal(
        llong const x,
        llong const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
llong__compare(
        llong const x,
        llong const y )
{
    return ( x > y ) - ( x < y );
}


bool
llong__less_than(
        llong const x,
        llong const y )
{
    return x < y;
}


bool
llong__less_than_or_eq(
        llong const x,
        llong const y )
{
    return x <= y;
}


bool
llong__greater_than_or_eq(
        llong const x,
        llong const y )
{
    return x >= y;
}


bool
llong__greater_than(
        llong const x,
        llong const y )
{
    return x > y;
}


llong
llong__min2(
        llong const x,
        llong const y )
{
    return ( x < y ) ? x : y;
}


llong
llong__max2(
        llong const x,
        llong const y )
{
    return ( x > y ) ? x : y;
}


llong
llong__min_n(
        size_t const n,
        llong const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    llong min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = llong__min2( min, xs[ i ] );
    }
    return min;
}


llong
llong__max_n(
        size_t const n,
        llong const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    llong max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = llong__max2( max, xs[ i ] );
    }
    return max;
}


llong
llong__clamp(
        llong const lower,
        llong const upper,
        llong const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
llong__in_range(
        llong const lower,
        llong const upper,
        llong const x )
{
    return lower <= x && x <= upper;
}


bool
llong__in_range_x(
        llong const lower,
        llong const upper,
        llong const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


llong
llong__succ( llong const x )
{
    ASSERT( x != llong__max_bound() );

    return x + 1;
}


llong
llong__succ_b( llong const x )
{
    return ( x == llong__max_bound() ) ? x : ( x + 1 );
}


llong
llong__pred( llong const x )
{
    ASSERT( x != llong__min_bound() );

    return x - 1;
}


llong
llong__pred_b( llong const x )
{
    return ( x == llong__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool llong__is_signed( void ) { return true; }


bool
llong__add_would_underflow(
        llong const x,
        llong const y )
{
    return y < 0 && x < ( llong__min_bound() - y );
}


bool
llong__add_would_overflow(
        llong const x,
        llong const y )
{
    return y > 0 && x > ( llong__max_bound() - y );
}


bool
llong__can_add(
        llong const x,
        llong const y )
{
    return !llong__add_would_underflow( x, y )
        && !llong__add_would_overflow( x, y );
}


bool
llong__sub_would_underflow(
        llong const x,
        llong const y )
{
    return y > 0 && x < ( llong__min_bound() + y );
}


bool
llong__sub_would_overflow(
        llong const x,
        llong const y )
{
    return y < 0 && x > ( llong__max_bound() + y );
}


bool
llong__can_sub(
        llong const x,
        llong const y )
{
    return !llong__sub_would_underflow( x, y )
        && !llong__sub_would_overflow( x, y );
}


bool
llong__mul_would_underflow(
        llong const x,
        llong const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( llong__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( llong__min_bound() / y ) )
                              : false;
}


bool
llong__mul_would_overflow(
        llong const x,
        llong const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( llong__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( llong__max_bound() / x ) )
                              : false;
}


bool
llong__can_mul(
        llong const x,
        llong const y )
{
    return !llong__mul_would_underflow( x, y )
        && !llong__mul_would_overflow( x, y );
}


bool
llong__div_would_underflow(
        llong const x,
        llong const y )
{
    return false;
}


bool
llong__div_would_overflow(
        llong const x,
        llong const y )
{
    return x == llong__min_bound() && y == -1;
}


bool
llong__can_div(
        llong const x,
        llong const y )
{
    return ( y != 0 && !llong__div_would_overflow( x, y ) );
}


llong
llong__add(
        llong const x,
        llong const y )
{
    ASSERT( llong__can_add( x, y ) );

    return x + y;
}


llong
llong__sub(
        llong const x,
        llong const y )
{
    ASSERT( llong__can_sub( x, y ) );

    return x - y;
}


llong
llong__mul(
        llong const x,
        llong const y )
{
    ASSERT( llong__can_mul( x, y ) );

    return x * y;
}


llong
llong__div(
        llong const x,
        llong const y )
{
    ASSERT( llong__can_div( x, y ) );

    return x / y;
}


llong
llong__mod(
        llong const x,
        llong const y )
{
    ASSERT( llong__can_div( x, y ) );

    return x % y;
}


llong
llong__negate( llong const x )
{
    ASSERT( x != llong__min_bound() );

    return -x;
}


llong
llong__abs( llong const x )
{
    ASSERT( x != llong__min_bound() );

    return ( x < 0 ) ? -x : x;
}


llong
llong__add_b(
        llong const x,
        llong const y )
{
    if ( llong__add_would_underflow( x, y ) ) {
        return llong__min_bound();
    } else if ( llong__add_would_overflow( x, y ) ) {
        return llong__max_bound();
    } else {
        return x + y;
    }
}


llong
llong__sub_b(
        llong const x,
        llong const y )
{
    if ( llong__sub_would_underflow( x, y ) ) {
        return llong__min_bound();
    } else if ( llong__sub_would_overflow( x, y ) ) {
        return llong__max_bound();
    } else {
        return x - y;
    }
}


llong
llong__mul_b(
        llong const x,
        llong const y )
{
    if ( llong__mul_would_underflow( x, y ) ) {
        return llong__min_bound();
    } else if ( llong__mul_would_overflow( x, y ) ) {
        return llong__max_bound();
    } else {
        return x * y;
    }
}


llong
llong__div_b(
        llong const x,
        llong const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return llong__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return llong__max_bound();
        }
    } else if ( llong__div_would_underflow( x, y ) ) {
        return llong__min_bound();
    } else if ( llong__div_would_overflow( x, y ) ) {
        return llong__max_bound();
    } else {
        return x / y;
    }
}


llong
llong__mod_b(
        llong const x,
        llong const y )
{
    if ( !llong__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


llong
llong__negate_b( llong const x )
{
    if ( x == llong__min_bound() ) {
        return llong__max_bound();
    } else {
        return -x;
    }
}


llong
llong__abs_b( llong const x )
{
    if ( x == llong__min_bound() ) {
        return llong__max_bound();
    } else {
        return llong__abs( x );
    }
}


bool
llong__same_sign(
        llong const x,
        llong const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
llong__in_delta(
        llong const x,
        llong const delta,
        llong const y )
{
    return llong__sub_b( x, delta ) <= y
        && y <= llong__add_b( x, delta );
}


bool
llong__in_delta_x(
        llong const x,
        llong const delta,
        llong const y )
{
    return llong__sub_b( x, delta ) < y
        && y < llong__add_b( x, delta );
}


bool llong__is_negative   ( llong const x ) { return x < 0; }
bool llong__is_nonpositive( llong const x ) { return x <= 0; }
bool llong__is_zero       ( llong const x ) { return x == 0; }
bool llong__is_nonzero    ( llong const x ) { return x != 0; }
bool llong__is_nonnegative( llong const x ) { return x >= 0; }
bool llong__is_positive   ( llong const x ) { return x > 0; }


ord
llong__compare_0( llong const x )
{
    return llong__compare( x, 0 );
}


bool llong__is_even( llong const x ) { return x % 2 == 0; }
bool llong__is_odd ( llong const x ) { return x % 2 == 1; }


llong llong__add_2( llong const x )
        { return llong__add( x, 2 ); }
llong llong__sub_2( llong const x )
        { return llong__sub( x, 2 ); }
llong llong__mul_2( llong const x )
        { return llong__mul( x, 2 ); }
llong llong__div_2( llong const x )
        { return llong__div( x, 2 ); }
llong llong__mod_2( llong const x )
        { return llong__mod( x, 2 ); }


llong llong__mul_10( llong const x )
        { return llong__mul( x, 10 ); }
llong llong__div_10( llong const x )
        { return llong__div( x, 10 ); }


llong llong__add_b_2( llong const x )
        { return llong__add_b( x, 2 ); }
llong llong__sub_b_2( llong const x )
        { return llong__sub_b( x, 2 ); }
llong llong__mul_b_2( llong const x )
        { return llong__mul_b( x, 2 ); }
llong llong__mul_b_10( llong const x )
        { return llong__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

llong
llong__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    llong const x = strtoll( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < llong__min_bound()
             || x > llong__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

