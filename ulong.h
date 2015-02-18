
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


#ifndef LIBBASE_ULONG_H
#define LIBBASE_ULONG_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_ulong {
    ulong value;
    bool nothing;
} Maybe_ulong;


typedef struct result_ulong {
    ulong value;
    int error;
} Result_ulong;


typedef struct arrayc_ulong {
    ulong const * e;
    size_t length;
} ArrayC_ulong;


typedef struct arraym_ulong {
    ulong * e;
    size_t length;
} ArrayM_ulong;


typedef struct vec_ulong {
    ulong * e;
    size_t length;
    size_t capacity;
} Vec_ulong;


ulong ulong__id( ulong x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

ulong ulong__min_bound( void );
// Returns `0`, as that's the minimum value representable by `ulong`.

ulong ulong__max_bound( void );
// Returns the maximum value representable by the `ulong` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool ulong__equal( ulong x, ulong y );
// Returns `true` if `x == y`, or `false` if not.

bool ulong__not_equal( ulong x, ulong y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord ulong__compare( ulong x, ulong y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ulong__less_than( ulong x, ulong y );
// Returns `true` if `x < y`, or `false` if not.

bool ulong__less_than_or_eq( ulong x, ulong y );
// Returns `true` if `x <= y`, or `false` if not.

bool ulong__greater_than_or_eq( ulong x, ulong y );
// Returns `true` if `x >= y`, or `false` if not.

bool ulong__greater_than( ulong x, ulong y );
// Returns `true` if `x > y`, or `false` if not.

ulong ulong__min2( ulong x, ulong y );
// Returns `x` if `x < y`, or `y` otherwise.

ulong ulong__max2( ulong x, ulong y );
// Returns `x` if `x > y`, or `y` otherwise.

ulong ulong__min_n( size_t n, ulong const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ulong ulong__max_n( size_t n, ulong const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ulong__min( ... ) \
    ulong__min_n( PP_COUNT( __VA_ARGS__ ), ( ulong[] ){ __VA_ARGS__ } )

// @public
#define ulong__max( ... ) \
    ulong__max_n( PP_COUNT( __VA_ARGS__ ), ( ulong[] ){ __VA_ARGS__ } )

ulong ulong__clamp( ulong lower, ulong upper, ulong x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

ulong ulong__succ( ulong x );
// Returns `x + 1`.
// @requires x != ulong__max_bound()

ulong ulong__succ_b( ulong x );
// Returns `x + 1`, or `ulong__max_bound()` if
// `x == ulong__max_bound()`.

ulong ulong__pred( ulong x );
// Returns `x - 1`.
// @requires x != ulong__min_bound()

ulong ulong__pred_b( ulong x );
// Returns `x - 1`, or `ulong__min_bound()` if
// `x == ulong__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool ulong__is_signed( void );
// Returns `false`, because `ulong` values can't be negative.

bool ulong__add_would_underflow( ulong, ulong );
bool ulong__add_would_overflow( ulong, ulong );

bool ulong__can_add( ulong x, ulong y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool ulong__sub_would_underflow( ulong, ulong );
bool ulong__sub_would_overflow( ulong, ulong );

bool ulong__can_sub( ulong x, ulong y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool ulong__mul_would_underflow( ulong, ulong );
bool ulong__mul_would_overflow( ulong, ulong );

bool ulong__can_mul( ulong x, ulong y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool ulong__div_would_underflow( ulong, ulong );
bool ulong__div_would_overflow( ulong, ulong );

bool ulong__can_div( ulong x, ulong y );
// Returns the boolean that `y != 0`.

ulong ulong__add( ulong x, ulong y );
// Returns `x + y`, which may overflow.

ulong ulong__sub( ulong x, ulong y );
// Returns `x - y`, which may underflow.

ulong ulong__mul( ulong x, ulong y );
// Returns `x * y`, which may overflow.

ulong ulong__div( ulong x, ulong y );
// Returns `x / y`.
// @requires y != 0

ulong ulong__mod( ulong x, ulong y );
// Returns `x % y`.
// @requires y != 0

ulong ulong__negate( ulong x );
// Returns `-x`, which gives `ulong__max_bound() - x + 1`.

ulong ulong__abs( ulong x );
// Returns `x`, because it will never be negative.

ulong ulong__add_b( ulong x, ulong y );
// Returns: - `ulong__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

ulong ulong__sub_b( ulong x, ulong y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

ulong ulong__mul_b( ulong x, ulong y );
// Returns: - `ulong__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

ulong ulong__div_b( ulong x, ulong y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `ulong__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

ulong ulong__mod_b( ulong x, ulong y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

ulong ulong__negate_b( ulong x );
// Returns `ulong__negate( x )`.

ulong ulong__abs_b( ulong x );
// Returns `ulong__abs( x )`.

bool ulong__same_sign( ulong, ulong );
// Returns `true`, because `ulong` values will always have the same sign.

bool ulong__is_negative( ulong x );     // Returns `false`.
bool ulong__is_nonpositive( ulong x );  // Returns `x == 0`.
bool ulong__is_zero( ulong x );         // Returns `x == 0`.
bool ulong__is_nonnegative( ulong x );  // Returns `true`.
bool ulong__is_positive( ulong x );     // Returns `x != 0`.

ord ulong__compare_0( ulong x );
// Returns `ulong__compare( x, 0 )`.

bool ulong__is_even( ulong x );  // Returns `x % 2 == 0`.
bool ulong__is_odd( ulong x );   // Returns `x % 2 == 1`.

ulong ulong__add_2( ulong );
ulong ulong__sub_2( ulong );
ulong ulong__mul_2( ulong );
ulong ulong__div_2( ulong );
ulong ulong__mod_2( ulong );

ulong ulong__mul_10( ulong );
ulong ulong__div_10( ulong );

ulong ulong__add_b_2( ulong );
ulong ulong__sub_b_2( ulong );
ulong ulong__mul_b_2( ulong );
ulong ulong__mul_b_10( ulong );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

ulong ulong__from_str( char const * str );
// Parses the given `str` to produce the contained `ulong` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `ulong`.


#endif // ifndef LIBBASE_ULONG_H

