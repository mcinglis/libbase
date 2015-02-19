
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


#ifndef LIBBASE_INT_H
#define LIBBASE_INT_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_int {
    int value;
    bool nothing;
} Maybe_int;


typedef struct result_int {
    int value;
    int error;
} Result_int;


typedef struct arrayc_int {
    int const * e;
    size_t capacity;
} ArrayC_int;


typedef struct arraym_int {
    int * e;
    size_t capacity;
} ArrayM_int;


typedef struct vec_int {
    int * e;
    size_t length;
    size_t capacity;
} Vec_int;


int int__id( int x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

int int__min_bound( void );
// Returns the minimum value representable by the `int` type.

int int__max_bound( void );
// Returns the maximum value representable by the `int` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool int__equal( int x, int y );
// Returns `true` if `x == y`, or `false` if not.

bool int__not_equal( int x, int y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord int__compare( int x, int y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool int__less_than( int x, int y );
// Returns `true` if `x < y`, or `false` if not.

bool int__less_than_or_eq( int x, int y );
// Returns `true` if `x <= y`, or `false` if not.

bool int__greater_than_or_eq( int x, int y );
// Returns `true` if `x >= y`, or `false` if not.

bool int__greater_than( int x, int y );
// Returns `true` if `x > y`, or `false` if not.

int int__min2( int x, int y );
// Returns `x` if `x < y`, or `y` otherwise.

int int__max2( int x, int y );
// Returns `x` if `x > y`, or `y` otherwise.

int int__min_n( size_t n, int const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

int int__max_n( size_t n, int const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define int__min( ... ) \
    int__min_n( PP_COUNT( __VA_ARGS__ ), ( int[] ){ __VA_ARGS__ } )

// @public
#define int__max( ... ) \
    int__max_n( PP_COUNT( __VA_ARGS__ ), ( int[] ){ __VA_ARGS__ } )

int int__clamp( int lower, int upper, int x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

int int__succ( int x );
// Returns `x + 1`.
// @requires x != int__max_bound()

int int__succ_b( int x );
// Returns `x + 1`, or `int__max_bound()` if
// `x == int__max_bound()`.

int int__pred( int x );
// Returns `x - 1`.
// @requires x != int__min_bound()

int int__pred_b( int x );
// Returns `x - 1`, or `int__min_bound()` if
// `x == int__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool int__is_signed( void );
// Returns `true`, because `int` values can be negative.

bool int__add_would_underflow( int, int );
bool int__add_would_overflow( int, int );

bool int__can_add( int x, int y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool int__sub_would_underflow( int, int );
bool int__sub_would_overflow( int, int );

bool int__can_sub( int x, int y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool int__mul_would_underflow( int, int );
bool int__mul_would_overflow( int, int );

bool int__can_mul( int x, int y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool int__div_would_underflow( int, int );
bool int__div_would_overflow( int, int );

bool int__can_div( int x, int y );
// Returns the boolean that the behavior of `x / y` is well-defined.

int int__add( int x, int y );
// Returns `x + y`.
// @requires int__can_add( x, y )

int int__sub( int x, int y );
// Returns `x - y`.
// @requires int__can_sub( x, y )

int int__mul( int x, int y );
// Returns `x * y`.
// @requires int__can_mul( x, y )

int int__div( int x, int y );
// Returns `x / y`.
// @requires int__can_div( x, y )

int int__mod( int x, int y );
// Returns `x % y`.
// @requires int__can_div( x, y )

int int__negate( int x );
// Returns `-x`.
// @requires x != int__min_bound()

int int__abs( int x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != int__min_bound()

int int__add_b( int x, int y );
// Returns: - `int__min_bound()` if `x + y` would underflow;
//          - `int__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

int int__sub_b( int x, int y );
// Returns: - `int__min_bound()` if `x - y` would underflow;
//          - `int__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

int int__mul_b( int x, int y );
// Returns: - `int__min_bound()` if `x * y` would underflow;
//          - `int__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

int int__div_b( int x, int y );
// If `y == 0`, returns: - `int__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `int__max_bound()` if `x > 0`;
// Otherwise, returns: - `int__min_bound()` if
//                         `int__div_would_underflow( x, y )`;
//                     - `int__max_bound()` if
//                         `int__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

int int__mod_b( int x, int y );
// Returns: - `0` if `!int__can_div( x, y )`;
//          - `x % y` otherwise.

int int__negate_b( int x );
// Returns: - `int__max_bound()` if `x == int__min_bound()`;
//          - `-x` otherwise.

int int__abs_b( int x );
// Returns: - `int__max_bound()` if `x == int__min_bound()`;
//          - `int__abs( x )` otherwise.

bool int__same_sign( int x, int y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool int__is_negative( int x );     // Returns `x < 0`.
bool int__is_nonpositive( int x );  // Returns `x <= 0`.
bool int__is_zero( int x );         // Returns `x == 0`.
bool int__is_nonzero( int x );      // Returns `x != 0`.
bool int__is_nonnegative( int x );  // Returns `x >= 0`.
bool int__is_positive( int x );     // Returns `x > 0`.

ord int__compare_0( int x );
// Returns `int__compare( x, 0 )`.

bool int__is_even( int x );     // Returns `x % 2 == 0`.
bool int__is_odd( int x );      // Returns `x % 2 == 1`.

int int__add_2( int );
int int__sub_2( int );
int int__mul_2( int );
int int__div_2( int );
int int__mod_2( int );

int int__mul_10( int );
int int__div_10( int );

int int__add_b_2( int );
int int__sub_b_2( int );
int int__mul_b_2( int );
int int__mul_b_10( int );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

int int__from_str( char const * str );
// Parses the given `str` to produce the contained `int` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `int`.


#endif // ifndef LIBBASE_INT_H

