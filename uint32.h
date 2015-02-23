
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


#ifndef LIBBASE_UINT32_H
#define LIBBASE_UINT32_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_uint32 {
    uint32_t value;
    bool nothing;
} Maybe_uint32;


typedef struct result_uint32 {
    uint32_t value;
    int error;
} Result_uint32;


typedef struct arrayc_uint32 {
    uint32_t const * e;
    size_t length;
} ArrayC_uint32;


typedef struct arraym_uint32 {
    uint32_t * e;
    size_t length;
} ArrayM_uint32;


typedef struct vec_uint32 {
    uint32_t * e;
    size_t length;
    size_t capacity;
} Vec_uint32;


uint32_t uint32__id( uint32_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

uint32_t uint32__min_bound( void );
// Returns `0`, as that's the minimum value representable by `uint32_t`.

uint32_t uint32__max_bound( void );
// Returns the maximum value representable by the `uint32_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool uint32__equal( uint32_t x, uint32_t y );
// Returns `true` if `x == y`, or `false` if not.

bool uint32__not_equal( uint32_t x, uint32_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord uint32__compare( uint32_t x, uint32_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uint32__less_than( uint32_t x, uint32_t y );
// Returns `true` if `x < y`, or `false` if not.

bool uint32__less_than_or_eq( uint32_t x, uint32_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool uint32__greater_than_or_eq( uint32_t x, uint32_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool uint32__greater_than( uint32_t x, uint32_t y );
// Returns `true` if `x > y`, or `false` if not.

uint32_t uint32__min2( uint32_t x, uint32_t y );
// Returns `x` if `x < y`, or `y` otherwise.

uint32_t uint32__max2( uint32_t x, uint32_t y );
// Returns `x` if `x > y`, or `y` otherwise.

uint32_t uint32__min_n( size_t n, uint32_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uint32_t uint32__max_n( size_t n, uint32_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uint32__min( ... ) \
    uint32__min_n( PP_COUNT( __VA_ARGS__ ), ( uint32_t[] ){ __VA_ARGS__ } )

// @public
#define uint32__max( ... ) \
    uint32__max_n( PP_COUNT( __VA_ARGS__ ), ( uint32_t[] ){ __VA_ARGS__ } )

uint32_t uint32__clamp( uint32_t lower, uint32_t upper, uint32_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`

bool uint32__in_range( uint32_t lower, uint32_t upper, uint32_t x );
// Returns `lower <= x && x <= upper`.

bool uint32__in_range_x( uint32_t lower, uint32_t upper, uint32_t x );
// Returns `lower < x && x < upper`.



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

uint32_t uint32__succ( uint32_t x );
// Returns `x + 1`.
// @requires x != uint32__max_bound()

uint32_t uint32__succ_b( uint32_t x );
// Returns `x + 1`, or `uint32__max_bound()` if
// `x == uint32__max_bound()`.

uint32_t uint32__pred( uint32_t x );
// Returns `x - 1`.
// @requires x != uint32__min_bound()

uint32_t uint32__pred_b( uint32_t x );
// Returns `x - 1`, or `uint32__min_bound()` if
// `x == uint32__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool uint32__is_signed( void );
// Returns `false`, because `uint32_t` values can't be negative.

bool uint32__add_would_underflow( uint32_t, uint32_t );
bool uint32__add_would_overflow( uint32_t, uint32_t );

bool uint32__can_add( uint32_t x, uint32_t y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool uint32__sub_would_underflow( uint32_t, uint32_t );
bool uint32__sub_would_overflow( uint32_t, uint32_t );

bool uint32__can_sub( uint32_t x, uint32_t y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool uint32__mul_would_underflow( uint32_t, uint32_t );
bool uint32__mul_would_overflow( uint32_t, uint32_t );

bool uint32__can_mul( uint32_t x, uint32_t y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool uint32__div_would_underflow( uint32_t, uint32_t );
bool uint32__div_would_overflow( uint32_t, uint32_t );

bool uint32__can_div( uint32_t x, uint32_t y );
// Returns the boolean that `y != 0`.

uint32_t uint32__add( uint32_t x, uint32_t y );
// Returns `x + y`, which may overflow.

uint32_t uint32__sub( uint32_t x, uint32_t y );
// Returns `x - y`, which may underflow.

uint32_t uint32__mul( uint32_t x, uint32_t y );
// Returns `x * y`, which may overflow.

uint32_t uint32__div( uint32_t x, uint32_t y );
// Returns `x / y`.
// @requires y != 0

uint32_t uint32__mod( uint32_t x, uint32_t y );
// Returns `x % y`.
// @requires y != 0

uint32_t uint32__negate( uint32_t x );
// Returns `-x`, which gives `uint32__max_bound() - x + 1`.

uint32_t uint32__abs( uint32_t x );
// Returns `x`, because it will never be negative.

uint32_t uint32__add_b( uint32_t x, uint32_t y );
// Returns: - `uint32__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

uint32_t uint32__sub_b( uint32_t x, uint32_t y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

uint32_t uint32__mul_b( uint32_t x, uint32_t y );
// Returns: - `uint32__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

uint32_t uint32__div_b( uint32_t x, uint32_t y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `uint32__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

uint32_t uint32__mod_b( uint32_t x, uint32_t y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

uint32_t uint32__negate_b( uint32_t x );
// Returns `uint32__negate( x )`.

uint32_t uint32__abs_b( uint32_t x );
// Returns `uint32__abs( x )`.

bool uint32__same_sign( uint32_t, uint32_t );
// Returns `true`, because `uint32_t` values will always have the same sign.

bool uint32__is_negative( uint32_t x );     // Returns `false`.
bool uint32__is_nonpositive( uint32_t x );  // Returns `x == 0`.
bool uint32__is_zero( uint32_t x );         // Returns `x == 0`.
bool uint32__is_nonzero( uint32_t x );      // Returns `x != 0`.
bool uint32__is_nonnegative( uint32_t x );  // Returns `true`.
bool uint32__is_positive( uint32_t x );     // Returns `x != 0`.

ord uint32__compare_0( uint32_t x );
// Returns `uint32__compare( x, 0 )`.

bool uint32__is_even( uint32_t x );  // Returns `x % 2 == 0`.
bool uint32__is_odd( uint32_t x );   // Returns `x % 2 == 1`.

uint32_t uint32__add_2( uint32_t );
uint32_t uint32__sub_2( uint32_t );
uint32_t uint32__mul_2( uint32_t );
uint32_t uint32__div_2( uint32_t );
uint32_t uint32__mod_2( uint32_t );

uint32_t uint32__mul_10( uint32_t );
uint32_t uint32__div_10( uint32_t );

uint32_t uint32__add_b_2( uint32_t );
uint32_t uint32__sub_b_2( uint32_t );
uint32_t uint32__mul_b_2( uint32_t );
uint32_t uint32__mul_b_10( uint32_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

uint32_t uint32__from_str( char const * str );
// Parses the given `str` to produce the contained `uint32_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `uint32_t`.


#endif // ifndef LIBBASE_UINT32_H

