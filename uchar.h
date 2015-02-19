
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


#ifndef LIBBASE_UCHAR_H
#define LIBBASE_UCHAR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_uchar {
    uchar value;
    bool nothing;
} Maybe_uchar;


typedef struct result_uchar {
    uchar value;
    int error;
} Result_uchar;


typedef struct arrayc_uchar {
    uchar const * e;
    size_t capacity;
} ArrayC_uchar;


typedef struct arraym_uchar {
    uchar * e;
    size_t capacity;
} ArrayM_uchar;


typedef struct vec_uchar {
    uchar * e;
    size_t length;
    size_t capacity;
} Vec_uchar;


uchar uchar__id( uchar x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

uchar uchar__min_bound( void );
// Returns `0`, as that's the minimum value representable by `uchar`.

uchar uchar__max_bound( void );
// Returns the maximum value representable by the `uchar` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool uchar__equal( uchar x, uchar y );
// Returns `true` if `x == y`, or `false` if not.

bool uchar__not_equal( uchar x, uchar y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord uchar__compare( uchar x, uchar y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uchar__less_than( uchar x, uchar y );
// Returns `true` if `x < y`, or `false` if not.

bool uchar__less_than_or_eq( uchar x, uchar y );
// Returns `true` if `x <= y`, or `false` if not.

bool uchar__greater_than_or_eq( uchar x, uchar y );
// Returns `true` if `x >= y`, or `false` if not.

bool uchar__greater_than( uchar x, uchar y );
// Returns `true` if `x > y`, or `false` if not.

uchar uchar__min2( uchar x, uchar y );
// Returns `x` if `x < y`, or `y` otherwise.

uchar uchar__max2( uchar x, uchar y );
// Returns `x` if `x > y`, or `y` otherwise.

uchar uchar__min_n( size_t n, uchar const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uchar uchar__max_n( size_t n, uchar const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uchar__min( ... ) \
    uchar__min_n( PP_COUNT( __VA_ARGS__ ), ( uchar[] ){ __VA_ARGS__ } )

// @public
#define uchar__max( ... ) \
    uchar__max_n( PP_COUNT( __VA_ARGS__ ), ( uchar[] ){ __VA_ARGS__ } )

uchar uchar__clamp( uchar lower, uchar upper, uchar x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

uchar uchar__succ( uchar x );
// Returns `x + 1`.
// @requires x != uchar__max_bound()

uchar uchar__succ_b( uchar x );
// Returns `x + 1`, or `uchar__max_bound()` if
// `x == uchar__max_bound()`.

uchar uchar__pred( uchar x );
// Returns `x - 1`.
// @requires x != uchar__min_bound()

uchar uchar__pred_b( uchar x );
// Returns `x - 1`, or `uchar__min_bound()` if
// `x == uchar__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool uchar__is_signed( void );
// Returns `false`, because `uchar` values can't be negative.

bool uchar__add_would_underflow( uchar, uchar );
bool uchar__add_would_overflow( uchar, uchar );

bool uchar__can_add( uchar x, uchar y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool uchar__sub_would_underflow( uchar, uchar );
bool uchar__sub_would_overflow( uchar, uchar );

bool uchar__can_sub( uchar x, uchar y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool uchar__mul_would_underflow( uchar, uchar );
bool uchar__mul_would_overflow( uchar, uchar );

bool uchar__can_mul( uchar x, uchar y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool uchar__div_would_underflow( uchar, uchar );
bool uchar__div_would_overflow( uchar, uchar );

bool uchar__can_div( uchar x, uchar y );
// Returns the boolean that `y != 0`.

uchar uchar__add( uchar x, uchar y );
// Returns `x + y`, which may overflow.

uchar uchar__sub( uchar x, uchar y );
// Returns `x - y`, which may underflow.

uchar uchar__mul( uchar x, uchar y );
// Returns `x * y`, which may overflow.

uchar uchar__div( uchar x, uchar y );
// Returns `x / y`.
// @requires y != 0

uchar uchar__mod( uchar x, uchar y );
// Returns `x % y`.
// @requires y != 0

uchar uchar__negate( uchar x );
// Returns `-x`, which gives `uchar__max_bound() - x + 1`.

uchar uchar__abs( uchar x );
// Returns `x`, because it will never be negative.

uchar uchar__add_b( uchar x, uchar y );
// Returns: - `uchar__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

uchar uchar__sub_b( uchar x, uchar y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

uchar uchar__mul_b( uchar x, uchar y );
// Returns: - `uchar__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

uchar uchar__div_b( uchar x, uchar y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `uchar__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

uchar uchar__mod_b( uchar x, uchar y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

uchar uchar__negate_b( uchar x );
// Returns `uchar__negate( x )`.

uchar uchar__abs_b( uchar x );
// Returns `uchar__abs( x )`.

bool uchar__same_sign( uchar, uchar );
// Returns `true`, because `uchar` values will always have the same sign.

bool uchar__is_negative( uchar x );     // Returns `false`.
bool uchar__is_nonpositive( uchar x );  // Returns `x == 0`.
bool uchar__is_zero( uchar x );         // Returns `x == 0`.
bool uchar__is_nonzero( uchar x );      // Returns `x != 0`.
bool uchar__is_nonnegative( uchar x );  // Returns `true`.
bool uchar__is_positive( uchar x );     // Returns `x != 0`.

ord uchar__compare_0( uchar x );
// Returns `uchar__compare( x, 0 )`.

bool uchar__is_even( uchar x );  // Returns `x % 2 == 0`.
bool uchar__is_odd( uchar x );   // Returns `x % 2 == 1`.

uchar uchar__add_2( uchar );
uchar uchar__sub_2( uchar );
uchar uchar__mul_2( uchar );
uchar uchar__div_2( uchar );
uchar uchar__mod_2( uchar );

uchar uchar__mul_10( uchar );
uchar uchar__div_10( uchar );

uchar uchar__add_b_2( uchar );
uchar uchar__sub_b_2( uchar );
uchar uchar__mul_b_2( uchar );
uchar uchar__mul_b_10( uchar );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

uchar uchar__from_str( char const * str );
// Parses the given `str` to produce the contained `uchar` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `uchar`.


#endif // ifndef LIBBASE_UCHAR_H

