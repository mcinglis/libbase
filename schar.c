
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


#include "schar.h"

#include <libtypes/types.h>


schar schar__id( schar const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

schar schar__min_bound( void ) { return SCHAR_MIN; }
schar schar__max_bound( void ) { return SCHAR_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
schar__equal(
        schar const x,
        schar const y )
{
    return x == y;
}


bool
schar__not_equal(
        schar const x,
        schar const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
schar__compare(
        schar const x,
        schar const y )
{
    return ( x > y ) - ( x < y );
}


bool
schar__less_than(
        schar const x,
        schar const y )
{
    return x < y;
}


bool
schar__less_than_or_eq(
        schar const x,
        schar const y )
{
    return x <= y;
}


bool
schar__greater_than_or_eq(
        schar const x,
        schar const y )
{
    return x >= y;
}


bool
schar__greater_than(
        schar const x,
        schar const y )
{
    return x > y;
}


schar
schar__min2(
        schar const x,
        schar const y )
{
    return ( x < y ) ? x : y;
}


schar
schar__max2(
        schar const x,
        schar const y )
{
    return ( x > y ) ? x : y;
}


schar
schar__min_n(
        size_t const n,
        schar const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    schar min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = schar__min2( min, xs[ i ] );
    }
    return min;
}


schar
schar__max_n(
        size_t const n,
        schar const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    schar max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = schar__max2( max, xs[ i ] );
    }
    return max;
}


schar
schar__clamp(
        schar const lower,
        schar const upper,
        schar const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}


bool
schar__in_range(
        schar const lower,
        schar const upper,
        schar const x )
{
    return lower <= x && x <= upper;
}


bool
schar__in_range_x(
        schar const lower,
        schar const upper,
        schar const x )
{
    return lower < x && x < upper;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


schar
schar__succ( schar const x )
{
    ASSERT( x != schar__max_bound() );

    return x + 1;
}


schar
schar__succ_b( schar const x )
{
    return ( x == schar__max_bound() ) ? x : ( x + 1 );
}


schar
schar__pred( schar const x )
{
    ASSERT( x != schar__min_bound() );

    return x - 1;
}


schar
schar__pred_b( schar const x )
{
    return ( x == schar__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool schar__is_signed( void ) { return true; }


bool
schar__add_would_underflow(
        schar const x,
        schar const y )
{
    return y < 0 && x < ( schar__min_bound() - y );
}


bool
schar__add_would_overflow(
        schar const x,
        schar const y )
{
    return y > 0 && x > ( schar__max_bound() - y );
}


bool
schar__can_add(
        schar const x,
        schar const y )
{
    return !schar__add_would_underflow( x, y )
        && !schar__add_would_overflow( x, y );
}


bool
schar__sub_would_underflow(
        schar const x,
        schar const y )
{
    return y > 0 && x < ( schar__min_bound() + y );
}


bool
schar__sub_would_overflow(
        schar const x,
        schar const y )
{
    return y < 0 && x > ( schar__max_bound() + y );
}


bool
schar__can_sub(
        schar const x,
        schar const y )
{
    return !schar__sub_would_underflow( x, y )
        && !schar__sub_would_overflow( x, y );
}


bool
schar__mul_would_underflow(
        schar const x,
        schar const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( schar__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( schar__min_bound() / y ) )
                              : false;
}


bool
schar__mul_would_overflow(
        schar const x,
        schar const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( schar__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( schar__max_bound() / x ) )
                              : false;
}


bool
schar__can_mul(
        schar const x,
        schar const y )
{
    return !schar__mul_would_underflow( x, y )
        && !schar__mul_would_overflow( x, y );
}


bool
schar__div_would_underflow(
        schar const x,
        schar const y )
{
    return false;
}


bool
schar__div_would_overflow(
        schar const x,
        schar const y )
{
    return x == schar__min_bound() && y == -1;
}


bool
schar__can_div(
        schar const x,
        schar const y )
{
    return ( y != 0 && !schar__div_would_overflow( x, y ) );
}


schar
schar__add(
        schar const x,
        schar const y )
{
    ASSERT( schar__can_add( x, y ) );

    return x + y;
}


schar
schar__sub(
        schar const x,
        schar const y )
{
    ASSERT( schar__can_sub( x, y ) );

    return x - y;
}


schar
schar__mul(
        schar const x,
        schar const y )
{
    ASSERT( schar__can_mul( x, y ) );

    return x * y;
}


schar
schar__div(
        schar const x,
        schar const y )
{
    ASSERT( schar__can_div( x, y ) );

    return x / y;
}


schar
schar__mod(
        schar const x,
        schar const y )
{
    ASSERT( schar__can_div( x, y ) );

    return x % y;
}


schar
schar__negate( schar const x )
{
    ASSERT( x != schar__min_bound() );

    return -x;
}


schar
schar__abs( schar const x )
{
    ASSERT( x != schar__min_bound() );

    return ( x < 0 ) ? -x : x;
}


schar
schar__add_b(
        schar const x,
        schar const y )
{
    if ( schar__add_would_underflow( x, y ) ) {
        return schar__min_bound();
    } else if ( schar__add_would_overflow( x, y ) ) {
        return schar__max_bound();
    } else {
        return x + y;
    }
}


schar
schar__sub_b(
        schar const x,
        schar const y )
{
    if ( schar__sub_would_underflow( x, y ) ) {
        return schar__min_bound();
    } else if ( schar__sub_would_overflow( x, y ) ) {
        return schar__max_bound();
    } else {
        return x - y;
    }
}


schar
schar__mul_b(
        schar const x,
        schar const y )
{
    if ( schar__mul_would_underflow( x, y ) ) {
        return schar__min_bound();
    } else if ( schar__mul_would_overflow( x, y ) ) {
        return schar__max_bound();
    } else {
        return x * y;
    }
}


schar
schar__div_b(
        schar const x,
        schar const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return schar__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return schar__max_bound();
        }
    } else if ( schar__div_would_underflow( x, y ) ) {
        return schar__min_bound();
    } else if ( schar__div_would_overflow( x, y ) ) {
        return schar__max_bound();
    } else {
        return x / y;
    }
}


schar
schar__mod_b(
        schar const x,
        schar const y )
{
    if ( !schar__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


schar
schar__negate_b( schar const x )
{
    if ( x == schar__min_bound() ) {
        return schar__max_bound();
    } else {
        return -x;
    }
}


schar
schar__abs_b( schar const x )
{
    if ( x == schar__min_bound() ) {
        return schar__max_bound();
    } else {
        return schar__abs( x );
    }
}


bool
schar__same_sign(
        schar const x,
        schar const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool
schar__in_delta(
        schar const x,
        schar const delta,
        schar const y )
{
    return schar__sub_b( x, delta ) <= y
        && y <= schar__add_b( x, delta );
}


bool
schar__in_delta_x(
        schar const x,
        schar const delta,
        schar const y )
{
    return schar__sub_b( x, delta ) < y
        && y < schar__add_b( x, delta );
}


bool schar__is_negative   ( schar const x ) { return x < 0; }
bool schar__is_nonpositive( schar const x ) { return x <= 0; }
bool schar__is_zero       ( schar const x ) { return x == 0; }
bool schar__is_nonzero    ( schar const x ) { return x != 0; }
bool schar__is_nonnegative( schar const x ) { return x >= 0; }
bool schar__is_positive   ( schar const x ) { return x > 0; }


ord
schar__compare_0( schar const x )
{
    return schar__compare( x, 0 );
}


bool schar__is_even( schar const x ) { return x % 2 == 0; }
bool schar__is_odd ( schar const x ) { return x % 2 == 1; }


schar schar__add_2( schar const x )
        { return schar__add( x, 2 ); }
schar schar__sub_2( schar const x )
        { return schar__sub( x, 2 ); }
schar schar__mul_2( schar const x )
        { return schar__mul( x, 2 ); }
schar schar__div_2( schar const x )
        { return schar__div( x, 2 ); }
schar schar__mod_2( schar const x )
        { return schar__mod( x, 2 ); }


schar schar__mul_10( schar const x )
        { return schar__mul( x, 10 ); }
schar schar__div_10( schar const x )
        { return schar__div( x, 10 ); }


schar schar__add_b_2( schar const x )
        { return schar__add_b( x, 2 ); }
schar schar__sub_b_2( schar const x )
        { return schar__sub_b( x, 2 ); }
schar schar__mul_b_2( schar const x )
        { return schar__mul_b( x, 2 ); }
schar schar__mul_b_10( schar const x )
        { return schar__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

schar
schar__from_str( char const * const str )
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
    } else if ( x < schar__min_bound()
             || x > schar__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

