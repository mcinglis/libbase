
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


#ifndef LIBBASE_INTMAX_H
#define LIBBASE_INTMAX_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_intmax {
    intmax_t value;
    bool nothing;
} Maybe_intmax;


typedef struct result_intmax {
    intmax_t value;
    int error;
} Result_intmax;


typedef struct arrayc_intmax {
    intmax_t const * e;
    size_t length;
} ArrayC_intmax;


typedef struct arraym_intmax {
    intmax_t * e;
    size_t length;
} ArrayM_intmax;


typedef struct vec_intmax {
    intmax_t * e;
    size_t length;
    size_t capacity;
} Vec_intmax;


intmax_t intmax__id( intmax_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

intmax_t intmax__min_bound( void );
// Returns the minimum value representable by the `intmax_t` type.

intmax_t intmax__max_bound( void );
// Returns the maximum value representable by the `intmax_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool intmax__equal( intmax_t x, intmax_t y );
// Returns `true` if `x == y`, or `false` if not.

bool intmax__not_equal( intmax_t x, intmax_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord intmax__compare( intmax_t x, intmax_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool intmax__less_than( intmax_t x, intmax_t y );
// Returns `true` if `x < y`, or `false` if not.

bool intmax__less_than_or_eq( intmax_t x, intmax_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool intmax__greater_than_or_eq( intmax_t x, intmax_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool intmax__greater_than( intmax_t x, intmax_t y );
// Returns `true` if `x > y`, or `false` if not.

intmax_t intmax__min2( intmax_t x, intmax_t y );
// Returns `x` if `x < y`, or `y` otherwise.

intmax_t intmax__max2( intmax_t x, intmax_t y );
// Returns `x` if `x > y`, or `y` otherwise.

intmax_t intmax__min_n( size_t n, intmax_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

intmax_t intmax__max_n( size_t n, intmax_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define intmax__min( ... ) \
    intmax__min_n( PP_COUNT( __VA_ARGS__ ), ( intmax_t[] ){ __VA_ARGS__ } )

// @public
#define intmax__max( ... ) \
    intmax__max_n( PP_COUNT( __VA_ARGS__ ), ( intmax_t[] ){ __VA_ARGS__ } )

intmax_t intmax__clamp( intmax_t lower, intmax_t upper, intmax_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`

bool intmax__in_range( intmax_t lower, intmax_t upper, intmax_t x );
// Returns `lower <= x && x <= upper`.

bool intmax__in_range_x( intmax_t lower, intmax_t upper, intmax_t x );
// Returns `lower < x && x < upper`.



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

intmax_t intmax__succ( intmax_t x );
// Returns `x + 1`.
// @requires x != intmax__max_bound()

intmax_t intmax__succ_b( intmax_t x );
// Returns `x + 1`, or `intmax__max_bound()` if
// `x == intmax__max_bound()`.

intmax_t intmax__pred( intmax_t x );
// Returns `x - 1`.
// @requires x != intmax__min_bound()

intmax_t intmax__pred_b( intmax_t x );
// Returns `x - 1`, or `intmax__min_bound()` if
// `x == intmax__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool intmax__is_signed( void );
// Returns `true`, because `intmax_t` values can be negative.

bool intmax__add_would_underflow( intmax_t, intmax_t );
bool intmax__add_would_overflow( intmax_t, intmax_t );

bool intmax__can_add( intmax_t x, intmax_t y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool intmax__sub_would_underflow( intmax_t, intmax_t );
bool intmax__sub_would_overflow( intmax_t, intmax_t );

bool intmax__can_sub( intmax_t x, intmax_t y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool intmax__mul_would_underflow( intmax_t, intmax_t );
bool intmax__mul_would_overflow( intmax_t, intmax_t );

bool intmax__can_mul( intmax_t x, intmax_t y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool intmax__div_would_underflow( intmax_t, intmax_t );
bool intmax__div_would_overflow( intmax_t, intmax_t );

bool intmax__can_div( intmax_t x, intmax_t y );
// Returns the boolean that the behavior of `x / y` is well-defined.

intmax_t intmax__add( intmax_t x, intmax_t y );
// Returns `x + y`.
// @requires intmax__can_add( x, y )

intmax_t intmax__sub( intmax_t x, intmax_t y );
// Returns `x - y`.
// @requires intmax__can_sub( x, y )

intmax_t intmax__mul( intmax_t x, intmax_t y );
// Returns `x * y`.
// @requires intmax__can_mul( x, y )

intmax_t intmax__div( intmax_t x, intmax_t y );
// Returns `x / y`.
// @requires intmax__can_div( x, y )

intmax_t intmax__mod( intmax_t x, intmax_t y );
// Returns `x % y`.
// @requires intmax__can_div( x, y )

intmax_t intmax__negate( intmax_t x );
// Returns `-x`.
// @requires x != intmax__min_bound()

intmax_t intmax__abs( intmax_t x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != intmax__min_bound()

intmax_t intmax__add_b( intmax_t x, intmax_t y );
// Returns: - `intmax__min_bound()` if `x + y` would underflow;
//          - `intmax__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

intmax_t intmax__sub_b( intmax_t x, intmax_t y );
// Returns: - `intmax__min_bound()` if `x - y` would underflow;
//          - `intmax__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

intmax_t intmax__mul_b( intmax_t x, intmax_t y );
// Returns: - `intmax__min_bound()` if `x * y` would underflow;
//          - `intmax__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

intmax_t intmax__div_b( intmax_t x, intmax_t y );
// If `y == 0`, returns: - `intmax__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `intmax__max_bound()` if `x > 0`;
// Otherwise, returns: - `intmax__min_bound()` if
//                         `intmax__div_would_underflow( x, y )`;
//                     - `intmax__max_bound()` if
//                         `intmax__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

intmax_t intmax__mod_b( intmax_t x, intmax_t y );
// Returns: - `0` if `!intmax__can_div( x, y )`;
//          - `x % y` otherwise.

intmax_t intmax__negate_b( intmax_t x );
// Returns: - `intmax__max_bound()` if `x == intmax__min_bound()`;
//          - `-x` otherwise.

intmax_t intmax__abs_b( intmax_t x );
// Returns: - `intmax__max_bound()` if `x == intmax__min_bound()`;
//          - `intmax__abs( x )` otherwise.

bool intmax__same_sign( intmax_t x, intmax_t y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool intmax__in_delta( intmax_t x, intmax_t delta, intmax_t y );
// Returns `( x - delta ) <= y && y <= ( x + delta )`, with the arithmetic
// being bounded.

bool intmax__in_delta_x( intmax_t x, intmax_t delta, intmax_t y );
// Returns `( x - delta ) < y && y < ( x + delta )`, with the arithmetic being
// bounded.

bool intmax__is_negative( intmax_t x );     // Returns `x < 0`.
bool intmax__is_nonpositive( intmax_t x );  // Returns `x <= 0`.
bool intmax__is_zero( intmax_t x );         // Returns `x == 0`.
bool intmax__is_nonzero( intmax_t x );      // Returns `x != 0`.
bool intmax__is_nonnegative( intmax_t x );  // Returns `x >= 0`.
bool intmax__is_positive( intmax_t x );     // Returns `x > 0`.

ord intmax__compare_0( intmax_t x );
// Returns `intmax__compare( x, 0 )`.

bool intmax__is_even( intmax_t x );     // Returns `x % 2 == 0`.
bool intmax__is_odd( intmax_t x );      // Returns `x % 2 == 1`.

intmax_t intmax__add_2( intmax_t );
intmax_t intmax__sub_2( intmax_t );
intmax_t intmax__mul_2( intmax_t );
intmax_t intmax__div_2( intmax_t );
intmax_t intmax__mod_2( intmax_t );

intmax_t intmax__mul_10( intmax_t );
intmax_t intmax__div_10( intmax_t );

intmax_t intmax__add_b_2( intmax_t );
intmax_t intmax__sub_b_2( intmax_t );
intmax_t intmax__mul_b_2( intmax_t );
intmax_t intmax__mul_b_10( intmax_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

intmax_t intmax__from_str( char const * str );
// Parses the given `str` to produce the contained `intmax_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `intmax_t`.


#endif // ifndef LIBBASE_INTMAX_H

