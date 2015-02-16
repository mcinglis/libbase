
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


#include "char.h"

#include <libtypes/types.h>


char char__id( char const x ) { return x; }



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////


#include <limits.h>

char char__min_bound( void ) { return CHAR_MIN; }
char char__max_bound( void ) { return CHAR_MAX; }



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////


bool
char__equal(
        char const x,
        char const y )
{
    return x == y;
}


bool
char__not_equal(
        char const x,
        char const y )
{
    return x != y;
}



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////


#include <libmacro/assert.h>


ord
char__compare(
        char const x,
        char const y )
{
    return ( x > y ) - ( x < y );
}


bool
char__less_than(
        char const x,
        char const y )
{
    return x < y;
}


bool
char__less_than_or_eq(
        char const x,
        char const y )
{
    return x <= y;
}


bool
char__greater_than_or_eq(
        char const x,
        char const y )
{
    return x >= y;
}


bool
char__greater_than(
        char const x,
        char const y )
{
    return x > y;
}


char
char__min2(
        char const x,
        char const y )
{
    return ( x < y ) ? x : y;
}


char
char__max2(
        char const x,
        char const y )
{
    return ( x > y ) ? x : y;
}


char
char__min_n(
        size_t const n,
        char const * const xs )
{ ASSERT( n != 0, xs != NULL );
    char min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        min = char__min2( min, xs[ i ] );
    }
    return min;
}


char
char__max_n(
        size_t const n,
        char const * const xs )
{ ASSERT( n != 0, xs != NULL );
    char max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        max = char__max2( max, xs[ i ] );
    }
    return max;
}


char
char__clamp(
        char const lower,
        char const upper,
        char const x )
{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////


#include <libmacro/assert.h>


char
char__succ( char const x )
{ ASSERT( x != char__max_bound() );
    return x + 1;
}


char
char__succ_b( char const x )
{
    return ( x == char__max_bound() ) ? x : ( x + 1 );
}


char
char__pred( char const x )
{ ASSERT( x != char__min_bound() );
    return x - 1;
}


char
char__pred_b( char const x )
{
    return ( x == char__min_bound() ) ? x : ( x - 1 );
}



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////


bool char__is_signed( void ) { return true; }


bool
char__add_would_underflow(
        char const x,
        char const y )
{
    return y < 0 && x < ( char__min_bound() - y );
}


bool
char__add_would_overflow(
        char const x,
        char const y )
{
    return y > 0 && x > ( char__max_bound() - y );
}


bool
char__can_add(
        char const x,
        char const y )
{
    return !char__add_would_underflow( x, y )
        && !char__add_would_overflow( x, y );
}


bool
char__sub_would_underflow(
        char const x,
        char const y )
{
    return y > 0 && x < ( char__min_bound() + y );
}


bool
char__sub_would_overflow(
        char const x,
        char const y )
{
    return y < 0 && x > ( char__max_bound() + y );
}


bool
char__can_sub(
        char const x,
        char const y )
{
    return !char__sub_would_underflow( x, y )
        && !char__sub_would_overflow( x, y );
}


bool
char__mul_would_underflow(
        char const x,
        char const y )
{
    return ( x > 0 && y < 0 ) ? ( y < ( char__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( char__min_bound() / y ) )
                              : false;
}


bool
char__mul_would_overflow(
        char const x,
        char const y )
{
    return ( x > 0 && y > 0 ) ? ( x > ( char__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( char__max_bound() / x ) )
                              : false;
}


bool
char__can_mul(
        char const x,
        char const y )
{
    return !char__mul_would_underflow( x, y )
        && !char__mul_would_overflow( x, y );
}


bool
char__div_would_underflow(
        char const x,
        char const y )
{
    return false;
}


bool
char__div_would_overflow(
        char const x,
        char const y )
{
    return x == char__min_bound() && y == -1;
}


bool
char__can_div(
        char const x,
        char const y )
{
    return ( y != 0 && !char__div_would_overflow( x, y ) );
}


char
char__add(
        char const x,
        char const y )
{ ASSERT( char__can_add( x, y ) );
    return x + y;
}


char
char__sub(
        char const x,
        char const y )
{ ASSERT( char__can_sub( x, y ) );
    return x - y;
}


char
char__mul(
        char const x,
        char const y )
{ ASSERT( char__can_mul( x, y ) );
    return x * y;
}


char
char__div(
        char const x,
        char const y )
{ ASSERT( char__can_div( x, y ) );
    return x / y;
}


char
char__mod(
        char const x,
        char const y )
{ ASSERT( char__can_div( x, y ) );
    return x % y;
}


char
char__negate( char const x )
{ ASSERT( x != char__min_bound() );
    return -x;
}


char
char__abs( char const x )
{ ASSERT( x != char__min_bound() );
    return ( x < 0 ) ? -x : x;
}


char
char__add_b(
        char const x,
        char const y )
{
    if ( char__add_would_underflow( x, y ) ) {
        return char__min_bound();
    } else if ( char__add_would_overflow( x, y ) ) {
        return char__max_bound();
    } else {
        return x + y;
    }
}


char
char__sub_b(
        char const x,
        char const y )
{
    if ( char__sub_would_underflow( x, y ) ) {
        return char__min_bound();
    } else if ( char__sub_would_overflow( x, y ) ) {
        return char__max_bound();
    } else {
        return x - y;
    }
}


char
char__mul_b(
        char const x,
        char const y )
{
    if ( char__mul_would_underflow( x, y ) ) {
        return char__min_bound();
    } else if ( char__mul_would_overflow( x, y ) ) {
        return char__max_bound();
    } else {
        return x * y;
    }
}


char
char__div_b(
        char const x,
        char const y )
{
    if ( y == 0 ) {
        if ( x < 0 ) {
            return char__min_bound();
        } else if ( x == 0 ) {
            return 0;
        } else /* x > 0 */ {
            return char__max_bound();
        }
    } else if ( char__div_would_underflow( x, y ) ) {
        return char__min_bound();
    } else if ( char__div_would_overflow( x, y ) ) {
        return char__max_bound();
    } else {
        return x / y;
    }
}


char
char__mod_b(
        char const x,
        char const y )
{
    if ( !char__can_div( x, y ) ) {
        return 0;
    } else {
        return x % y;
    }
}


char
char__negate_b( char const x )
{
    if ( x == char__min_bound() ) {
        return char__max_bound();
    } else {
        return -x;
    }
}


char
char__abs_b( char const x )
{
    if ( x == char__min_bound() ) {
        return char__max_bound();
    } else {
        return char__abs( x );
    }
}


bool
char__same_sign(
        char const x,
        char const y )
{
    return ( x < 0 ) == ( y < 0 );
}


bool char__is_negative   ( char const x ) { return x < 0; }
bool char__is_nonpositive( char const x ) { return x <= 0; }
bool char__is_zero       ( char const x ) { return x == 0; }
bool char__is_nonnegative( char const x ) { return x >= 0; }
bool char__is_positive   ( char const x ) { return x > 0; }


ord
char__compare_0( char const x )
{
    return char__compare( x, 0 );
}


bool char__is_even( char const x ) { return x % 2 == 0; }
bool char__is_odd ( char const x ) { return x % 2 == 1; }


char char__add_2( char const x )
        { return char__add( x, 2 ); }
char char__sub_2( char const x )
        { return char__sub( x, 2 ); }
char char__mul_2( char const x )
        { return char__mul( x, 2 ); }
char char__div_2( char const x )
        { return char__div( x, 2 ); }
char char__mod_2( char const x )
        { return char__mod( x, 2 ); }


char char__mul_10( char const x )
        { return char__mul( x, 10 ); }
char char__div_10( char const x )
        { return char__div( x, 10 ); }


char char__add_b_2( char const x )
        { return char__add_b( x, 2 ); }
char char__sub_b_2( char const x )
        { return char__sub_b( x, 2 ); }
char char__mul_b_2( char const x )
        { return char__mul_b( x, 2 ); }
char char__mul_b_10( char const x )
        { return char__mul_b( x, 10 ); }



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////


#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

char
char__from_str( char const * const str )
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
    } else if ( x < char__min_bound()
             || x > char__max_bound() ) {
        errno = ERANGE;
        return 0;
    } else {
        return x;
    }
}

