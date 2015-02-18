
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


#ifndef LIBBASE_INT16_H
#define LIBBASE_INT16_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_int16 {
    int16_t value;
    bool nothing;
} Maybe_int16;


typedef struct result_int16 {
    int16_t value;
    int error;
} Result_int16;


typedef struct arrayc_int16 {
    int16_t const * e;
    size_t length;
} ArrayC_int16;


typedef struct arraym_int16 {
    int16_t * e;
    size_t length;
} ArrayM_int16;


typedef struct vec_int16 {
    int16_t * e;
    size_t length;
    size_t capacity;
} Vec_int16;


int16_t int16__id( int16_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

int16_t int16__min_bound( void );
// Returns the minimum value representable by the `int16_t` type.

int16_t int16__max_bound( void );
// Returns the maximum value representable by the `int16_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool int16__equal( int16_t x, int16_t y );
// Returns `true` if `x == y`, or `false` if not.

bool int16__not_equal( int16_t x, int16_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord int16__compare( int16_t x, int16_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool int16__less_than( int16_t x, int16_t y );
// Returns `true` if `x < y`, or `false` if not.

bool int16__less_than_or_eq( int16_t x, int16_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool int16__greater_than_or_eq( int16_t x, int16_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool int16__greater_than( int16_t x, int16_t y );
// Returns `true` if `x > y`, or `false` if not.

int16_t int16__min2( int16_t x, int16_t y );
// Returns `x` if `x < y`, or `y` otherwise.

int16_t int16__max2( int16_t x, int16_t y );
// Returns `x` if `x > y`, or `y` otherwise.

int16_t int16__min_n( size_t n, int16_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

int16_t int16__max_n( size_t n, int16_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define int16__min( ... ) \
    int16__min_n( PP_COUNT( __VA_ARGS__ ), ( int16_t[] ){ __VA_ARGS__ } )

// @public
#define int16__max( ... ) \
    int16__max_n( PP_COUNT( __VA_ARGS__ ), ( int16_t[] ){ __VA_ARGS__ } )

int16_t int16__clamp( int16_t lower, int16_t upper, int16_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

int16_t int16__succ( int16_t x );
// Returns `x + 1`.
// @requires x != int16__max_bound()

int16_t int16__succ_b( int16_t x );
// Returns `x + 1`, or `int16__max_bound()` if
// `x == int16__max_bound()`.

int16_t int16__pred( int16_t x );
// Returns `x - 1`.
// @requires x != int16__min_bound()

int16_t int16__pred_b( int16_t x );
// Returns `x - 1`, or `int16__min_bound()` if
// `x == int16__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool int16__is_signed( void );
// Returns `true`, because `int16_t` values can be negative.

bool int16__add_would_underflow( int16_t, int16_t );
bool int16__add_would_overflow( int16_t, int16_t );

bool int16__can_add( int16_t x, int16_t y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool int16__sub_would_underflow( int16_t, int16_t );
bool int16__sub_would_overflow( int16_t, int16_t );

bool int16__can_sub( int16_t x, int16_t y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool int16__mul_would_underflow( int16_t, int16_t );
bool int16__mul_would_overflow( int16_t, int16_t );

bool int16__can_mul( int16_t x, int16_t y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool int16__div_would_underflow( int16_t, int16_t );
bool int16__div_would_overflow( int16_t, int16_t );

bool int16__can_div( int16_t x, int16_t y );
// Returns the boolean that the behavior of `x / y` is well-defined.

int16_t int16__add( int16_t x, int16_t y );
// Returns `x + y`.
// @requires int16__can_add( x, y )

int16_t int16__sub( int16_t x, int16_t y );
// Returns `x - y`.
// @requires int16__can_sub( x, y )

int16_t int16__mul( int16_t x, int16_t y );
// Returns `x * y`.
// @requires int16__can_mul( x, y )

int16_t int16__div( int16_t x, int16_t y );
// Returns `x / y`.
// @requires int16__can_div( x, y )

int16_t int16__mod( int16_t x, int16_t y );
// Returns `x % y`.
// @requires int16__can_div( x, y )

int16_t int16__negate( int16_t x );
// Returns `-x`.
// @requires x != int16__min_bound()

int16_t int16__abs( int16_t x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != int16__min_bound()

int16_t int16__add_b( int16_t x, int16_t y );
// Returns: - `int16__min_bound()` if `x + y` would underflow;
//          - `int16__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

int16_t int16__sub_b( int16_t x, int16_t y );
// Returns: - `int16__min_bound()` if `x - y` would underflow;
//          - `int16__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

int16_t int16__mul_b( int16_t x, int16_t y );
// Returns: - `int16__min_bound()` if `x * y` would underflow;
//          - `int16__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

int16_t int16__div_b( int16_t x, int16_t y );
// If `y == 0`, returns: - `int16__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `int16__max_bound()` if `x > 0`;
// Otherwise, returns: - `int16__min_bound()` if
//                         `int16__div_would_underflow( x, y )`;
//                     - `int16__max_bound()` if
//                         `int16__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

int16_t int16__mod_b( int16_t x, int16_t y );
// Returns: - `0` if `!int16__can_div( x, y )`;
//          - `x % y` otherwise.

int16_t int16__negate_b( int16_t x );
// Returns: - `int16__max_bound()` if `x == int16__min_bound()`;
//          - `-x` otherwise.

int16_t int16__abs_b( int16_t x );
// Returns: - `int16__max_bound()` if `x == int16__min_bound()`;
//          - `int16__abs( x )` otherwise.

bool int16__same_sign( int16_t x, int16_t y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool int16__is_negative( int16_t x );     // Returns `x < 0`.
bool int16__is_nonpositive( int16_t x );  // Returns `x <= 0`.
bool int16__is_zero( int16_t x );         // Returns `x == 0`.
bool int16__is_nonnegative( int16_t x );  // Returns `x >= 0`.
bool int16__is_positive( int16_t x );     // Returns `x > 0`.

ord int16__compare_0( int16_t x );
// Returns `int16__compare( x, 0 )`.

bool int16__is_even( int16_t x );     // Returns `x % 2 == 0`.
bool int16__is_odd( int16_t x );      // Returns `x % 2 == 1`.

int16_t int16__add_2( int16_t );
int16_t int16__sub_2( int16_t );
int16_t int16__mul_2( int16_t );
int16_t int16__div_2( int16_t );
int16_t int16__mod_2( int16_t );

int16_t int16__mul_10( int16_t );
int16_t int16__div_10( int16_t );

int16_t int16__add_b_2( int16_t );
int16_t int16__sub_b_2( int16_t );
int16_t int16__mul_b_2( int16_t );
int16_t int16__mul_b_10( int16_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

int16_t int16__from_str( char const * str );
// Parses the given `str` to produce the contained `int16_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `int16_t`.


#endif // ifndef LIBBASE_INT16_H

