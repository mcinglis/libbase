
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


#ifndef LIBBASE_SIZE_H
#define LIBBASE_SIZE_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_size {
    size_t value;
    bool nothing;
} Maybe_size;


typedef struct result_size {
    size_t value;
    int error;
} Result_size;


typedef struct arrayc_size {
    size_t const * e;
    size_t capacity;
} ArrayC_size;


typedef struct arraym_size {
    size_t * e;
    size_t capacity;
} ArrayM_size;


typedef struct vec_size {
    size_t * e;
    size_t length;
    size_t capacity;
} Vec_size;


size_t size__id( size_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

size_t size__min_bound( void );
// Returns `0`, as that's the minimum value representable by `size_t`.

size_t size__max_bound( void );
// Returns the maximum value representable by the `size_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool size__equal( size_t x, size_t y );
// Returns `true` if `x == y`, or `false` if not.

bool size__not_equal( size_t x, size_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord size__compare( size_t x, size_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool size__less_than( size_t x, size_t y );
// Returns `true` if `x < y`, or `false` if not.

bool size__less_than_or_eq( size_t x, size_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool size__greater_than_or_eq( size_t x, size_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool size__greater_than( size_t x, size_t y );
// Returns `true` if `x > y`, or `false` if not.

size_t size__min2( size_t x, size_t y );
// Returns `x` if `x < y`, or `y` otherwise.

size_t size__max2( size_t x, size_t y );
// Returns `x` if `x > y`, or `y` otherwise.

size_t size__min_n( size_t n, size_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

size_t size__max_n( size_t n, size_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define size__min( ... ) \
    size__min_n( PP_COUNT( __VA_ARGS__ ), ( size_t[] ){ __VA_ARGS__ } )

// @public
#define size__max( ... ) \
    size__max_n( PP_COUNT( __VA_ARGS__ ), ( size_t[] ){ __VA_ARGS__ } )

size_t size__clamp( size_t lower, size_t upper, size_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

size_t size__succ( size_t x );
// Returns `x + 1`.
// @requires x != size__max_bound()

size_t size__succ_b( size_t x );
// Returns `x + 1`, or `size__max_bound()` if
// `x == size__max_bound()`.

size_t size__pred( size_t x );
// Returns `x - 1`.
// @requires x != size__min_bound()

size_t size__pred_b( size_t x );
// Returns `x - 1`, or `size__min_bound()` if
// `x == size__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool size__is_signed( void );
// Returns `false`, because `size_t` values can't be negative.

bool size__add_would_underflow( size_t, size_t );
bool size__add_would_overflow( size_t, size_t );

bool size__can_add( size_t x, size_t y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool size__sub_would_underflow( size_t, size_t );
bool size__sub_would_overflow( size_t, size_t );

bool size__can_sub( size_t x, size_t y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool size__mul_would_underflow( size_t, size_t );
bool size__mul_would_overflow( size_t, size_t );

bool size__can_mul( size_t x, size_t y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool size__div_would_underflow( size_t, size_t );
bool size__div_would_overflow( size_t, size_t );

bool size__can_div( size_t x, size_t y );
// Returns the boolean that `y != 0`.

size_t size__add( size_t x, size_t y );
// Returns `x + y`, which may overflow.

size_t size__sub( size_t x, size_t y );
// Returns `x - y`, which may underflow.

size_t size__mul( size_t x, size_t y );
// Returns `x * y`, which may overflow.

size_t size__div( size_t x, size_t y );
// Returns `x / y`.
// @requires y != 0

size_t size__mod( size_t x, size_t y );
// Returns `x % y`.
// @requires y != 0

size_t size__negate( size_t x );
// Returns `-x`, which gives `size__max_bound() - x + 1`.

size_t size__abs( size_t x );
// Returns `x`, because it will never be negative.

size_t size__add_b( size_t x, size_t y );
// Returns: - `size__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

size_t size__sub_b( size_t x, size_t y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

size_t size__mul_b( size_t x, size_t y );
// Returns: - `size__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

size_t size__div_b( size_t x, size_t y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `size__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

size_t size__mod_b( size_t x, size_t y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

size_t size__negate_b( size_t x );
// Returns `size__negate( x )`.

size_t size__abs_b( size_t x );
// Returns `size__abs( x )`.

bool size__same_sign( size_t, size_t );
// Returns `true`, because `size_t` values will always have the same sign.

bool size__is_negative( size_t x );     // Returns `false`.
bool size__is_nonpositive( size_t x );  // Returns `x == 0`.
bool size__is_zero( size_t x );         // Returns `x == 0`.
bool size__is_nonnegative( size_t x );  // Returns `true`.
bool size__is_positive( size_t x );     // Returns `x != 0`.

ord size__compare_0( size_t x );
// Returns `size__compare( x, 0 )`.

bool size__is_even( size_t x );  // Returns `x % 2 == 0`.
bool size__is_odd( size_t x );   // Returns `x % 2 == 1`.

size_t size__add_2( size_t );
size_t size__sub_2( size_t );
size_t size__mul_2( size_t );
size_t size__div_2( size_t );
size_t size__mod_2( size_t );

size_t size__mul_10( size_t );
size_t size__div_10( size_t );

size_t size__add_b_2( size_t );
size_t size__sub_b_2( size_t );
size_t size__mul_b_2( size_t );
size_t size__mul_b_10( size_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

size_t size__from_str( char const * str );
// Parses the given `str` to produce the contained `size_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `size_t`.


#endif // ifndef LIBBASE_SIZE_H

