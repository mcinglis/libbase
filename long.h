
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


#ifndef LIBBASE_LONG_H
#define LIBBASE_LONG_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_long {
    long value;
    bool nothing;
} Maybe_long;


typedef struct result_long {
    long value;
    int error;
} Result_long;


typedef struct arrayc_long {
    long const * e;
    size_t capacity;
} ArrayC_long;


typedef struct arraym_long {
    long * e;
    size_t capacity;
} ArrayM_long;


typedef struct vec_long {
    long * e;
    size_t length;
    size_t capacity;
} Vec_long;


long long__id( long x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

long long__min_bound( void );
// Returns the minimum value representable by the `long` type.

long long__max_bound( void );
// Returns the maximum value representable by the `long` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool long__equal( long x, long y );
// Returns `true` if `x == y`, or `false` if not.

bool long__not_equal( long x, long y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord long__compare( long x, long y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool long__less_than( long x, long y );
// Returns `true` if `x < y`, or `false` if not.

bool long__less_than_or_eq( long x, long y );
// Returns `true` if `x <= y`, or `false` if not.

bool long__greater_than_or_eq( long x, long y );
// Returns `true` if `x >= y`, or `false` if not.

bool long__greater_than( long x, long y );
// Returns `true` if `x > y`, or `false` if not.

long long__min2( long x, long y );
// Returns `x` if `x < y`, or `y` otherwise.

long long__max2( long x, long y );
// Returns `x` if `x > y`, or `y` otherwise.

long long__min_n( size_t n, long const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

long long__max_n( size_t n, long const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define long__min( ... ) \
    long__min_n( PP_COUNT( __VA_ARGS__ ), ( long[] ){ __VA_ARGS__ } )

// @public
#define long__max( ... ) \
    long__max_n( PP_COUNT( __VA_ARGS__ ), ( long[] ){ __VA_ARGS__ } )

long long__clamp( long lower, long upper, long x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

long long__succ( long x );
// Returns `x + 1`.
// @requires x != long__max_bound()

long long__succ_b( long x );
// Returns `x + 1`, or `long__max_bound()` if
// `x == long__max_bound()`.

long long__pred( long x );
// Returns `x - 1`.
// @requires x != long__min_bound()

long long__pred_b( long x );
// Returns `x - 1`, or `long__min_bound()` if
// `x == long__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool long__is_signed( void );
// Returns `true`, because `long` values can be negative.

bool long__add_would_underflow( long, long );
bool long__add_would_overflow( long, long );

bool long__can_add( long x, long y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool long__sub_would_underflow( long, long );
bool long__sub_would_overflow( long, long );

bool long__can_sub( long x, long y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool long__mul_would_underflow( long, long );
bool long__mul_would_overflow( long, long );

bool long__can_mul( long x, long y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool long__div_would_underflow( long, long );
bool long__div_would_overflow( long, long );

bool long__can_div( long x, long y );
// Returns the boolean that the behavior of `x / y` is well-defined.

long long__add( long x, long y );
// Returns `x + y`.
// @requires long__can_add( x, y )

long long__sub( long x, long y );
// Returns `x - y`.
// @requires long__can_sub( x, y )

long long__mul( long x, long y );
// Returns `x * y`.
// @requires long__can_mul( x, y )

long long__div( long x, long y );
// Returns `x / y`.
// @requires long__can_div( x, y )

long long__mod( long x, long y );
// Returns `x % y`.
// @requires long__can_div( x, y )

long long__negate( long x );
// Returns `-x`.
// @requires x != long__min_bound()

long long__abs( long x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != long__min_bound()

long long__add_b( long x, long y );
// Returns: - `long__min_bound()` if `x + y` would underflow;
//          - `long__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

long long__sub_b( long x, long y );
// Returns: - `long__min_bound()` if `x - y` would underflow;
//          - `long__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

long long__mul_b( long x, long y );
// Returns: - `long__min_bound()` if `x * y` would underflow;
//          - `long__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

long long__div_b( long x, long y );
// If `y == 0`, returns: - `long__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `long__max_bound()` if `x > 0`;
// Otherwise, returns: - `long__min_bound()` if
//                         `long__div_would_underflow( x, y )`;
//                     - `long__max_bound()` if
//                         `long__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

long long__mod_b( long x, long y );
// Returns: - `0` if `!long__can_div( x, y )`;
//          - `x % y` otherwise.

long long__negate_b( long x );
// Returns: - `long__max_bound()` if `x == long__min_bound()`;
//          - `-x` otherwise.

long long__abs_b( long x );
// Returns: - `long__max_bound()` if `x == long__min_bound()`;
//          - `long__abs( x )` otherwise.

bool long__same_sign( long x, long y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool long__is_negative( long x );     // Returns `x < 0`.
bool long__is_nonpositive( long x );  // Returns `x <= 0`.
bool long__is_zero( long x );         // Returns `x == 0`.
bool long__is_nonnegative( long x );  // Returns `x >= 0`.
bool long__is_positive( long x );     // Returns `x > 0`.

ord long__compare_0( long x );
// Returns `long__compare( x, 0 )`.

bool long__is_even( long x );     // Returns `x % 2 == 0`.
bool long__is_odd( long x );      // Returns `x % 2 == 1`.

long long__add_2( long );
long long__sub_2( long );
long long__mul_2( long );
long long__div_2( long );
long long__mod_2( long );

long long__mul_10( long );
long long__div_10( long );

long long__add_b_2( long );
long long__sub_b_2( long );
long long__mul_b_2( long );
long long__mul_b_10( long );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

long long__from_str( char const * str );
// Parses the given `str` to produce the contained `long` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `long`.


#endif // ifndef LIBBASE_LONG_H

