
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


#include "ullong.h"

#include <libtypes/types.h>


ullong ullong__id( ullong const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

ullong ullong__min_bound( void ) { return 0; }
ullong ullong__max_bound( void ) { return ULLONG_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
ullong__equal(
        ullong const x,
        ullong const y )
{
    return x == y;
}


bool
ullong__not_equal(
        ullong const x,
        ullong const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
ullong__compare(
        ullong const x,
        ullong const y )
{
    return ( x > y ) - ( x < y );
}


bool
ullong__less_than(
        ullong const x,
        ullong const y )
{
    return x < y;
}


bool
ullong__less_than_or_eq(
        ullong const x,
        ullong const y )
{
    return x <= y;
}


bool
ullong__greater_than_or_eq(
        ullong const x,
        ullong const y )
{
    return x >= y;
}


bool
ullong__greater_than(
        ullong const x,
        ullong const y )
{
    return x > y;
}


ullong
ullong__min2(
        ullong const x,
        ullong const y )
{
    return ( x < y ) ? x : y;
}


ullong
ullong__max2(
        ullong const x,
        ullong const y )
{
    return ( x > y ) ? x : y;
}


ullong
ullong__min_n(
        size_t const n,
        ullong const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    ullong min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = ullong__min2( min, xs[ i ] );
    }
    return min;
}


ullong
ullong__max_n(
        size_t const n,
        ullong const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    ullong max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = ullong__max2( max, xs[ i ] );
    }
    return max;
}


ullong
ullong__clamp(
        ullong const lower,
        ullong const upper,
        ullong const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


ullong
ullong__succ( ullong const x )
{
    ASSERT( x != ullong__max_bound() );

    return x + 1;
}


ullong
ullong__succ_b( ullong const x )
{
    return ( x == ullong__max_bound() ) ? x : ( x + 1 );
}


ullong
ullong__pred( ullong const x )
{
    ASSERT( x != ullong__min_bound() );

    return x - 1;
}


ullong
ullong__pred_b( ullong const x )
{
    return ( x == ullong__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool ullong__is_signed( void ) { return false; }


bool
ullong__add_would_underflow(
        ullong const x,
        ullong const y )
{
    return false;
}


bool
ullong__add_would_overflow(
        ullong const x,
        ullong const y )
{
    return ( x > ( ullong__max_bound() - y ) );
}


bool
ullong__can_add(
        ullong const x,
        ullong const y )
{
    return !ullong__add_would_overflow( x, y );
}


bool
ullong__sub_would_underflow(
        ullong const x,
        ullong const y )
{
    return ( x < y );
}


bool
ullong__sub_would_overflow(
        ullong const x,
        ullong const y )
{
    return false;
}


bool
ullong__can_sub(
        ullong const x,
        ullong const y )
{
    return !ullong__sub_would_underflow( x, y );
}


bool
ullong__mul_would_underflow(
        ullong const x,
        ullong const y )
{
    return false;
}


bool
ullong__mul_would_overflow(
        ullong const x,
        ullong const y )
{
    return ( x > ( ullong__max_bound() / y ) );
}


bool
ullong__can_mul(
        ullong const x,
        ullong const y )
{
    return !ullong__mul_would_overflow( x, y );
}


bool
ullong__div_would_underflow(
        ullong const x,
        ullong const y )
{
    return false;
}


bool
ullong__div_would_overflow(
        ullong const x,
        ullong const y )
{
    return false;
}


bool
ullong__can_div(
        ullong const x,
        ullong const y )
{
    return y != 0;
}


ullong
ullong__add(
        ullong const x,
        ullong const y )
{
    return x + y;
}


ullong
ullong__sub(
        ullong const x,
        ullong const y )
{
    return x - y;
}


ullong
ullong__mul(
        ullong const x,
        ullong const y )
{
    return x * y;
}


ullong
ullong__div(
        ullong const x,
        ullong const y )
{
    ASSERT( y != 0 );

    return x / y;
}


ullong
ullong__mod(
        ullong const x,
        ullong const y )
{
    ASSERT( y != 0 );

    return x % y;
}


ullong
ullong__negate( ullong const x )
{
    return -x;
}


ullong
ullong__abs( ullong const x )
{
    return x;
}


ullong
ullong__add_b(
        ullong const x,
        ullong const y )
{
    if ( ullong__add_would_overflow( x, y ) ) {
        return ullong__max_bound();
    } else {
        return x + y;
    }
}


ullong
ullong__sub_b(
        ullong const x,
        ullong const y )
{
    if ( ullong__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


ullong
ullong__mul_b(
        ullong const x,
        ullong const y )
{
    if ( ullong__mul_would_overflow( x, y ) ) {
        return ullong__max_bound();
    } else {
        return x * y;
    }
}


ullong
ullong__div_b(
        ullong const x,
        ullong const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return ullong__max_bound();
        }
    } else {
        return x / y;
    }
}


ullong
ullong__mod_b(
        ullong const x,
        ullong const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


ullong
ullong__negate_b( ullong const x )
{
    return ullong__negate( x );
}


ullong
ullong__abs_b( ullong const x )
{
    return ullong__abs( x );
}


bool
ullong__same_sign(
        ullong const x,
        ullong const y )
{
    return true;
}


bool ullong__is_negative   ( ullong const x ) { return false; }
bool ullong__is_nonpositive( ullong const x ) { return x == 0; }
bool ullong__is_zero       ( ullong const x ) { return x == 0; }
bool ullong__is_nonnegative( ullong const x ) { return true; }
bool ullong__is_positive   ( ullong const x ) { return x != 0; }


ord
ullong__compare_0( ullong const x )
{
    return ullong__compare( x, 0 );
}


bool ullong__is_even( ullong const x ) { return x % 2 == 0; }
bool ullong__is_odd ( ullong const x ) { return x % 2 == 1; }


ullong ullong__add_2( ullong const x )
        { return ullong__add( x, 2 ); }
ullong ullong__sub_2( ullong const x )
        { return ullong__sub( x, 2 ); }
ullong ullong__mul_2( ullong const x )
        { return ullong__mul( x, 2 ); }
ullong ullong__div_2( ullong const x )
        { return ullong__div( x, 2 ); }
ullong ullong__mod_2( ullong const x )
        { return ullong__mod( x, 2 ); }


ullong ullong__mul_10( ullong const x )
        { return ullong__mul( x, 10 ); }
ullong ullong__div_10( ullong const x )
        { return ullong__div( x, 10 ); }


ullong ullong__add_b_2( ullong const x )
        { return ullong__add_b( x, 2 ); }
ullong ullong__sub_b_2( ullong const x )
        { return ullong__sub_b( x, 2 ); }
ullong ullong__mul_b_2( ullong const x )
        { return ullong__mul_b( x, 2 ); }
ullong ullong__mul_b_10( ullong const x )
        { return ullong__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

ullong
ullong__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    ullong const x = strtoull( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < ullong__min_bound()
             || x > ullong__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

