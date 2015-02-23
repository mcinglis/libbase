
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


#include "short.h"

#include <libtypes/types.h>


short short__id( short const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

short short__min_bound( void ) { return SHRT_MIN; }
short short__max_bound( void ) { return SHRT_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
short__equal(
        short const x,
        short const y )
{
    return x == y;
}


bool
short__not_equal(
        short const x,
        short const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
short__compare(
        short const x,
        short const y )
{
    return ( x > y ) - ( x < y );
}


bool
short__less_than(
        short const x,
        short const y )
{
    return x < y;
}


bool
short__less_than_or_eq(
        short const x,
        short const y )
{
    return x <= y;
}


bool
short__greater_than_or_eq(
        short const x,
        short const y )
{
    return x >= y;
}


bool
short__greater_than(
        short const x,
        short const y )
{
    return x > y;
}


short
short__min2(
        short const x,
        short const y )
{
    return ( x < y ) ? x : y;
}


short
short__max2(
        short const x,
        short const y )
{
    return ( x > y ) ? x : y;
}


short
short__min_n(
        size_t const n,
        short const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    short min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = short__min2( min, xs[ i ] );
    }
    return min;
}


short
short__max_n(
        size_t const n,
        short const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    short max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = short__max2( max, xs[ i ] );
    }
    return max;
}


short
short__clamp(
        short const lower,
        short const upper,
        short const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
short__in_range(
        short const lower,
        short const upper,
        short const x )
{
    return lower <= x && x <= upper;
}


bool
short__in_range_x(
        short const lower,
        short const upper,
        short const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


short
short__succ( short const x )
{
    ASSERT( x != short__max_bound() );

    return x + 1;
}


short
short__succ_b( short const x )
{
    return ( x == short__max_bound() ) ? x : ( x + 1 );
}


short
short__pred( short const x )
{
    ASSERT( x != short__min_bound() );

    return x - 1;
}


short
short__pred_b( short const x )
{
    return ( x == short__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool short__is_signed( void ) { return true; }


bool
short__add_would_underflow(
        short const x,
        short const y )
{
    return y < 0 && x < ( short__min_bound() - y );
}


bool
short__add_would_overflow(
        short const x,
        short const y )
{
    return y > 0 && x > ( short__max_bound() - y );
}


bool
short__can_add(
        short const x,
        short const y )
{
    return !short__add_would_underflow( x, y )
        && !short__add_would_overflow( x, y );
}


bool
short__sub_would_underflow(
        short const x,
        short const y )
{
    return y > 0 && x < ( short__min_bound() + y );
}


bool
short__sub_would_overflow(
        short const x,
        short const y )
{
    return y < 0 && x > ( short__max_bound() + y );
}


bool
short__can_sub(
        short const x,
        short const y )
{
    return !short__sub_would_underflow( x, y )
        && !short__sub_would_overflow( x, y );
}


bool
short__mul_would_underflow(
        short const x,
        short const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( short__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( short__min_bound() / y ) )
                              : false;
}


bool
short__mul_would_overflow(
        short const x,
        short const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( short__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( short__max_bound() / x ) )
                              : false;
}


bool
short__can_mul(
        short const x,
        short const y )
{
    return !short__mul_would_underflow( x, y )
        && !short__mul_would_overflow( x, y );
}


bool
short__div_would_underflow(
        short const x,
        short const y )
{
    return false;
}


bool
short__div_would_overflow(
        short const x,
        short const y )
{
    return x == short__min_bound() && y == -1;
}


bool
short__can_div(
        short const x,
        short const y )
{
    return ( y != 0 && !short__div_would_overflow( x, y ) );
}


short
short__add(
        short const x,
        short const y )
{
    ASSERT( short__can_add( x, y ) );

    return x + y;
}


short
short__sub(
        short const x,
        short const y )
{
    ASSERT( short__can_sub( x, y ) );

    return x - y;
}


short
short__mul(
        short const x,
        short const y )
{
    ASSERT( short__can_mul( x, y ) );

    return x * y;
}


short
short__div(
        short const x,
        short const y )
{
    ASSERT( short__can_div( x, y ) );

    return x / y;
}


short
short__mod(
        short const x,
        short const y )
{
    ASSERT( short__can_div( x, y ) );

    return x % y;
}


short
short__negate( short const x )
{
    ASSERT( x != short__min_bound() );

    return -x;
}


short
short__abs( short const x )
{
    ASSERT( x != short__min_bound() );

    return ( x < 0 ) ? -x : x;
}


short
short__add_b(
        short const x,
        short const y )
{
    if ( short__add_would_underflow( x, y ) ) {
        return short__min_bound();
    } else if ( short__add_would_overflow( x, y ) ) {
        return short__max_bound();
    } else {
        return x + y;
    }
}


short
short__sub_b(
        short const x,
        short const y )
{
    if ( short__sub_would_underflow( x, y ) ) {
        return short__min_bound();
    } else if ( short__sub_would_overflow( x, y ) ) {
        return short__max_bound();
    } else {
        return x - y;
    }
}


short
short__mul_b(
        short const x,
        short const y )
{
    if ( short__mul_would_underflow( x, y ) ) {
        return short__min_bound();
    } else if ( short__mul_would_overflow( x, y ) ) {
        return short__max_bound();
    } else {
        return x * y;
    }
}


short
short__div_b(
        short const x,
        short const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return short__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return short__max_bound();
        }
    } else if ( short__div_would_underflow( x, y ) ) {
        return short__min_bound();
    } else if ( short__div_would_overflow( x, y ) ) {
        return short__max_bound();
    } else {
        return x / y;
    }
}


short
short__mod_b(
        short const x,
        short const y )
{
    if ( !short__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


short
short__negate_b( short const x )
{
    if ( x == short__min_bound() ) {
        return short__max_bound();
    } else {
        return -x;
    }
}


short
short__abs_b( short const x )
{
    if ( x == short__min_bound() ) {
        return short__max_bound();
    } else {
        return short__abs( x );
    }
}


bool
short__same_sign(
        short const x,
        short const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
short__in_delta(
        short const x,
        short const delta,
        short const y )
{
    return short__sub_b( x, delta ) <= y
        && y <= short__add_b( x, delta );
}


bool
short__in_delta_x(
        short const x,
        short const delta,
        short const y )
{
    return short__sub_b( x, delta ) < y
        && y < short__add_b( x, delta );
}


bool short__is_negative   ( short const x ) { return x < 0; }
bool short__is_nonpositive( short const x ) { return x <= 0; }
bool short__is_zero       ( short const x ) { return x == 0; }
bool short__is_nonzero    ( short const x ) { return x != 0; }
bool short__is_nonnegative( short const x ) { return x >= 0; }
bool short__is_positive   ( short const x ) { return x > 0; }


ord
short__compare_0( short const x )
{
    return short__compare( x, 0 );
}


bool short__is_even( short const x ) { return x % 2 == 0; }
bool short__is_odd ( short const x ) { return x % 2 == 1; }


short short__add_2( short const x )
        { return short__add( x, 2 ); }
short short__sub_2( short const x )
        { return short__sub( x, 2 ); }
short short__mul_2( short const x )
        { return short__mul( x, 2 ); }
short short__div_2( short const x )
        { return short__div( x, 2 ); }
short short__mod_2( short const x )
        { return short__mod( x, 2 ); }


short short__mul_10( short const x )
        { return short__mul( x, 10 ); }
short short__div_10( short const x )
        { return short__div( x, 10 ); }


short short__add_b_2( short const x )
        { return short__add_b( x, 2 ); }
short short__sub_b_2( short const x )
        { return short__sub_b( x, 2 ); }
short short__mul_b_2( short const x )
        { return short__mul_b( x, 2 ); }
short short__mul_b_10( short const x )
        { return short__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

short
short__from_str( char const * const str )
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
    } else if ( x < short__min_bound()
             || x > short__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

