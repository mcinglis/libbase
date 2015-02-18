
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


#ifndef LIBBASE_UINT8_H
#define LIBBASE_UINT8_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_uint8 {
    uint8_t value;
    bool nothing;
} Maybe_uint8;


typedef struct result_uint8 {
    uint8_t value;
    int error;
} Result_uint8;


typedef struct arrayc_uint8 {
    uint8_t const * e;
    size_t length;
} ArrayC_uint8;


typedef struct arraym_uint8 {
    uint8_t * e;
    size_t length;
} ArrayM_uint8;


typedef struct vec_uint8 {
    uint8_t * e;
    size_t length;
    size_t capacity;
} Vec_uint8;


uint8_t uint8__id( uint8_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

uint8_t uint8__min_bound( void );
// Returns `0`, as that's the minimum value representable by `uint8_t`.

uint8_t uint8__max_bound( void );
// Returns the maximum value representable by the `uint8_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool uint8__equal( uint8_t x, uint8_t y );
// Returns `true` if `x == y`, or `false` if not.

bool uint8__not_equal( uint8_t x, uint8_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord uint8__compare( uint8_t x, uint8_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uint8__less_than( uint8_t x, uint8_t y );
// Returns `true` if `x < y`, or `false` if not.

bool uint8__less_than_or_eq( uint8_t x, uint8_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool uint8__greater_than_or_eq( uint8_t x, uint8_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool uint8__greater_than( uint8_t x, uint8_t y );
// Returns `true` if `x > y`, or `false` if not.

uint8_t uint8__min2( uint8_t x, uint8_t y );
// Returns `x` if `x < y`, or `y` otherwise.

uint8_t uint8__max2( uint8_t x, uint8_t y );
// Returns `x` if `x > y`, or `y` otherwise.

uint8_t uint8__min_n( size_t n, uint8_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uint8_t uint8__max_n( size_t n, uint8_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uint8__min( ... ) \
    uint8__min_n( PP_COUNT( __VA_ARGS__ ), ( uint8_t[] ){ __VA_ARGS__ } )

// @public
#define uint8__max( ... ) \
    uint8__max_n( PP_COUNT( __VA_ARGS__ ), ( uint8_t[] ){ __VA_ARGS__ } )

uint8_t uint8__clamp( uint8_t lower, uint8_t upper, uint8_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

uint8_t uint8__succ( uint8_t x );
// Returns `x + 1`.
// @requires x != uint8__max_bound()

uint8_t uint8__succ_b( uint8_t x );
// Returns `x + 1`, or `uint8__max_bound()` if
// `x == uint8__max_bound()`.

uint8_t uint8__pred( uint8_t x );
// Returns `x - 1`.
// @requires x != uint8__min_bound()

uint8_t uint8__pred_b( uint8_t x );
// Returns `x - 1`, or `uint8__min_bound()` if
// `x == uint8__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool uint8__is_signed( void );
// Returns `false`, because `uint8_t` values can't be negative.

bool uint8__add_would_underflow( uint8_t, uint8_t );
bool uint8__add_would_overflow( uint8_t, uint8_t );

bool uint8__can_add( uint8_t x, uint8_t y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool uint8__sub_would_underflow( uint8_t, uint8_t );
bool uint8__sub_would_overflow( uint8_t, uint8_t );

bool uint8__can_sub( uint8_t x, uint8_t y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool uint8__mul_would_underflow( uint8_t, uint8_t );
bool uint8__mul_would_overflow( uint8_t, uint8_t );

bool uint8__can_mul( uint8_t x, uint8_t y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool uint8__div_would_underflow( uint8_t, uint8_t );
bool uint8__div_would_overflow( uint8_t, uint8_t );

bool uint8__can_div( uint8_t x, uint8_t y );
// Returns the boolean that `y != 0`.

uint8_t uint8__add( uint8_t x, uint8_t y );
// Returns `x + y`, which may overflow.

uint8_t uint8__sub( uint8_t x, uint8_t y );
// Returns `x - y`, which may underflow.

uint8_t uint8__mul( uint8_t x, uint8_t y );
// Returns `x * y`, which may overflow.

uint8_t uint8__div( uint8_t x, uint8_t y );
// Returns `x / y`.
// @requires y != 0

uint8_t uint8__mod( uint8_t x, uint8_t y );
// Returns `x % y`.
// @requires y != 0

uint8_t uint8__negate( uint8_t x );
// Returns `-x`, which gives `uint8__max_bound() - x + 1`.

uint8_t uint8__abs( uint8_t x );
// Returns `x`, because it will never be negative.

uint8_t uint8__add_b( uint8_t x, uint8_t y );
// Returns: - `uint8__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

uint8_t uint8__sub_b( uint8_t x, uint8_t y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

uint8_t uint8__mul_b( uint8_t x, uint8_t y );
// Returns: - `uint8__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

uint8_t uint8__div_b( uint8_t x, uint8_t y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `uint8__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

uint8_t uint8__mod_b( uint8_t x, uint8_t y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

uint8_t uint8__negate_b( uint8_t x );
// Returns `uint8__negate( x )`.

uint8_t uint8__abs_b( uint8_t x );
// Returns `uint8__abs( x )`.

bool uint8__same_sign( uint8_t, uint8_t );
// Returns `true`, because `uint8_t` values will always have the same sign.

bool uint8__is_negative( uint8_t x );     // Returns `false`.
bool uint8__is_nonpositive( uint8_t x );  // Returns `x == 0`.
bool uint8__is_zero( uint8_t x );         // Returns `x == 0`.
bool uint8__is_nonnegative( uint8_t x );  // Returns `true`.
bool uint8__is_positive( uint8_t x );     // Returns `x != 0`.

ord uint8__compare_0( uint8_t x );
// Returns `uint8__compare( x, 0 )`.

bool uint8__is_even( uint8_t x );  // Returns `x % 2 == 0`.
bool uint8__is_odd( uint8_t x );   // Returns `x % 2 == 1`.

uint8_t uint8__add_2( uint8_t );
uint8_t uint8__sub_2( uint8_t );
uint8_t uint8__mul_2( uint8_t );
uint8_t uint8__div_2( uint8_t );
uint8_t uint8__mod_2( uint8_t );

uint8_t uint8__mul_10( uint8_t );
uint8_t uint8__div_10( uint8_t );

uint8_t uint8__add_b_2( uint8_t );
uint8_t uint8__sub_b_2( uint8_t );
uint8_t uint8__mul_b_2( uint8_t );
uint8_t uint8__mul_b_10( uint8_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

uint8_t uint8__from_str( char const * str );
// Parses the given `str` to produce the contained `uint8_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `uint8_t`.


#endif // ifndef LIBBASE_UINT8_H

