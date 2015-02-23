
// This file is the result of executing `genheader.py`. You should make changes
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


#ifndef LIBBASE_INT32_H
#define LIBBASE_INT32_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_int32 {
    int32_t value;
    bool nothing;
} Maybe_int32;


typedef struct result_int32 {
    int32_t value;
    int error;
} Result_int32;


typedef struct arrayc_int32 {
    int32_t const * e;
    size_t length;
} ArrayC_int32;


typedef struct arraym_int32 {
    int32_t * e;
    size_t length;
} ArrayM_int32;


typedef struct vec_int32 {
    int32_t * e;
    size_t length;
    size_t capacity;
} Vec_int32;


int32_t int32__id( int32_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

int32_t int32__min_bound( void );
// Returns the minimum value representable by the `int32_t` type.

int32_t int32__max_bound( void );
// Returns the maximum value representable by the `int32_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool int32__equal( int32_t x, int32_t y );
// Returns `true` if `x == y`, or `false` if not.

bool int32__not_equal( int32_t x, int32_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord int32__compare( int32_t x, int32_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool int32__less_than( int32_t x, int32_t y );
// Returns `true` if `x < y`, or `false` if not.

bool int32__less_than_or_eq( int32_t x, int32_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool int32__greater_than_or_eq( int32_t x, int32_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool int32__greater_than( int32_t x, int32_t y );
// Returns `true` if `x > y`, or `false` if not.

int32_t int32__min2( int32_t x, int32_t y );
// Returns `x` if `x < y`, or `y` otherwise.

int32_t int32__max2( int32_t x, int32_t y );
// Returns `x` if `x > y`, or `y` otherwise.

int32_t int32__min_n( size_t n, int32_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

int32_t int32__max_n( size_t n, int32_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define int32__min( ... ) \
    int32__min_n( PP_COUNT( __VA_ARGS__ ), ( int32_t[] ){ __VA_ARGS__ } )

// @public
#define int32__max( ... ) \
    int32__max_n( PP_COUNT( __VA_ARGS__ ), ( int32_t[] ){ __VA_ARGS__ } )

int32_t int32__clamp( int32_t lower, int32_t upper, int32_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`

bool int32__in_range( int32_t lower, int32_t upper, int32_t x );
// Returns `lower <= x && x <= upper`.

bool int32__in_range_x( int32_t lower, int32_t upper, int32_t x );
// Returns `lower < x && x < upper`.



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

int32_t int32__succ( int32_t x );
// Returns `x + 1`.
// @requires x != int32__max_bound()

int32_t int32__succ_b( int32_t x );
// Returns `x + 1`, or `int32__max_bound()` if
// `x == int32__max_bound()`.

int32_t int32__pred( int32_t x );
// Returns `x - 1`.
// @requires x != int32__min_bound()

int32_t int32__pred_b( int32_t x );
// Returns `x - 1`, or `int32__min_bound()` if
// `x == int32__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool int32__is_signed( void );
// Returns `true`, because `int32_t` values can be negative.

bool int32__add_would_underflow( int32_t, int32_t );
bool int32__add_would_overflow( int32_t, int32_t );

bool int32__can_add( int32_t x, int32_t y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool int32__sub_would_underflow( int32_t, int32_t );
bool int32__sub_would_overflow( int32_t, int32_t );

bool int32__can_sub( int32_t x, int32_t y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool int32__mul_would_underflow( int32_t, int32_t );
bool int32__mul_would_overflow( int32_t, int32_t );

bool int32__can_mul( int32_t x, int32_t y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool int32__div_would_underflow( int32_t, int32_t );
bool int32__div_would_overflow( int32_t, int32_t );

bool int32__can_div( int32_t x, int32_t y );
// Returns the boolean that the behavior of `x / y` is well-defined.

int32_t int32__add( int32_t x, int32_t y );
// Returns `x + y`.
// @requires int32__can_add( x, y )

int32_t int32__sub( int32_t x, int32_t y );
// Returns `x - y`.
// @requires int32__can_sub( x, y )

int32_t int32__mul( int32_t x, int32_t y );
// Returns `x * y`.
// @requires int32__can_mul( x, y )

int32_t int32__div( int32_t x, int32_t y );
// Returns `x / y`.
// @requires int32__can_div( x, y )

int32_t int32__mod( int32_t x, int32_t y );
// Returns `x % y`.
// @requires int32__can_div( x, y )

int32_t int32__negate( int32_t x );
// Returns `-x`.
// @requires x != int32__min_bound()

int32_t int32__abs( int32_t x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != int32__min_bound()

int32_t int32__add_b( int32_t x, int32_t y );
// Returns: - `int32__min_bound()` if `x + y` would underflow;
//          - `int32__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

int32_t int32__sub_b( int32_t x, int32_t y );
// Returns: - `int32__min_bound()` if `x - y` would underflow;
//          - `int32__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

int32_t int32__mul_b( int32_t x, int32_t y );
// Returns: - `int32__min_bound()` if `x * y` would underflow;
//          - `int32__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

int32_t int32__div_b( int32_t x, int32_t y );
// If `y == 0`, returns: - `int32__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `int32__max_bound()` if `x > 0`;
// Otherwise, returns: - `int32__min_bound()` if
//                         `int32__div_would_underflow( x, y )`;
//                     - `int32__max_bound()` if
//                         `int32__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

int32_t int32__mod_b( int32_t x, int32_t y );
// Returns: - `0` if `!int32__can_div( x, y )`;
//          - `x % y` otherwise.

int32_t int32__negate_b( int32_t x );
// Returns: - `int32__max_bound()` if `x == int32__min_bound()`;
//          - `-x` otherwise.

int32_t int32__abs_b( int32_t x );
// Returns: - `int32__max_bound()` if `x == int32__min_bound()`;
//          - `int32__abs( x )` otherwise.

bool int32__same_sign( int32_t x, int32_t y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool int32__in_delta( int32_t x, int32_t delta, int32_t y );
// Returns `( x - delta ) <= y && y <= ( x + delta )`, with the arithmetic
// being bounded.

bool int32__in_delta_x( int32_t x, int32_t delta, int32_t y );
// Returns `( x - delta ) < y && y < ( x + delta )`, with the arithmetic being
// bounded.

bool int32__is_negative( int32_t x );     // Returns `x < 0`.
bool int32__is_nonpositive( int32_t x );  // Returns `x <= 0`.
bool int32__is_zero( int32_t x );         // Returns `x == 0`.
bool int32__is_nonzero( int32_t x );      // Returns `x != 0`.
bool int32__is_nonnegative( int32_t x );  // Returns `x >= 0`.
bool int32__is_positive( int32_t x );     // Returns `x > 0`.

ord int32__compare_0( int32_t x );
// Returns `int32__compare( x, 0 )`.

bool int32__is_even( int32_t x );     // Returns `x % 2 == 0`.
bool int32__is_odd( int32_t x );      // Returns `x % 2 == 1`.

int32_t int32__add_2( int32_t );
int32_t int32__sub_2( int32_t );
int32_t int32__mul_2( int32_t );
int32_t int32__div_2( int32_t );
int32_t int32__mod_2( int32_t );

int32_t int32__mul_10( int32_t );
int32_t int32__div_10( int32_t );

int32_t int32__add_b_2( int32_t );
int32_t int32__sub_b_2( int32_t );
int32_t int32__mul_b_2( int32_t );
int32_t int32__mul_b_10( int32_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

int32_t int32__from_str( char const * str );
// Parses the given `str` to produce the contained `int32_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `int32_t`.


#endif // ifndef LIBBASE_INT32_H

