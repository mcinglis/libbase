
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


#ifndef LIBBASE_ULLONG_H
#define LIBBASE_ULLONG_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_ullong {
    ullong value;
    bool nothing;
} Maybe_ullong;


typedef struct result_ullong {
    ullong value;
    int error;
} Result_ullong;


typedef struct arrayc_ullong {
    ullong const * e;
    size_t length;
} ArrayC_ullong;


typedef struct arraym_ullong {
    ullong * e;
    size_t length;
} ArrayM_ullong;


typedef struct vec_ullong {
    ullong * e;
    size_t length;
    size_t capacity;
} Vec_ullong;


ullong ullong__id( ullong x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

ullong ullong__min_bound( void );
// Returns `0`, as that's the minimum value representable by `ullong`.

ullong ullong__max_bound( void );
// Returns the maximum value representable by the `ullong` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool ullong__equal( ullong x, ullong y );
// Returns `true` if `x == y`, or `false` if not.

bool ullong__not_equal( ullong x, ullong y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord ullong__compare( ullong x, ullong y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ullong__less_than( ullong x, ullong y );
// Returns `true` if `x < y`, or `false` if not.

bool ullong__less_than_or_eq( ullong x, ullong y );
// Returns `true` if `x <= y`, or `false` if not.

bool ullong__greater_than_or_eq( ullong x, ullong y );
// Returns `true` if `x >= y`, or `false` if not.

bool ullong__greater_than( ullong x, ullong y );
// Returns `true` if `x > y`, or `false` if not.

ullong ullong__min2( ullong x, ullong y );
// Returns `x` if `x < y`, or `y` otherwise.

ullong ullong__max2( ullong x, ullong y );
// Returns `x` if `x > y`, or `y` otherwise.

ullong ullong__min_n( size_t n, ullong const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ullong ullong__max_n( size_t n, ullong const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ullong__min( ... ) \
    ullong__min_n( PP_COUNT( __VA_ARGS__ ), ( ullong[] ){ __VA_ARGS__ } )

// @public
#define ullong__max( ... ) \
    ullong__max_n( PP_COUNT( __VA_ARGS__ ), ( ullong[] ){ __VA_ARGS__ } )

ullong ullong__clamp( ullong lower, ullong upper, ullong x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

ullong ullong__succ( ullong x );
// Returns `x + 1`.
// @requires x != ullong__max_bound()

ullong ullong__succ_b( ullong x );
// Returns `x + 1`, or `ullong__max_bound()` if
// `x == ullong__max_bound()`.

ullong ullong__pred( ullong x );
// Returns `x - 1`.
// @requires x != ullong__min_bound()

ullong ullong__pred_b( ullong x );
// Returns `x - 1`, or `ullong__min_bound()` if
// `x == ullong__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool ullong__is_signed( void );
// Returns `false`, because `ullong` values can't be negative.

bool ullong__add_would_underflow( ullong, ullong );
bool ullong__add_would_overflow( ullong, ullong );

bool ullong__can_add( ullong x, ullong y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool ullong__sub_would_underflow( ullong, ullong );
bool ullong__sub_would_overflow( ullong, ullong );

bool ullong__can_sub( ullong x, ullong y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool ullong__mul_would_underflow( ullong, ullong );
bool ullong__mul_would_overflow( ullong, ullong );

bool ullong__can_mul( ullong x, ullong y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool ullong__div_would_underflow( ullong, ullong );
bool ullong__div_would_overflow( ullong, ullong );

bool ullong__can_div( ullong x, ullong y );
// Returns the boolean that `y != 0`.

ullong ullong__add( ullong x, ullong y );
// Returns `x + y`, which may overflow.

ullong ullong__sub( ullong x, ullong y );
// Returns `x - y`, which may underflow.

ullong ullong__mul( ullong x, ullong y );
// Returns `x * y`, which may overflow.

ullong ullong__div( ullong x, ullong y );
// Returns `x / y`.
// @requires y != 0

ullong ullong__mod( ullong x, ullong y );
// Returns `x % y`.
// @requires y != 0

ullong ullong__negate( ullong x );
// Returns `-x`, which gives `ullong__max_bound() - x + 1`.

ullong ullong__abs( ullong x );
// Returns `x`, because it will never be negative.

ullong ullong__add_b( ullong x, ullong y );
// Returns: - `ullong__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

ullong ullong__sub_b( ullong x, ullong y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

ullong ullong__mul_b( ullong x, ullong y );
// Returns: - `ullong__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

ullong ullong__div_b( ullong x, ullong y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `ullong__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

ullong ullong__mod_b( ullong x, ullong y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

ullong ullong__negate_b( ullong x );
// Returns `ullong__negate( x )`.

ullong ullong__abs_b( ullong x );
// Returns `ullong__abs( x )`.

bool ullong__same_sign( ullong, ullong );
// Returns `true`, because `ullong` values will always have the same sign.

bool ullong__is_negative( ullong x );     // Returns `false`.
bool ullong__is_nonpositive( ullong x );  // Returns `x == 0`.
bool ullong__is_zero( ullong x );         // Returns `x == 0`.
bool ullong__is_nonzero( ullong x );      // Returns `x != 0`.
bool ullong__is_nonnegative( ullong x );  // Returns `true`.
bool ullong__is_positive( ullong x );     // Returns `x != 0`.

ord ullong__compare_0( ullong x );
// Returns `ullong__compare( x, 0 )`.

bool ullong__is_even( ullong x );  // Returns `x % 2 == 0`.
bool ullong__is_odd( ullong x );   // Returns `x % 2 == 1`.

ullong ullong__add_2( ullong );
ullong ullong__sub_2( ullong );
ullong ullong__mul_2( ullong );
ullong ullong__div_2( ullong );
ullong ullong__mod_2( ullong );

ullong ullong__mul_10( ullong );
ullong ullong__div_10( ullong );

ullong ullong__add_b_2( ullong );
ullong ullong__sub_b_2( ullong );
ullong ullong__mul_b_2( ullong );
ullong ullong__mul_b_10( ullong );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

ullong ullong__from_str( char const * str );
// Parses the given `str` to produce the contained `ullong` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `ullong`.


#endif // ifndef LIBBASE_ULLONG_H

