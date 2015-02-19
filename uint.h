
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


#ifndef LIBBASE_UINT_H
#define LIBBASE_UINT_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_uint {
    uint value;
    bool nothing;
} Maybe_uint;


typedef struct result_uint {
    uint value;
    int error;
} Result_uint;


typedef struct arrayc_uint {
    uint const * e;
    size_t capacity;
} ArrayC_uint;


typedef struct arraym_uint {
    uint * e;
    size_t capacity;
} ArrayM_uint;


typedef struct vec_uint {
    uint * e;
    size_t length;
    size_t capacity;
} Vec_uint;


uint uint__id( uint x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

uint uint__min_bound( void );
// Returns `0`, as that's the minimum value representable by `uint`.

uint uint__max_bound( void );
// Returns the maximum value representable by the `uint` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool uint__equal( uint x, uint y );
// Returns `true` if `x == y`, or `false` if not.

bool uint__not_equal( uint x, uint y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord uint__compare( uint x, uint y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uint__less_than( uint x, uint y );
// Returns `true` if `x < y`, or `false` if not.

bool uint__less_than_or_eq( uint x, uint y );
// Returns `true` if `x <= y`, or `false` if not.

bool uint__greater_than_or_eq( uint x, uint y );
// Returns `true` if `x >= y`, or `false` if not.

bool uint__greater_than( uint x, uint y );
// Returns `true` if `x > y`, or `false` if not.

uint uint__min2( uint x, uint y );
// Returns `x` if `x < y`, or `y` otherwise.

uint uint__max2( uint x, uint y );
// Returns `x` if `x > y`, or `y` otherwise.

uint uint__min_n( size_t n, uint const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uint uint__max_n( size_t n, uint const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uint__min( ... ) \
    uint__min_n( PP_COUNT( __VA_ARGS__ ), ( uint[] ){ __VA_ARGS__ } )

// @public
#define uint__max( ... ) \
    uint__max_n( PP_COUNT( __VA_ARGS__ ), ( uint[] ){ __VA_ARGS__ } )

uint uint__clamp( uint lower, uint upper, uint x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

uint uint__succ( uint x );
// Returns `x + 1`.
// @requires x != uint__max_bound()

uint uint__succ_b( uint x );
// Returns `x + 1`, or `uint__max_bound()` if
// `x == uint__max_bound()`.

uint uint__pred( uint x );
// Returns `x - 1`.
// @requires x != uint__min_bound()

uint uint__pred_b( uint x );
// Returns `x - 1`, or `uint__min_bound()` if
// `x == uint__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool uint__is_signed( void );
// Returns `false`, because `uint` values can't be negative.

bool uint__add_would_underflow( uint, uint );
bool uint__add_would_overflow( uint, uint );

bool uint__can_add( uint x, uint y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool uint__sub_would_underflow( uint, uint );
bool uint__sub_would_overflow( uint, uint );

bool uint__can_sub( uint x, uint y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool uint__mul_would_underflow( uint, uint );
bool uint__mul_would_overflow( uint, uint );

bool uint__can_mul( uint x, uint y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool uint__div_would_underflow( uint, uint );
bool uint__div_would_overflow( uint, uint );

bool uint__can_div( uint x, uint y );
// Returns the boolean that `y != 0`.

uint uint__add( uint x, uint y );
// Returns `x + y`, which may overflow.

uint uint__sub( uint x, uint y );
// Returns `x - y`, which may underflow.

uint uint__mul( uint x, uint y );
// Returns `x * y`, which may overflow.

uint uint__div( uint x, uint y );
// Returns `x / y`.
// @requires y != 0

uint uint__mod( uint x, uint y );
// Returns `x % y`.
// @requires y != 0

uint uint__negate( uint x );
// Returns `-x`, which gives `uint__max_bound() - x + 1`.

uint uint__abs( uint x );
// Returns `x`, because it will never be negative.

uint uint__add_b( uint x, uint y );
// Returns: - `uint__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

uint uint__sub_b( uint x, uint y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

uint uint__mul_b( uint x, uint y );
// Returns: - `uint__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

uint uint__div_b( uint x, uint y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `uint__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

uint uint__mod_b( uint x, uint y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

uint uint__negate_b( uint x );
// Returns `uint__negate( x )`.

uint uint__abs_b( uint x );
// Returns `uint__abs( x )`.

bool uint__same_sign( uint, uint );
// Returns `true`, because `uint` values will always have the same sign.

bool uint__is_negative( uint x );     // Returns `false`.
bool uint__is_nonpositive( uint x );  // Returns `x == 0`.
bool uint__is_zero( uint x );         // Returns `x == 0`.
bool uint__is_nonzero( uint x );      // Returns `x != 0`.
bool uint__is_nonnegative( uint x );  // Returns `true`.
bool uint__is_positive( uint x );     // Returns `x != 0`.

ord uint__compare_0( uint x );
// Returns `uint__compare( x, 0 )`.

bool uint__is_even( uint x );  // Returns `x % 2 == 0`.
bool uint__is_odd( uint x );   // Returns `x % 2 == 1`.

uint uint__add_2( uint );
uint uint__sub_2( uint );
uint uint__mul_2( uint );
uint uint__div_2( uint );
uint uint__mod_2( uint );

uint uint__mul_10( uint );
uint uint__div_10( uint );

uint uint__add_b_2( uint );
uint uint__sub_b_2( uint );
uint uint__mul_b_2( uint );
uint uint__mul_b_10( uint );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

uint uint__from_str( char const * str );
// Parses the given `str` to produce the contained `uint` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `uint`.


#endif // ifndef LIBBASE_UINT_H

