
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


#include "wchar.h"

#include <libtypes/types.h>


wchar_t wchar__id( wchar_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

wchar_t wchar__min_bound( void ) { return WCHAR_MIN; }
wchar_t wchar__max_bound( void ) { return WCHAR_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
wchar__equal(
        wchar_t const x,
        wchar_t const y )
{
    return x == y;
}


bool
wchar__not_equal(
        wchar_t const x,
        wchar_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
wchar__compare(
        wchar_t const x,
        wchar_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
wchar__less_than(
        wchar_t const x,
        wchar_t const y )
{
    return x < y;
}


bool
wchar__less_than_or_eq(
        wchar_t const x,
        wchar_t const y )
{
    return x <= y;
}


bool
wchar__greater_than_or_eq(
        wchar_t const x,
        wchar_t const y )
{
    return x >= y;
}


bool
wchar__greater_than(
        wchar_t const x,
        wchar_t const y )
{
    return x > y;
}


wchar_t
wchar__min2(
        wchar_t const x,
        wchar_t const y )
{
    return ( x < y ) ? x : y;
}


wchar_t
wchar__max2(
        wchar_t const x,
        wchar_t const y )
{
    return ( x > y ) ? x : y;
}


wchar_t
wchar__min_n(
        size_t const n,
        wchar_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    wchar_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = wchar__min2( min, xs[ i ] );
    }
    return min;
}


wchar_t
wchar__max_n(
        size_t const n,
        wchar_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    wchar_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = wchar__max2( max, xs[ i ] );
    }
    return max;
}


wchar_t
wchar__clamp(
        wchar_t const lower,
        wchar_t const upper,
        wchar_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


wchar_t
wchar__succ( wchar_t const x )
{
    ASSERT( x != wchar__max_bound() );

    return x + 1;
}


wchar_t
wchar__succ_b( wchar_t const x )
{
    return ( x == wchar__max_bound() ) ? x : ( x + 1 );
}


wchar_t
wchar__pred( wchar_t const x )
{
    ASSERT( x != wchar__min_bound() );

    return x - 1;
}


wchar_t
wchar__pred_b( wchar_t const x )
{
    return ( x == wchar__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool wchar__is_signed( void ) { return true; }


bool
wchar__add_would_underflow(
        wchar_t const x,
        wchar_t const y )
{
    return y < 0 && x < ( wchar__min_bound() - y );
}


bool
wchar__add_would_overflow(
        wchar_t const x,
        wchar_t const y )
{
    return y > 0 && x > ( wchar__max_bound() - y );
}


bool
wchar__can_add(
        wchar_t const x,
        wchar_t const y )
{
    return !wchar__add_would_underflow( x, y )
        && !wchar__add_would_overflow( x, y );
}


bool
wchar__sub_would_underflow(
        wchar_t const x,
        wchar_t const y )
{
    return y > 0 && x < ( wchar__min_bound() + y );
}


bool
wchar__sub_would_overflow(
        wchar_t const x,
        wchar_t const y )
{
    return y < 0 && x > ( wchar__max_bound() + y );
}


bool
wchar__can_sub(
        wchar_t const x,
        wchar_t const y )
{
    return !wchar__sub_would_underflow( x, y )
        && !wchar__sub_would_overflow( x, y );
}


bool
wchar__mul_would_underflow(
        wchar_t const x,
        wchar_t const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( wchar__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( wchar__min_bound() / y ) )
                              : false;
}


bool
wchar__mul_would_overflow(
        wchar_t const x,
        wchar_t const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( wchar__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( wchar__max_bound() / x ) )
                              : false;
}


bool
wchar__can_mul(
        wchar_t const x,
        wchar_t const y )
{
    return !wchar__mul_would_underflow( x, y )
        && !wchar__mul_would_overflow( x, y );
}


bool
wchar__div_would_underflow(
        wchar_t const x,
        wchar_t const y )
{
    return false;
}


bool
wchar__div_would_overflow(
        wchar_t const x,
        wchar_t const y )
{
    return x == wchar__min_bound() && y == -1;
}


bool
wchar__can_div(
        wchar_t const x,
        wchar_t const y )
{
    return ( y != 0 && !wchar__div_would_overflow( x, y ) );
}


wchar_t
wchar__add(
        wchar_t const x,
        wchar_t const y )
{
    ASSERT( wchar__can_add( x, y ) );

    return x + y;
}


wchar_t
wchar__sub(
        wchar_t const x,
        wchar_t const y )
{
    ASSERT( wchar__can_sub( x, y ) );

    return x - y;
}


wchar_t
wchar__mul(
        wchar_t const x,
        wchar_t const y )
{
    ASSERT( wchar__can_mul( x, y ) );

    return x * y;
}


wchar_t
wchar__div(
        wchar_t const x,
        wchar_t const y )
{
    ASSERT( wchar__can_div( x, y ) );

    return x / y;
}


wchar_t
wchar__mod(
        wchar_t const x,
        wchar_t const y )
{
    ASSERT( wchar__can_div( x, y ) );

    return x % y;
}


wchar_t
wchar__negate( wchar_t const x )
{
    ASSERT( x != wchar__min_bound() );

    return -x;
}


wchar_t
wchar__abs( wchar_t const x )
{
    ASSERT( x != wchar__min_bound() );

    return ( x < 0 ) ? -x : x;
}


wchar_t
wchar__add_b(
        wchar_t const x,
        wchar_t const y )
{
    if ( wchar__add_would_underflow( x, y ) ) {
        return wchar__min_bound();
    } else if ( wchar__add_would_overflow( x, y ) ) {
        return wchar__max_bound();
    } else {
        return x + y;
    }
}


wchar_t
wchar__sub_b(
        wchar_t const x,
        wchar_t const y )
{
    if ( wchar__sub_would_underflow( x, y ) ) {
        return wchar__min_bound();
    } else if ( wchar__sub_would_overflow( x, y ) ) {
        return wchar__max_bound();
    } else {
        return x - y;
    }
}


wchar_t
wchar__mul_b(
        wchar_t const x,
        wchar_t const y )
{
    if ( wchar__mul_would_underflow( x, y ) ) {
        return wchar__min_bound();
    } else if ( wchar__mul_would_overflow( x, y ) ) {
        return wchar__max_bound();
    } else {
        return x * y;
    }
}


wchar_t
wchar__div_b(
        wchar_t const x,
        wchar_t const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return wchar__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return wchar__max_bound();
        }
    } else if ( wchar__div_would_underflow( x, y ) ) {
        return wchar__min_bound();
    } else if ( wchar__div_would_overflow( x, y ) ) {
        return wchar__max_bound();
    } else {
        return x / y;
    }
}


wchar_t
wchar__mod_b(
        wchar_t const x,
        wchar_t const y )
{
    if ( !wchar__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


wchar_t
wchar__negate_b( wchar_t const x )
{
    if ( x == wchar__min_bound() ) {
        return wchar__max_bound();
    } else {
        return -x;
    }
}


wchar_t
wchar__abs_b( wchar_t const x )
{
    if ( x == wchar__min_bound() ) {
        return wchar__max_bound();
    } else {
        return wchar__abs( x );
    }
}


bool
wchar__same_sign(
        wchar_t const x,
        wchar_t const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool wchar__is_negative   ( wchar_t const x ) { return x < 0; }
bool wchar__is_nonpositive( wchar_t const x ) { return x <= 0; }
bool wchar__is_zero       ( wchar_t const x ) { return x == 0; }
bool wchar__is_nonzero    ( wchar_t const x ) { return x != 0; }
bool wchar__is_nonnegative( wchar_t const x ) { return x >= 0; }
bool wchar__is_positive   ( wchar_t const x ) { return x > 0; }


ord
wchar__compare_0( wchar_t const x )
{
    return wchar__compare( x, 0 );
}


bool wchar__is_even( wchar_t const x ) { return x % 2 == 0; }
bool wchar__is_odd ( wchar_t const x ) { return x % 2 == 1; }


wchar_t wchar__add_2( wchar_t const x )
        { return wchar__add( x, 2 ); }
wchar_t wchar__sub_2( wchar_t const x )
        { return wchar__sub( x, 2 ); }
wchar_t wchar__mul_2( wchar_t const x )
        { return wchar__mul( x, 2 ); }
wchar_t wchar__div_2( wchar_t const x )
        { return wchar__div( x, 2 ); }
wchar_t wchar__mod_2( wchar_t const x )
        { return wchar__mod( x, 2 ); }


wchar_t wchar__mul_10( wchar_t const x )
        { return wchar__mul( x, 10 ); }
wchar_t wchar__div_10( wchar_t const x )
        { return wchar__div( x, 10 ); }


wchar_t wchar__add_b_2( wchar_t const x )
        { return wchar__add_b( x, 2 ); }
wchar_t wchar__sub_b_2( wchar_t const x )
        { return wchar__sub_b( x, 2 ); }
wchar_t wchar__mul_b_2( wchar_t const x )
        { return wchar__mul_b( x, 2 ); }
wchar_t wchar__mul_b_10( wchar_t const x )
        { return wchar__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

wchar_t
wchar__from_str( char const * const str )
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
    } else if ( x < wchar__min_bound()
             || x > wchar__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

