
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


#ifndef LIBBASE_USHORT_H
#define LIBBASE_USHORT_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_ushort {
    ushort value;
    bool nothing;
} Maybe_ushort;


typedef struct result_ushort {
    ushort value;
    int error;
} Result_ushort;


typedef struct arrayc_ushort {
    ushort const * e;
    size_t capacity;
} ArrayC_ushort;


typedef struct arraym_ushort {
    ushort * e;
    size_t capacity;
} ArrayM_ushort;


typedef struct vec_ushort {
    ushort * e;
    size_t length;
    size_t capacity;
} Vec_ushort;


ushort ushort__id( ushort x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

ushort ushort__min_bound( void );
// Returns the minimum value representable by the `ushort` type.

ushort ushort__max_bound( void );
// Returns the maximum value representable by the `ushort` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool ushort__equal( ushort x, ushort y );
// Returns `true` if `x == y`, or `false` if not.

bool ushort__not_equal( ushort x, ushort y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord ushort__compare( ushort x, ushort y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ushort__less_than( ushort x, ushort y );
// Returns `true` if `x < y`, or `false` if not.

bool ushort__less_than_or_eq( ushort x, ushort y );
// Returns `true` if `x <= y`, or `false` if not.

bool ushort__greater_than_or_eq( ushort x, ushort y );
// Returns `true` if `x >= y`, or `false` if not.

bool ushort__greater_than( ushort x, ushort y );
// Returns `true` if `x > y`, or `false` if not.

ushort ushort__min2( ushort x, ushort y );
// Returns `x` if `x < y`, or `y` otherwise.

ushort ushort__max2( ushort x, ushort y );
// Returns `x` if `x > y`, or `y` otherwise.

ushort ushort__min_n( size_t n, ushort const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ushort ushort__max_n( size_t n, ushort const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ushort__min( ... ) \
    ushort__min_n( PP_COUNT( __VA_ARGS__ ), ( ushort[] ){ __VA_ARGS__ } )

// @public
#define ushort__max( ... ) \
    ushort__max_n( PP_COUNT( __VA_ARGS__ ), ( ushort[] ){ __VA_ARGS__ } )

ushort ushort__clamp( ushort lower, ushort upper, ushort x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

ushort ushort__succ( ushort x );
// Returns `x + 1`.
// @requires x != ushort__max_bound()

ushort ushort__succ_b( ushort x );
// Returns `x + 1`, or `ushort__max_bound()` if
// `x == ushort__max_bound()`.

ushort ushort__pred( ushort x );
// Returns `x - 1`.
// @requires x != ushort__min_bound()

ushort ushort__pred_b( ushort x );
// Returns `x - 1`, or `ushort__min_bound()` if
// `x == ushort__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool ushort__is_signed( void );
// Returns `false`, because `ushort` values can't be negative.

bool ushort__add_would_underflow( ushort, ushort );
bool ushort__add_would_overflow( ushort, ushort );

bool ushort__can_add( ushort x, ushort y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool ushort__sub_would_underflow( ushort, ushort );
bool ushort__sub_would_overflow( ushort, ushort );

bool ushort__can_sub( ushort x, ushort y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool ushort__mul_would_underflow( ushort, ushort );
bool ushort__mul_would_overflow( ushort, ushort );

bool ushort__can_mul( ushort x, ushort y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool ushort__div_would_underflow( ushort, ushort );
bool ushort__div_would_overflow( ushort, ushort );

bool ushort__can_div( ushort x, ushort y );
// Returns the boolean that `y != 0`.

ushort ushort__add( ushort x, ushort y );
// Returns `x + y`, which may overflow.

ushort ushort__sub( ushort x, ushort y );
// Returns `x - y`, which may underflow.

ushort ushort__mul( ushort x, ushort y );
// Returns `x * y`, which may overflow.

ushort ushort__div( ushort x, ushort y );
// Returns `x / y`.
// @requires y != 0

ushort ushort__mod( ushort x, ushort y );
// Returns `x % y`.
// @requires y != 0

ushort ushort__negate( ushort x );
// Returns `-x`, which gives `ushort__max_bound() - x + 1`.

ushort ushort__abs( ushort x );
// Returns `x`, because it will never be negative.

ushort ushort__add_b( ushort x, ushort y );
// Returns: - `ushort__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

ushort ushort__sub_b( ushort x, ushort y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

ushort ushort__mul_b( ushort x, ushort y );
// Returns: - `ushort__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

ushort ushort__div_b( ushort x, ushort y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `ushort__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

ushort ushort__mod_b( ushort x, ushort y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

ushort ushort__negate_b( ushort x );
// Returns `ushort__negate( x )`.

ushort ushort__abs_b( ushort x );
// Returns `ushort__abs( x )`.

bool ushort__same_sign( ushort, ushort );
// Returns `true`, because `ushort` values will always have the same sign.

bool ushort__is_negative( ushort x );     // Returns `false`.
bool ushort__is_nonpositive( ushort x );  // Returns `x == 0`.
bool ushort__is_zero( ushort x );         // Returns `x == 0`.
bool ushort__is_nonnegative( ushort x );  // Returns `true`.
bool ushort__is_positive( ushort x );     // Returns `x != 0`.

ord ushort__compare_0( ushort x );
// Returns `ushort__compare( x, 0 )`.

bool ushort__is_even( ushort x );  // Returns `x % 2 == 0`.
bool ushort__is_odd( ushort x );   // Returns `x % 2 == 1`.

ushort ushort__add_2( ushort );
ushort ushort__sub_2( ushort );
ushort ushort__mul_2( ushort );
ushort ushort__div_2( ushort );
ushort ushort__mod_2( ushort );

ushort ushort__mul_10( ushort );
ushort ushort__div_10( ushort );

ushort ushort__add_b_2( ushort );
ushort ushort__sub_b_2( ushort );
ushort ushort__mul_b_2( ushort );
ushort ushort__mul_b_10( ushort );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

ushort ushort__from_str( char const * str );
// Parses the given `str` to produce the contained `ushort` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `ushort`.


#endif // ifndef LIBBASE_USHORT_H

