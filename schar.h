
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


#ifndef LIBBASE_SCHAR_H
#define LIBBASE_SCHAR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_schar {
    schar value;
    bool nothing;
} Maybe_schar;


typedef struct result_schar {
    schar value;
    int error;
} Result_schar;


typedef struct arrayc_schar {
    schar const * e;
    size_t capacity;
} ArrayC_schar;


typedef struct arraym_schar {
    schar * e;
    size_t capacity;
} ArrayM_schar;


typedef struct vec_schar {
    schar * e;
    size_t length;
    size_t capacity;
} Vec_schar;


schar schar__id( schar x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

schar schar__min_bound( void );
// Returns the minimum value representable by the `schar` type.

schar schar__max_bound( void );
// Returns the maximum value representable by the `schar` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool schar__equal( schar x, schar y );
// Returns `true` if `x == y`, or `false` if not.

bool schar__not_equal( schar x, schar y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord schar__compare( schar x, schar y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool schar__less_than( schar x, schar y );
// Returns `true` if `x < y`, or `false` if not.

bool schar__less_than_or_eq( schar x, schar y );
// Returns `true` if `x <= y`, or `false` if not.

bool schar__greater_than_or_eq( schar x, schar y );
// Returns `true` if `x >= y`, or `false` if not.

bool schar__greater_than( schar x, schar y );
// Returns `true` if `x > y`, or `false` if not.

schar schar__min2( schar x, schar y );
// Returns `x` if `x < y`, or `y` otherwise.

schar schar__max2( schar x, schar y );
// Returns `x` if `x > y`, or `y` otherwise.

schar schar__min_n( size_t n, schar const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

schar schar__max_n( size_t n, schar const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define schar__min( ... ) \
    schar__min_n( PP_COUNT( __VA_ARGS__ ), ( schar[] ){ __VA_ARGS__ } )

// @public
#define schar__max( ... ) \
    schar__max_n( PP_COUNT( __VA_ARGS__ ), ( schar[] ){ __VA_ARGS__ } )

schar schar__clamp( schar lower, schar upper, schar x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

schar schar__succ( schar x );
// Returns `x + 1`.
// @requires x != schar__max_bound()

schar schar__succ_b( schar x );
// Returns `x + 1`, or `schar__max_bound()` if
// `x == schar__max_bound()`.

schar schar__pred( schar x );
// Returns `x - 1`.
// @requires x != schar__min_bound()

schar schar__pred_b( schar x );
// Returns `x - 1`, or `schar__min_bound()` if
// `x == schar__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool schar__is_signed( void );
// Returns `true`, because `schar` values can be negative.

bool schar__add_would_underflow( schar, schar );
bool schar__add_would_overflow( schar, schar );

bool schar__can_add( schar x, schar y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool schar__sub_would_underflow( schar, schar );
bool schar__sub_would_overflow( schar, schar );

bool schar__can_sub( schar x, schar y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool schar__mul_would_underflow( schar, schar );
bool schar__mul_would_overflow( schar, schar );

bool schar__can_mul( schar x, schar y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool schar__div_would_underflow( schar, schar );
bool schar__div_would_overflow( schar, schar );

bool schar__can_div( schar x, schar y );
// Returns the boolean that the behavior of `x / y` is well-defined.

schar schar__add( schar x, schar y );
// Returns `x + y`.
// @requires schar__can_add( x, y )

schar schar__sub( schar x, schar y );
// Returns `x - y`.
// @requires schar__can_sub( x, y )

schar schar__mul( schar x, schar y );
// Returns `x * y`.
// @requires schar__can_mul( x, y )

schar schar__div( schar x, schar y );
// Returns `x / y`.
// @requires schar__can_div( x, y )

schar schar__mod( schar x, schar y );
// Returns `x % y`.
// @requires schar__can_div( x, y )

schar schar__negate( schar x );
// Returns `-x`.
// @requires x != schar__min_bound()

schar schar__abs( schar x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != schar__min_bound()

schar schar__add_b( schar x, schar y );
// Returns: - `schar__min_bound()` if `x + y` would underflow;
//          - `schar__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

schar schar__sub_b( schar x, schar y );
// Returns: - `schar__min_bound()` if `x - y` would underflow;
//          - `schar__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

schar schar__mul_b( schar x, schar y );
// Returns: - `schar__min_bound()` if `x * y` would underflow;
//          - `schar__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

schar schar__div_b( schar x, schar y );
// If `y == 0`, returns: - `schar__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `schar__max_bound()` if `x > 0`;
// Otherwise, returns: - `schar__min_bound()` if
//                         `schar__div_would_underflow( x, y )`;
//                     - `schar__max_bound()` if
//                         `schar__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

schar schar__mod_b( schar x, schar y );
// Returns: - `0` if `!schar__can_div( x, y )`;
//          - `x % y` otherwise.

schar schar__negate_b( schar x );
// Returns: - `schar__max_bound()` if `x == schar__min_bound()`;
//          - `-x` otherwise.

schar schar__abs_b( schar x );
// Returns: - `schar__max_bound()` if `x == schar__min_bound()`;
//          - `schar__abs( x )` otherwise.

bool schar__same_sign( schar x, schar y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool schar__is_negative( schar x );     // Returns `x < 0`.
bool schar__is_nonpositive( schar x );  // Returns `x <= 0`.
bool schar__is_zero( schar x );         // Returns `x == 0`.
bool schar__is_nonzero( schar x );      // Returns `x != 0`.
bool schar__is_nonnegative( schar x );  // Returns `x >= 0`.
bool schar__is_positive( schar x );     // Returns `x > 0`.

ord schar__compare_0( schar x );
// Returns `schar__compare( x, 0 )`.

bool schar__is_even( schar x );     // Returns `x % 2 == 0`.
bool schar__is_odd( schar x );      // Returns `x % 2 == 1`.

schar schar__add_2( schar );
schar schar__sub_2( schar );
schar schar__mul_2( schar );
schar schar__div_2( schar );
schar schar__mod_2( schar );

schar schar__mul_10( schar );
schar schar__div_10( schar );

schar schar__add_b_2( schar );
schar schar__sub_b_2( schar );
schar schar__mul_b_2( schar );
schar schar__mul_b_10( schar );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

schar schar__from_str( char const * str );
// Parses the given `str` to produce the contained `schar` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `schar`.


#endif // ifndef LIBBASE_SCHAR_H

