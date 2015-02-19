
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


#ifndef LIBBASE_UINT16_H
#define LIBBASE_UINT16_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_uint16 {
    uint16_t value;
    bool nothing;
} Maybe_uint16;


typedef struct result_uint16 {
    uint16_t value;
    int error;
} Result_uint16;


typedef struct arrayc_uint16 {
    uint16_t const * e;
    size_t capacity;
} ArrayC_uint16;


typedef struct arraym_uint16 {
    uint16_t * e;
    size_t capacity;
} ArrayM_uint16;


typedef struct vec_uint16 {
    uint16_t * e;
    size_t length;
    size_t capacity;
} Vec_uint16;


uint16_t uint16__id( uint16_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

uint16_t uint16__min_bound( void );
// Returns `0`, as that's the minimum value representable by `uint16_t`.

uint16_t uint16__max_bound( void );
// Returns the maximum value representable by the `uint16_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool uint16__equal( uint16_t x, uint16_t y );
// Returns `true` if `x == y`, or `false` if not.

bool uint16__not_equal( uint16_t x, uint16_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord uint16__compare( uint16_t x, uint16_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uint16__less_than( uint16_t x, uint16_t y );
// Returns `true` if `x < y`, or `false` if not.

bool uint16__less_than_or_eq( uint16_t x, uint16_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool uint16__greater_than_or_eq( uint16_t x, uint16_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool uint16__greater_than( uint16_t x, uint16_t y );
// Returns `true` if `x > y`, or `false` if not.

uint16_t uint16__min2( uint16_t x, uint16_t y );
// Returns `x` if `x < y`, or `y` otherwise.

uint16_t uint16__max2( uint16_t x, uint16_t y );
// Returns `x` if `x > y`, or `y` otherwise.

uint16_t uint16__min_n( size_t n, uint16_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uint16_t uint16__max_n( size_t n, uint16_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uint16__min( ... ) \
    uint16__min_n( PP_COUNT( __VA_ARGS__ ), ( uint16_t[] ){ __VA_ARGS__ } )

// @public
#define uint16__max( ... ) \
    uint16__max_n( PP_COUNT( __VA_ARGS__ ), ( uint16_t[] ){ __VA_ARGS__ } )

uint16_t uint16__clamp( uint16_t lower, uint16_t upper, uint16_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

uint16_t uint16__succ( uint16_t x );
// Returns `x + 1`.
// @requires x != uint16__max_bound()

uint16_t uint16__succ_b( uint16_t x );
// Returns `x + 1`, or `uint16__max_bound()` if
// `x == uint16__max_bound()`.

uint16_t uint16__pred( uint16_t x );
// Returns `x - 1`.
// @requires x != uint16__min_bound()

uint16_t uint16__pred_b( uint16_t x );
// Returns `x - 1`, or `uint16__min_bound()` if
// `x == uint16__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool uint16__is_signed( void );
// Returns `false`, because `uint16_t` values can't be negative.

bool uint16__add_would_underflow( uint16_t, uint16_t );
bool uint16__add_would_overflow( uint16_t, uint16_t );

bool uint16__can_add( uint16_t x, uint16_t y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool uint16__sub_would_underflow( uint16_t, uint16_t );
bool uint16__sub_would_overflow( uint16_t, uint16_t );

bool uint16__can_sub( uint16_t x, uint16_t y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool uint16__mul_would_underflow( uint16_t, uint16_t );
bool uint16__mul_would_overflow( uint16_t, uint16_t );

bool uint16__can_mul( uint16_t x, uint16_t y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool uint16__div_would_underflow( uint16_t, uint16_t );
bool uint16__div_would_overflow( uint16_t, uint16_t );

bool uint16__can_div( uint16_t x, uint16_t y );
// Returns the boolean that `y != 0`.

uint16_t uint16__add( uint16_t x, uint16_t y );
// Returns `x + y`, which may overflow.

uint16_t uint16__sub( uint16_t x, uint16_t y );
// Returns `x - y`, which may underflow.

uint16_t uint16__mul( uint16_t x, uint16_t y );
// Returns `x * y`, which may overflow.

uint16_t uint16__div( uint16_t x, uint16_t y );
// Returns `x / y`.
// @requires y != 0

uint16_t uint16__mod( uint16_t x, uint16_t y );
// Returns `x % y`.
// @requires y != 0

uint16_t uint16__negate( uint16_t x );
// Returns `-x`, which gives `uint16__max_bound() - x + 1`.

uint16_t uint16__abs( uint16_t x );
// Returns `x`, because it will never be negative.

uint16_t uint16__add_b( uint16_t x, uint16_t y );
// Returns: - `uint16__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

uint16_t uint16__sub_b( uint16_t x, uint16_t y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

uint16_t uint16__mul_b( uint16_t x, uint16_t y );
// Returns: - `uint16__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

uint16_t uint16__div_b( uint16_t x, uint16_t y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `uint16__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

uint16_t uint16__mod_b( uint16_t x, uint16_t y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

uint16_t uint16__negate_b( uint16_t x );
// Returns `uint16__negate( x )`.

uint16_t uint16__abs_b( uint16_t x );
// Returns `uint16__abs( x )`.

bool uint16__same_sign( uint16_t, uint16_t );
// Returns `true`, because `uint16_t` values will always have the same sign.

bool uint16__is_negative( uint16_t x );     // Returns `false`.
bool uint16__is_nonpositive( uint16_t x );  // Returns `x == 0`.
bool uint16__is_zero( uint16_t x );         // Returns `x == 0`.
bool uint16__is_nonzero( uint16_t x );      // Returns `x != 0`.
bool uint16__is_nonnegative( uint16_t x );  // Returns `true`.
bool uint16__is_positive( uint16_t x );     // Returns `x != 0`.

ord uint16__compare_0( uint16_t x );
// Returns `uint16__compare( x, 0 )`.

bool uint16__is_even( uint16_t x );  // Returns `x % 2 == 0`.
bool uint16__is_odd( uint16_t x );   // Returns `x % 2 == 1`.

uint16_t uint16__add_2( uint16_t );
uint16_t uint16__sub_2( uint16_t );
uint16_t uint16__mul_2( uint16_t );
uint16_t uint16__div_2( uint16_t );
uint16_t uint16__mod_2( uint16_t );

uint16_t uint16__mul_10( uint16_t );
uint16_t uint16__div_10( uint16_t );

uint16_t uint16__add_b_2( uint16_t );
uint16_t uint16__sub_b_2( uint16_t );
uint16_t uint16__mul_b_2( uint16_t );
uint16_t uint16__mul_b_10( uint16_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

uint16_t uint16__from_str( char const * str );
// Parses the given `str` to produce the contained `uint16_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `uint16_t`.


#endif // ifndef LIBBASE_UINT16_H

