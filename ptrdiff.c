
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


#include "ptrdiff.h"

#include <libtypes/types.h>


ptrdiff_t ptrdiff__id( ptrdiff_t const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

ptrdiff_t ptrdiff__min_bound( void ) { return PTRDIFF_MIN; }
ptrdiff_t ptrdiff__max_bound( void ) { return PTRDIFF_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
ptrdiff__equal(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x == y;
}


bool
ptrdiff__not_equal(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
ptrdiff__compare(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( x > y ) - ( x < y );
}


bool
ptrdiff__less_than(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x < y;
}


bool
ptrdiff__less_than_or_eq(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x <= y;
}


bool
ptrdiff__greater_than_or_eq(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x >= y;
}


bool
ptrdiff__greater_than(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x > y;
}


ptrdiff_t
ptrdiff__min2(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( x < y ) ? x : y;
}


ptrdiff_t
ptrdiff__max2(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( x > y ) ? x : y;
}


ptrdiff_t
ptrdiff__min_n(
        size_t const n,
        ptrdiff_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    ptrdiff_t min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = ptrdiff__min2( min, xs[ i ] );
    }
    return min;
}


ptrdiff_t
ptrdiff__max_n(
        size_t const n,
        ptrdiff_t const * const xs )
{ ASSERT( n != 0, xs != NULL );
    ptrdiff_t max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = ptrdiff__max2( max, xs[ i ] );
    }
    return max;
}


ptrdiff_t
ptrdiff__clamp(
        ptrdiff_t const lower,
        ptrdiff_t const upper,
        ptrdiff_t const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


ptrdiff_t
ptrdiff__succ( ptrdiff_t const x )
{ ASSERT( x != ptrdiff__max_bound() );
    return x + 1;
}


ptrdiff_t
ptrdiff__succ_b( ptrdiff_t const x )
{
    return ( x == ptrdiff__max_bound() ) ? x : ( x + 1 );
}


ptrdiff_t
ptrdiff__pred( ptrdiff_t const x )
{ ASSERT( x != ptrdiff__min_bound() );
    return x - 1;
}


ptrdiff_t
ptrdiff__pred_b( ptrdiff_t const x )
{
    return ( x == ptrdiff__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool ptrdiff__is_signed( void ) { return true; }


bool
ptrdiff__add_would_underflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return y < 0 && x < ( ptrdiff__min_bound() - y );
}


bool
ptrdiff__add_would_overflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return y > 0 && x > ( ptrdiff__max_bound() - y );
}


bool
ptrdiff__can_add(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return !ptrdiff__add_would_underflow( x, y )
        && !ptrdiff__add_would_overflow( x, y );
}


bool
ptrdiff__sub_would_underflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return y > 0 && x < ( ptrdiff__min_bound() + y );
}


bool
ptrdiff__sub_would_overflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return y < 0 && x > ( ptrdiff__max_bound() + y );
}


bool
ptrdiff__can_sub(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return !ptrdiff__sub_would_underflow( x, y )
        && !ptrdiff__sub_would_overflow( x, y );
}


bool
ptrdiff__mul_would_underflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( ptrdiff__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( ptrdiff__min_bound() / y ) )
                              : false;
}


bool
ptrdiff__mul_would_overflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( ptrdiff__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( ptrdiff__max_bound() / x ) )
                              : false;
}


bool
ptrdiff__can_mul(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return !ptrdiff__mul_would_underflow( x, y )
        && !ptrdiff__mul_would_overflow( x, y );
}


bool
ptrdiff__div_would_underflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return false;
}


bool
ptrdiff__div_would_overflow(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return x == ptrdiff__min_bound() && y == -1;
}


bool
ptrdiff__can_div(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( y != 0 && !ptrdiff__div_would_overflow( x, y ) );
}


ptrdiff_t
ptrdiff__add(
        ptrdiff_t const x,
        ptrdiff_t const y )
{ ASSERT( ptrdiff__can_add( x, y ) );
    return x + y;
}


ptrdiff_t
ptrdiff__sub(
        ptrdiff_t const x,
        ptrdiff_t const y )
{ ASSERT( ptrdiff__can_sub( x, y ) );
    return x - y;
}


ptrdiff_t
ptrdiff__mul(
        ptrdiff_t const x,
        ptrdiff_t const y )
{ ASSERT( ptrdiff__can_mul( x, y ) );
    return x * y;
}


ptrdiff_t
ptrdiff__div(
        ptrdiff_t const x,
        ptrdiff_t const y )
{ ASSERT( ptrdiff__can_div( x, y ) );
    return x / y;
}


ptrdiff_t
ptrdiff__mod(
        ptrdiff_t const x,
        ptrdiff_t const y )
{ ASSERT( ptrdiff__can_div( x, y ) );
    return x % y;
}


ptrdiff_t
ptrdiff__negate( ptrdiff_t const x )
{ ASSERT( x != ptrdiff__min_bound() );
    return -x;
}


ptrdiff_t
ptrdiff__abs( ptrdiff_t const x )
{ ASSERT( x != ptrdiff__min_bound() );
    return ( x < 0 ) ? -x : x;
}


ptrdiff_t
ptrdiff__add_b(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    if ( ptrdiff__add_would_underflow( x, y ) ) {
        return ptrdiff__min_bound();
    } else if ( ptrdiff__add_would_overflow( x, y ) ) {
        return ptrdiff__max_bound();
    } else {
        return x + y;
    }
}


ptrdiff_t
ptrdiff__sub_b(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    if ( ptrdiff__sub_would_underflow( x, y ) ) {
        return ptrdiff__min_bound();
    } else if ( ptrdiff__sub_would_overflow( x, y ) ) {
        return ptrdiff__max_bound();
    } else {
        return x - y;
    }
}


ptrdiff_t
ptrdiff__mul_b(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    if ( ptrdiff__mul_would_underflow( x, y ) ) {
        return ptrdiff__min_bound();
    } else if ( ptrdiff__mul_would_overflow( x, y ) ) {
        return ptrdiff__max_bound();
    } else {
        return x * y;
    }
}


ptrdiff_t
ptrdiff__div_b(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return ptrdiff__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return ptrdiff__max_bound();
        }
    } else if ( ptrdiff__div_would_underflow( x, y ) ) {
        return ptrdiff__min_bound();
    } else if ( ptrdiff__div_would_overflow( x, y ) ) {
        return ptrdiff__max_bound();
    } else {
        return x / y;
    }
}


ptrdiff_t
ptrdiff__mod_b(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    if ( !ptrdiff__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


ptrdiff_t
ptrdiff__negate_b( ptrdiff_t const x )
{
    if ( x == ptrdiff__min_bound() ) {
        return ptrdiff__max_bound();
    } else {
        return -x;
    }
}


ptrdiff_t
ptrdiff__abs_b( ptrdiff_t const x )
{
    if ( x == ptrdiff__min_bound() ) {
        return ptrdiff__max_bound();
    } else {
        return ptrdiff__abs( x );
    }
}


bool
ptrdiff__same_sign(
        ptrdiff_t const x,
        ptrdiff_t const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool ptrdiff__is_negative   ( ptrdiff_t const x ) { return x < 0; }
bool ptrdiff__is_nonpositive( ptrdiff_t const x ) { return x <= 0; }
bool ptrdiff__is_zero       ( ptrdiff_t const x ) { return x == 0; }
bool ptrdiff__is_nonnegative( ptrdiff_t const x ) { return x >= 0; }
bool ptrdiff__is_positive   ( ptrdiff_t const x ) { return x > 0; }


ord
ptrdiff__compare_0( ptrdiff_t const x )
{
    return ptrdiff__compare( x, 0 );
}


bool ptrdiff__is_even( ptrdiff_t const x ) { return x % 2 == 0; }
bool ptrdiff__is_odd ( ptrdiff_t const x ) { return x % 2 == 1; }


ptrdiff_t ptrdiff__add_2( ptrdiff_t const x )
        { return ptrdiff__add( x, 2 ); }
ptrdiff_t ptrdiff__sub_2( ptrdiff_t const x )
        { return ptrdiff__sub( x, 2 ); }
ptrdiff_t ptrdiff__mul_2( ptrdiff_t const x )
        { return ptrdiff__mul( x, 2 ); }
ptrdiff_t ptrdiff__div_2( ptrdiff_t const x )
        { return ptrdiff__div( x, 2 ); }
ptrdiff_t ptrdiff__mod_2( ptrdiff_t const x )
        { return ptrdiff__mod( x, 2 ); }


ptrdiff_t ptrdiff__mul_10( ptrdiff_t const x )
        { return ptrdiff__mul( x, 10 ); }
ptrdiff_t ptrdiff__div_10( ptrdiff_t const x )
        { return ptrdiff__div( x, 10 ); }


ptrdiff_t ptrdiff__add_b_2( ptrdiff_t const x )
        { return ptrdiff__add_b( x, 2 ); }
ptrdiff_t ptrdiff__sub_b_2( ptrdiff_t const x )
        { return ptrdiff__sub_b( x, 2 ); }
ptrdiff_t ptrdiff__mul_b_2( ptrdiff_t const x )
        { return ptrdiff__mul_b( x, 2 ); }
ptrdiff_t ptrdiff__mul_b_10( ptrdiff_t const x )
        { return ptrdiff__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

ptrdiff_t
ptrdiff__from_str( char const * const str )
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
    } else if ( x < ptrdiff__min_bound()
             || x > ptrdiff__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

