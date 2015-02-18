
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


#include "ushort.h"

#include <libtypes/types.h>


ushort ushort__id( ushort const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

ushort ushort__min_bound( void ) { return 0; }
ushort ushort__max_bound( void ) { return USHRT_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
ushort__equal(
        ushort const x,
        ushort const y )
{
    return x == y;
}


bool
ushort__not_equal(
        ushort const x,
        ushort const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
ushort__compare(
        ushort const x,
        ushort const y )
{
    return ( x > y ) - ( x < y );
}


bool
ushort__less_than(
        ushort const x,
        ushort const y )
{
    return x < y;
}


bool
ushort__less_than_or_eq(
        ushort const x,
        ushort const y )
{
    return x <= y;
}


bool
ushort__greater_than_or_eq(
        ushort const x,
        ushort const y )
{
    return x >= y;
}


bool
ushort__greater_than(
        ushort const x,
        ushort const y )
{
    return x > y;
}


ushort
ushort__min2(
        ushort const x,
        ushort const y )
{
    return ( x < y ) ? x : y;
}


ushort
ushort__max2(
        ushort const x,
        ushort const y )
{
    return ( x > y ) ? x : y;
}


ushort
ushort__min_n(
        size_t const n,
        ushort const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    ushort min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = ushort__min2( min, xs[ i ] );
    }
    return min;
}


ushort
ushort__max_n(
        size_t const n,
        ushort const * const xs )
{
    ASSERT( n != 0, xs != NULL );

    ushort max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = ushort__max2( max, xs[ i ] );
    }
    return max;
}


ushort
ushort__clamp(
        ushort const lower,
        ushort const upper,
        ushort const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


ushort
ushort__succ( ushort const x )
{
    ASSERT( x != ushort__max_bound() );

    return x + 1;
}


ushort
ushort__succ_b( ushort const x )
{
    return ( x == ushort__max_bound() ) ? x : ( x + 1 );
}


ushort
ushort__pred( ushort const x )
{
    ASSERT( x != ushort__min_bound() );

    return x - 1;
}


ushort
ushort__pred_b( ushort const x )
{
    return ( x == ushort__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool ushort__is_signed( void ) { return false; }


bool
ushort__add_would_underflow(
        ushort const x,
        ushort const y )
{
    return false;
}


bool
ushort__add_would_overflow(
        ushort const x,
        ushort const y )
{
    return ( x > ( ushort__max_bound() - y ) );
}


bool
ushort__can_add(
        ushort const x,
        ushort const y )
{
    return !ushort__add_would_overflow( x, y );
}


bool
ushort__sub_would_underflow(
        ushort const x,
        ushort const y )
{
    return ( x < y );
}


bool
ushort__sub_would_overflow(
        ushort const x,
        ushort const y )
{
    return false;
}


bool
ushort__can_sub(
        ushort const x,
        ushort const y )
{
    return !ushort__sub_would_underflow( x, y );
}


bool
ushort__mul_would_underflow(
        ushort const x,
        ushort const y )
{
    return false;
}


bool
ushort__mul_would_overflow(
        ushort const x,
        ushort const y )
{
    return ( x > ( ushort__max_bound() / y ) );
}


bool
ushort__can_mul(
        ushort const x,
        ushort const y )
{
    return !ushort__mul_would_overflow( x, y );
}


bool
ushort__div_would_underflow(
        ushort const x,
        ushort const y )
{
    return false;
}


bool
ushort__div_would_overflow(
        ushort const x,
        ushort const y )
{
    return false;
}


bool
ushort__can_div(
        ushort const x,
        ushort const y )
{
    return y != 0;
}


ushort
ushort__add(
        ushort const x,
        ushort const y )
{
    return x + y;
}


ushort
ushort__sub(
        ushort const x,
        ushort const y )
{
    return x - y;
}


ushort
ushort__mul(
        ushort const x,
        ushort const y )
{
    return x * y;
}


ushort
ushort__div(
        ushort const x,
        ushort const y )
{
    ASSERT( y != 0 );

    return x / y;
}


ushort
ushort__mod(
        ushort const x,
        ushort const y )
{
    ASSERT( y != 0 );

    return x % y;
}


ushort
ushort__negate( ushort const x )
{
    return -x;
}


ushort
ushort__abs( ushort const x )
{
    return x;
}


ushort
ushort__add_b(
        ushort const x,
        ushort const y )
{
    if ( ushort__add_would_overflow( x, y ) ) {
        return ushort__max_bound();
    } else {
        return x + y;
    }
}


ushort
ushort__sub_b(
        ushort const x,
        ushort const y )
{
    if ( ushort__sub_would_underflow( x, y ) ) {
        return 0;
    } else {
        return x - y;
    }
}


ushort
ushort__mul_b(
        ushort const x,
        ushort const y )
{
    if ( ushort__mul_would_overflow( x, y ) ) {
        return ushort__max_bound();
    } else {
        return x * y;
    }
}


ushort
ushort__div_b(
        ushort const x,
        ushort const y )
{
    if ( y == 0 ) {
        if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return ushort__max_bound();
        }
    } else {
        return x / y;
    }
}


ushort
ushort__mod_b(
        ushort const x,
        ushort const y )
{
    if ( y == 0 ) {
        return 0;
    } else {
        return x % y;
    }
}


ushort
ushort__negate_b( ushort const x )
{
    return ushort__negate( x );
}


ushort
ushort__abs_b( ushort const x )
{
    return ushort__abs( x );
}


bool
ushort__same_sign(
        ushort const x,
        ushort const y )
{
    return true;
}


bool ushort__is_negative   ( ushort const x ) { return false; }
bool ushort__is_nonpositive( ushort const x ) { return x == 0; }
bool ushort__is_zero       ( ushort const x ) { return x == 0; }
bool ushort__is_nonnegative( ushort const x ) { return true; }
bool ushort__is_positive   ( ushort const x ) { return x != 0; }


ord
ushort__compare_0( ushort const x )
{
    return ushort__compare( x, 0 );
}


bool ushort__is_even( ushort const x ) { return x % 2 == 0; }
bool ushort__is_odd ( ushort const x ) { return x % 2 == 1; }


ushort ushort__add_2( ushort const x )
        { return ushort__add( x, 2 ); }
ushort ushort__sub_2( ushort const x )
        { return ushort__sub( x, 2 ); }
ushort ushort__mul_2( ushort const x )
        { return ushort__mul( x, 2 ); }
ushort ushort__div_2( ushort const x )
        { return ushort__div( x, 2 ); }
ushort ushort__mod_2( ushort const x )
        { return ushort__mod( x, 2 ); }


ushort ushort__mul_10( ushort const x )
        { return ushort__mul( x, 10 ); }
ushort ushort__div_10( ushort const x )
        { return ushort__div( x, 10 ); }


ushort ushort__add_b_2( ushort const x )
        { return ushort__add_b( x, 2 ); }
ushort ushort__sub_b_2( ushort const x )
        { return ushort__sub_b( x, 2 ); }
ushort ushort__mul_b_2( ushort const x )
        { return ushort__mul_b( x, 2 ); }
ushort ushort__mul_b_10( ushort const x )
        { return ushort__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

ushort
ushort__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        errno = EINVAL;
        return 0;
    }
    errno = 0;
    char * end_ptr;
    ulong const x = strtoul( str, &end_ptr, 10 );
    if ( errno ) {
        return 0;
    } else if ( *end_ptr != '\0' ) {
        errno = EBADMSG;
        return 0;
    } else if ( x < ushort__min_bound()
             || x > ushort__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

