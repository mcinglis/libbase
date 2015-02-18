
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


#include "size.h"

#include <libtypes/types.h>


size_t size__id( size_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

size_t size__min_bound( void ) { return 0; }
size_t size__max_bound( void ) { return SIZE_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
size__equal(
        size_t const x,
        size_t const y )
{
    return x == y;
}


bool
size__not_equal(
        size_t const x,
        size_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
size__compare(
        size_t const x,
        size_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
size__less_than(
        size_t const x,
        size_t const y )
{
    return x < y;
}


bool
size__less_than_or_eq(
        size_t const x,
        size_t const y )
{
    return x <= y;
}


bool
size__greater_than_or_eq(
        size_t const x,
        size_t const y )
{
    return x >= y;
}


bool
size__greater_than(
        size_t const x,
        size_t const y )
{
    return x > y;
}


size_t
size__min2(
        size_t const x,
        size_t const y )
{
    return ( x < y ) ? x : y;
}


size_t
size__max2(
        size_t const x,
        size_t const y )
{
    return ( x > y ) ? x : y;
}


size_t
size__min_n(
        size_t const n,
        size_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    size_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = size__min2( min, xs[ i ] );
    }
    return min;
}


size_t
size__max_n(
        size_t const n,
        size_t const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    size_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = size__max2( max, xs[ i ] );
    }
    return max;
}


size_t
size__clamp(
        size_t const lower,
        size_t const upper,
        size_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


size_t
size__succ( size_t const x )
{
    ASSERT( x != size__max_bound() );

    return x + 1;
}


size_t
size__succ_b( size_t const x )
{
    return ( x == size__max_bound() ) ? x : ( x + 1 );
}


size_t
size__pred( size_t const x )
{
    ASSERT( x != size__min_bound() );

    return x - 1;
}


size_t
size__pred_b( size_t const x )
{
    return ( x == size__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool size__is_signed( void ) { return false; }


bool
size__add_would_underflow(
        size_t const x,
        size_t const y )
{
    return false;
}


bool
size__add_would_overflow(
        size_t const x,
        size_t const y )
{
    return ( x > ( size__max_bound() - y ) );
}


bool
size__can_add(
        size_t const x,
        size_t const y )
{
    return !size__add_would_overflow( x, y );
}


bool
size__sub_would_underflow(
        size_t const x,
        size_t const y )
{
    return ( x < y );
}


bool
size__sub_would_overflow(
        size_t const x,
        size_t const y )
{
    return false;
}


bool
size__can_sub(
        size_t const x,
        size_t const y )
{
    return !size__sub_would_underflow( x, y );
}


bool
size__mul_would_underflow(
        size_t const x,
        size_t const y )
{
    return false;
}


bool
size__mul_would_overflow(
        size_t const x,
        size_t const y )
{
    return ( x > ( size__max_bound() / y ) );
}


bool
size__can_mul(
        size_t const x,
        size_t const y )
{
    return !size__mul_would_overflow( x, y );
}


bool
size__div_would_underflow(
        size_t const x,
        size_t const y )
{
    return false;
}


bool
size__div_would_overflow(
        size_t const x,
        size_t const y )
{
    return false;
}


bool
size__can_div(
        size_t const x,
        size_t const y )
{
    return y != 0;
}


size_t
size__add(
        size_t const x,
        size_t const y )
{
    return x + y;
}


size_t
size__sub(
        size_t const x,
        size_t const y )
{
    return x - y;
}


size_t
size__mul(
        size_t const x,
        size_t const y )
{
    return x * y;
}


size_t
size__div(
        size_t const x,
        size_t const y )
{
    ASSERT( y != 0 );

    return x / y;
}


size_t
size__mod(
        size_t const x,
        size_t const y )
{
    ASSERT( y != 0 );

    return x % y;
}


size_t
size__negate( size_t const x )
{
    return -x;
}


size_t
size__abs( size_t const x )
{
    return x;
}


size_t
size__add_b(
        size_t const x,
        size_t const y )
{
    if ( size__add_would_overflow( x, y ) ) {
        return size__max_bound();
    } else {
        return x + y;
    }
}


size_t
size__sub_b(
        size_t const x,
        size_t const y )
{
    if ( size__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


size_t
size__mul_b(
        size_t const x,
        size_t const y )
{
    if ( size__mul_would_overflow( x, y ) ) {
        return size__max_bound();
    } else {
        return x * y;
    }
}


size_t
size__div_b(
        size_t const x,
        size_t const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return size__max_bound();
        }
    } else {
        return x / y;
    }
}


size_t
size__mod_b(
        size_t const x,
        size_t const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


size_t
size__negate_b( size_t const x )
{
    return size__negate( x );
}


size_t
size__abs_b( size_t const x )
{
    return size__abs( x );
}


bool
size__same_sign(
        size_t const x,
        size_t const y )
{
    return true;
}


bool size__is_negative   ( size_t const x ) { return false; }
bool size__is_nonpositive( size_t const x ) { return x == 0; }
bool size__is_zero       ( size_t const x ) { return x == 0; }
bool size__is_nonnegative( size_t const x ) { return true; }
bool size__is_positive   ( size_t const x ) { return x != 0; }


ord
size__compare_0( size_t const x )
{
    return size__compare( x, 0 );
}


bool size__is_even( size_t const x ) { return x % 2 == 0; }
bool size__is_odd ( size_t const x ) { return x % 2 == 1; }


size_t size__add_2( size_t const x )
        { return size__add( x, 2 ); }
size_t size__sub_2( size_t const x )
        { return size__sub( x, 2 ); }
size_t size__mul_2( size_t const x )
        { return size__mul( x, 2 ); }
size_t size__div_2( size_t const x )
        { return size__div( x, 2 ); }
size_t size__mod_2( size_t const x )
        { return size__mod( x, 2 ); }


size_t size__mul_10( size_t const x )
        { return size__mul( x, 10 ); }
size_t size__div_10( size_t const x )
        { return size__div( x, 10 ); }


size_t size__add_b_2( size_t const x )
        { return size__add_b( x, 2 ); }
size_t size__sub_b_2( size_t const x )
        { return size__sub_b( x, 2 ); }
size_t size__mul_b_2( size_t const x )
        { return size__mul_b( x, 2 ); }
size_t size__mul_b_10( size_t const x )
        { return size__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

size_t
size__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    uintmax_t const x = strtoumax( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < size__min_bound()
             || x > size__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

