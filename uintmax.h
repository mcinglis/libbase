
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


#ifndef LIBBASE_UINTMAX_H
#define LIBBASE_UINTMAX_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_uintmax {
    uintmax_t value;
    bool nothing;
} Maybe_uintmax;


typedef struct result_uintmax {
    uintmax_t value;
    int error;
} Result_uintmax;


typedef struct arrayc_uintmax {
    uintmax_t const * e;
    size_t capacity;
} ArrayC_uintmax;


typedef struct arraym_uintmax {
    uintmax_t * e;
    size_t capacity;
} ArrayM_uintmax;


typedef struct vec_uintmax {
    uintmax_t * e;
    size_t length;
    size_t capacity;
} Vec_uintmax;


uintmax_t uintmax__id( uintmax_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

uintmax_t uintmax__min_bound( void );
// Returns `0`, as that's the minimum value representable by `uintmax_t`.

uintmax_t uintmax__max_bound( void );
// Returns the maximum value representable by the `uintmax_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool uintmax__equal( uintmax_t x, uintmax_t y );
// Returns `true` if `x == y`, or `false` if not.

bool uintmax__not_equal( uintmax_t x, uintmax_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord uintmax__compare( uintmax_t x, uintmax_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uintmax__less_than( uintmax_t x, uintmax_t y );
// Returns `true` if `x < y`, or `false` if not.

bool uintmax__less_than_or_eq( uintmax_t x, uintmax_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool uintmax__greater_than_or_eq( uintmax_t x, uintmax_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool uintmax__greater_than( uintmax_t x, uintmax_t y );
// Returns `true` if `x > y`, or `false` if not.

uintmax_t uintmax__min2( uintmax_t x, uintmax_t y );
// Returns `x` if `x < y`, or `y` otherwise.

uintmax_t uintmax__max2( uintmax_t x, uintmax_t y );
// Returns `x` if `x > y`, or `y` otherwise.

uintmax_t uintmax__min_n( size_t n, uintmax_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uintmax_t uintmax__max_n( size_t n, uintmax_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uintmax__min( ... ) \
    uintmax__min_n( PP_COUNT( __VA_ARGS__ ), ( uintmax_t[] ){ __VA_ARGS__ } )

// @public
#define uintmax__max( ... ) \
    uintmax__max_n( PP_COUNT( __VA_ARGS__ ), ( uintmax_t[] ){ __VA_ARGS__ } )

uintmax_t uintmax__clamp( uintmax_t lower, uintmax_t upper, uintmax_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

uintmax_t uintmax__succ( uintmax_t x );
// Returns `x + 1`.
// @requires x != uintmax__max_bound()

uintmax_t uintmax__succ_b( uintmax_t x );
// Returns `x + 1`, or `uintmax__max_bound()` if
// `x == uintmax__max_bound()`.

uintmax_t uintmax__pred( uintmax_t x );
// Returns `x - 1`.
// @requires x != uintmax__min_bound()

uintmax_t uintmax__pred_b( uintmax_t x );
// Returns `x - 1`, or `uintmax__min_bound()` if
// `x == uintmax__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool uintmax__is_signed( void );
// Returns `false`, because `uintmax_t` values can't be negative.

bool uintmax__add_would_underflow( uintmax_t, uintmax_t );
bool uintmax__add_would_overflow( uintmax_t, uintmax_t );

bool uintmax__can_add( uintmax_t x, uintmax_t y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool uintmax__sub_would_underflow( uintmax_t, uintmax_t );
bool uintmax__sub_would_overflow( uintmax_t, uintmax_t );

bool uintmax__can_sub( uintmax_t x, uintmax_t y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool uintmax__mul_would_underflow( uintmax_t, uintmax_t );
bool uintmax__mul_would_overflow( uintmax_t, uintmax_t );

bool uintmax__can_mul( uintmax_t x, uintmax_t y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool uintmax__div_would_underflow( uintmax_t, uintmax_t );
bool uintmax__div_would_overflow( uintmax_t, uintmax_t );

bool uintmax__can_div( uintmax_t x, uintmax_t y );
// Returns the boolean that `y != 0`.

uintmax_t uintmax__add( uintmax_t x, uintmax_t y );
// Returns `x + y`, which may overflow.

uintmax_t uintmax__sub( uintmax_t x, uintmax_t y );
// Returns `x - y`, which may underflow.

uintmax_t uintmax__mul( uintmax_t x, uintmax_t y );
// Returns `x * y`, which may overflow.

uintmax_t uintmax__div( uintmax_t x, uintmax_t y );
// Returns `x / y`.
// @requires y != 0

uintmax_t uintmax__mod( uintmax_t x, uintmax_t y );
// Returns `x % y`.
// @requires y != 0

uintmax_t uintmax__negate( uintmax_t x );
// Returns `-x`, which gives `uintmax__max_bound() - x + 1`.

uintmax_t uintmax__abs( uintmax_t x );
// Returns `x`, because it will never be negative.

uintmax_t uintmax__add_b( uintmax_t x, uintmax_t y );
// Returns: - `uintmax__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

uintmax_t uintmax__sub_b( uintmax_t x, uintmax_t y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

uintmax_t uintmax__mul_b( uintmax_t x, uintmax_t y );
// Returns: - `uintmax__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

uintmax_t uintmax__div_b( uintmax_t x, uintmax_t y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `uintmax__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

uintmax_t uintmax__mod_b( uintmax_t x, uintmax_t y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

uintmax_t uintmax__negate_b( uintmax_t x );
// Returns `uintmax__negate( x )`.

uintmax_t uintmax__abs_b( uintmax_t x );
// Returns `uintmax__abs( x )`.

bool uintmax__same_sign( uintmax_t, uintmax_t );
// Returns `true`, because `uintmax_t` values will always have the same sign.

bool uintmax__is_negative( uintmax_t x );     // Returns `false`.
bool uintmax__is_nonpositive( uintmax_t x );  // Returns `x == 0`.
bool uintmax__is_zero( uintmax_t x );         // Returns `x == 0`.
bool uintmax__is_nonzero( uintmax_t x );      // Returns `x != 0`.
bool uintmax__is_nonnegative( uintmax_t x );  // Returns `true`.
bool uintmax__is_positive( uintmax_t x );     // Returns `x != 0`.

ord uintmax__compare_0( uintmax_t x );
// Returns `uintmax__compare( x, 0 )`.

bool uintmax__is_even( uintmax_t x );  // Returns `x % 2 == 0`.
bool uintmax__is_odd( uintmax_t x );   // Returns `x % 2 == 1`.

uintmax_t uintmax__add_2( uintmax_t );
uintmax_t uintmax__sub_2( uintmax_t );
uintmax_t uintmax__mul_2( uintmax_t );
uintmax_t uintmax__div_2( uintmax_t );
uintmax_t uintmax__mod_2( uintmax_t );

uintmax_t uintmax__mul_10( uintmax_t );
uintmax_t uintmax__div_10( uintmax_t );

uintmax_t uintmax__add_b_2( uintmax_t );
uintmax_t uintmax__sub_b_2( uintmax_t );
uintmax_t uintmax__mul_b_2( uintmax_t );
uintmax_t uintmax__mul_b_10( uintmax_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

uintmax_t uintmax__from_str( char const * str );
// Parses the given `str` to produce the contained `uintmax_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `uintmax_t`.


#endif // ifndef LIBBASE_UINTMAX_H

