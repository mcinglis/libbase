
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


#ifndef LIBBASE_LLONG_H
#define LIBBASE_LLONG_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_llong {
    llong value;
    bool nothing;
} Maybe_llong;


llong llong__id( llong x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

llong llong__min_bound( void );
// Returns the minimum value representable by the `llong` type.

llong llong__max_bound( void );
// Returns the maximum value representable by the `llong` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool llong__equal( llong x, llong y );
// Returns `true` if `x == y`, or `false` if not.

bool llong__not_equal( llong x, llong y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord llong__compare( llong x, llong y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool llong__less_than( llong x, llong y );
// Returns `true` if `x < y`, or `false` if not.

bool llong__less_than_or_eq( llong x, llong y );
// Returns `true` if `x <= y`, or `false` if not.

bool llong__greater_than_or_eq( llong x, llong y );
// Returns `true` if `x >= y`, or `false` if not.

bool llong__greater_than( llong x, llong y );
// Returns `true` if `x > y`, or `false` if not.

llong llong__min2( llong x, llong y );
// Returns `x` if `x < y`, or `y` otherwise.

llong llong__max2( llong x, llong y );
// Returns `x` if `x > y`, or `y` otherwise.

llong llong__min_n( size_t n, llong const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

llong llong__max_n( size_t n, llong const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define llong__min( ... ) \
    llong__min_n( PP_COUNT( __VA_ARGS__ ), ( llong[] ){ __VA_ARGS__ } )

// @public
#define llong__max( ... ) \
    llong__max_n( PP_COUNT( __VA_ARGS__ ), ( llong[] ){ __VA_ARGS__ } )

llong llong__clamp( llong lower, llong upper, llong x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

llong llong__succ( llong x );
// Returns `x + 1`.
// @requires x != llong__max_bound()

llong llong__succ_b( llong x );
// Returns `x + 1`, or `llong__max_bound()` if
// `x == llong__max_bound()`.

llong llong__pred( llong x );
// Returns `x - 1`.
// @requires x != llong__min_bound()

llong llong__pred_b( llong x );
// Returns `x - 1`, or `llong__min_bound()` if
// `x == llong__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool llong__is_signed( void );
// Returns `true`, because `llong` values can be negative.

bool llong__add_would_underflow( llong, llong );
bool llong__add_would_overflow( llong, llong );

bool llong__can_add( llong x, llong y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool llong__sub_would_underflow( llong, llong );
bool llong__sub_would_overflow( llong, llong );

bool llong__can_sub( llong x, llong y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool llong__mul_would_underflow( llong, llong );
bool llong__mul_would_overflow( llong, llong );

bool llong__can_mul( llong x, llong y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool llong__div_would_underflow( llong, llong );
bool llong__div_would_overflow( llong, llong );

bool llong__can_div( llong x, llong y );
// Returns the boolean that the behavior of `x / y` is well-defined.

llong llong__add( llong x, llong y );
// Returns `x + y`.
// @requires llong__can_add( x, y )

llong llong__sub( llong x, llong y );
// Returns `x - y`.
// @requires llong__can_sub( x, y )

llong llong__mul( llong x, llong y );
// Returns `x * y`.
// @requires llong__can_mul( x, y )

llong llong__div( llong x, llong y );
// Returns `x / y`.
// @requires llong__can_div( x, y )

llong llong__mod( llong x, llong y );
// Returns `x % y`.
// @requires llong__can_div( x, y )

llong llong__negate( llong x );
// Returns `-x`.
// @requires x != llong__min_bound()

llong llong__abs( llong x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != llong__min_bound()

llong llong__add_b( llong x, llong y );
// Returns: - `llong__min_bound()` if `x + y` would underflow;
//          - `llong__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

llong llong__sub_b( llong x, llong y );
// Returns: - `llong__min_bound()` if `x - y` would underflow;
//          - `llong__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

llong llong__mul_b( llong x, llong y );
// Returns: - `llong__min_bound()` if `x * y` would underflow;
//          - `llong__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

llong llong__div_b( llong x, llong y );
// If `y == 0`, returns: - `llong__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `llong__max_bound()` if `x > 0`;
// Otherwise, returns: - `llong__min_bound()` if
//                         `llong__div_would_underflow( x, y )`;
//                     - `llong__max_bound()` if
//                         `llong__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

llong llong__mod_b( llong x, llong y );
// Returns: - `0` if `!llong__can_div( x, y )`;
//          - `x % y` otherwise.

llong llong__negate_b( llong x );
// Returns: - `llong__max_bound()` if `x == llong__min_bound()`;
//          - `-x` otherwise.

llong llong__abs_b( llong x );
// Returns: - `llong__max_bound()` if `x == llong__min_bound()`;
//          - `llong__abs( x )` otherwise.

bool llong__same_sign( llong x, llong y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool llong__is_negative( llong x );     // Returns `x < 0`.
bool llong__is_nonpositive( llong x );  // Returns `x <= 0`.
bool llong__is_zero( llong x );         // Returns `x == 0`.
bool llong__is_nonnegative( llong x );  // Returns `x >= 0`.
bool llong__is_positive( llong x );     // Returns `x > 0`.

ord llong__compare_0( llong x );
// Returns `llong__compare( x, 0 )`.

bool llong__is_even( llong x );     // Returns `x % 2 == 0`.
bool llong__is_odd( llong x );      // Returns `x % 2 == 1`.

llong llong__add_2( llong );
llong llong__sub_2( llong );
llong llong__mul_2( llong );
llong llong__div_2( llong );
llong llong__mod_2( llong );

llong llong__mul_10( llong );
llong llong__div_10( llong );

llong llong__add_b_2( llong );
llong llong__sub_b_2( llong );
llong llong__mul_b_2( llong );
llong llong__mul_b_10( llong );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

llong llong__from_str( char const * str );
// Parses the given `str` to produce the contained `llong` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `llong`.


#endif // ifndef LIBBASE_LLONG_H

