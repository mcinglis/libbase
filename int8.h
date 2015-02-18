
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


#ifndef LIBBASE_INT8_H
#define LIBBASE_INT8_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_int8 {
    int8_t value;
    bool nothing;
} Maybe_int8;


typedef struct result_int8 {
    int8_t value;
    int error;
} Result_int8;


typedef struct arrayc_int8 {
    int8_t const * e;
    size_t capacity;
} ArrayC_int8;


typedef struct arraym_int8 {
    int8_t * e;
    size_t capacity;
} ArrayM_int8;


typedef struct vec_int8 {
    int8_t * e;
    size_t length;
    size_t capacity;
} Vec_int8;


int8_t int8__id( int8_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

int8_t int8__min_bound( void );
// Returns the minimum value representable by the `int8_t` type.

int8_t int8__max_bound( void );
// Returns the maximum value representable by the `int8_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool int8__equal( int8_t x, int8_t y );
// Returns `true` if `x == y`, or `false` if not.

bool int8__not_equal( int8_t x, int8_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord int8__compare( int8_t x, int8_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool int8__less_than( int8_t x, int8_t y );
// Returns `true` if `x < y`, or `false` if not.

bool int8__less_than_or_eq( int8_t x, int8_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool int8__greater_than_or_eq( int8_t x, int8_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool int8__greater_than( int8_t x, int8_t y );
// Returns `true` if `x > y`, or `false` if not.

int8_t int8__min2( int8_t x, int8_t y );
// Returns `x` if `x < y`, or `y` otherwise.

int8_t int8__max2( int8_t x, int8_t y );
// Returns `x` if `x > y`, or `y` otherwise.

int8_t int8__min_n( size_t n, int8_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

int8_t int8__max_n( size_t n, int8_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define int8__min( ... ) \
    int8__min_n( PP_COUNT( __VA_ARGS__ ), ( int8_t[] ){ __VA_ARGS__ } )

// @public
#define int8__max( ... ) \
    int8__max_n( PP_COUNT( __VA_ARGS__ ), ( int8_t[] ){ __VA_ARGS__ } )

int8_t int8__clamp( int8_t lower, int8_t upper, int8_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

int8_t int8__succ( int8_t x );
// Returns `x + 1`.
// @requires x != int8__max_bound()

int8_t int8__succ_b( int8_t x );
// Returns `x + 1`, or `int8__max_bound()` if
// `x == int8__max_bound()`.

int8_t int8__pred( int8_t x );
// Returns `x - 1`.
// @requires x != int8__min_bound()

int8_t int8__pred_b( int8_t x );
// Returns `x - 1`, or `int8__min_bound()` if
// `x == int8__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool int8__is_signed( void );
// Returns `true`, because `int8_t` values can be negative.

bool int8__add_would_underflow( int8_t, int8_t );
bool int8__add_would_overflow( int8_t, int8_t );

bool int8__can_add( int8_t x, int8_t y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool int8__sub_would_underflow( int8_t, int8_t );
bool int8__sub_would_overflow( int8_t, int8_t );

bool int8__can_sub( int8_t x, int8_t y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool int8__mul_would_underflow( int8_t, int8_t );
bool int8__mul_would_overflow( int8_t, int8_t );

bool int8__can_mul( int8_t x, int8_t y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool int8__div_would_underflow( int8_t, int8_t );
bool int8__div_would_overflow( int8_t, int8_t );

bool int8__can_div( int8_t x, int8_t y );
// Returns the boolean that the behavior of `x / y` is well-defined.

int8_t int8__add( int8_t x, int8_t y );
// Returns `x + y`.
// @requires int8__can_add( x, y )

int8_t int8__sub( int8_t x, int8_t y );
// Returns `x - y`.
// @requires int8__can_sub( x, y )

int8_t int8__mul( int8_t x, int8_t y );
// Returns `x * y`.
// @requires int8__can_mul( x, y )

int8_t int8__div( int8_t x, int8_t y );
// Returns `x / y`.
// @requires int8__can_div( x, y )

int8_t int8__mod( int8_t x, int8_t y );
// Returns `x % y`.
// @requires int8__can_div( x, y )

int8_t int8__negate( int8_t x );
// Returns `-x`.
// @requires x != int8__min_bound()

int8_t int8__abs( int8_t x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != int8__min_bound()

int8_t int8__add_b( int8_t x, int8_t y );
// Returns: - `int8__min_bound()` if `x + y` would underflow;
//          - `int8__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

int8_t int8__sub_b( int8_t x, int8_t y );
// Returns: - `int8__min_bound()` if `x - y` would underflow;
//          - `int8__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

int8_t int8__mul_b( int8_t x, int8_t y );
// Returns: - `int8__min_bound()` if `x * y` would underflow;
//          - `int8__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

int8_t int8__div_b( int8_t x, int8_t y );
// If `y == 0`, returns: - `int8__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `int8__max_bound()` if `x > 0`;
// Otherwise, returns: - `int8__min_bound()` if
//                         `int8__div_would_underflow( x, y )`;
//                     - `int8__max_bound()` if
//                         `int8__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

int8_t int8__mod_b( int8_t x, int8_t y );
// Returns: - `0` if `!int8__can_div( x, y )`;
//          - `x % y` otherwise.

int8_t int8__negate_b( int8_t x );
// Returns: - `int8__max_bound()` if `x == int8__min_bound()`;
//          - `-x` otherwise.

int8_t int8__abs_b( int8_t x );
// Returns: - `int8__max_bound()` if `x == int8__min_bound()`;
//          - `int8__abs( x )` otherwise.

bool int8__same_sign( int8_t x, int8_t y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool int8__is_negative( int8_t x );     // Returns `x < 0`.
bool int8__is_nonpositive( int8_t x );  // Returns `x <= 0`.
bool int8__is_zero( int8_t x );         // Returns `x == 0`.
bool int8__is_nonnegative( int8_t x );  // Returns `x >= 0`.
bool int8__is_positive( int8_t x );     // Returns `x > 0`.

ord int8__compare_0( int8_t x );
// Returns `int8__compare( x, 0 )`.

bool int8__is_even( int8_t x );     // Returns `x % 2 == 0`.
bool int8__is_odd( int8_t x );      // Returns `x % 2 == 1`.

int8_t int8__add_2( int8_t );
int8_t int8__sub_2( int8_t );
int8_t int8__mul_2( int8_t );
int8_t int8__div_2( int8_t );
int8_t int8__mod_2( int8_t );

int8_t int8__mul_10( int8_t );
int8_t int8__div_10( int8_t );

int8_t int8__add_b_2( int8_t );
int8_t int8__sub_b_2( int8_t );
int8_t int8__mul_b_2( int8_t );
int8_t int8__mul_b_10( int8_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

int8_t int8__from_str( char const * str );
// Parses the given `str` to produce the contained `int8_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `int8_t`.


#endif // ifndef LIBBASE_INT8_H

