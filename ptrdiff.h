
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


#ifndef LIBBASE_PTRDIFF_H
#define LIBBASE_PTRDIFF_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_ptrdiff {
    ptrdiff_t value;
    bool nothing;
} Maybe_ptrdiff;


typedef struct result_ptrdiff {
    ptrdiff_t value;
    int error;
} Result_ptrdiff;


typedef struct arrayc_ptrdiff {
    ptrdiff_t const * e;
    size_t length;
} ArrayC_ptrdiff;


typedef struct arraym_ptrdiff {
    ptrdiff_t * e;
    size_t length;
} ArrayM_ptrdiff;


typedef struct vec_ptrdiff {
    ptrdiff_t * e;
    size_t length;
    size_t capacity;
} Vec_ptrdiff;


ptrdiff_t ptrdiff__id( ptrdiff_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

ptrdiff_t ptrdiff__min_bound( void );
// Returns the minimum value representable by the `ptrdiff_t` type.

ptrdiff_t ptrdiff__max_bound( void );
// Returns the maximum value representable by the `ptrdiff_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool ptrdiff__equal( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x == y`, or `false` if not.

bool ptrdiff__not_equal( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord ptrdiff__compare( ptrdiff_t x, ptrdiff_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ptrdiff__less_than( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x < y`, or `false` if not.

bool ptrdiff__less_than_or_eq( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool ptrdiff__greater_than_or_eq( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool ptrdiff__greater_than( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x > y`, or `false` if not.

ptrdiff_t ptrdiff__min2( ptrdiff_t x, ptrdiff_t y );
// Returns `x` if `x < y`, or `y` otherwise.

ptrdiff_t ptrdiff__max2( ptrdiff_t x, ptrdiff_t y );
// Returns `x` if `x > y`, or `y` otherwise.

ptrdiff_t ptrdiff__min_n( size_t n, ptrdiff_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ptrdiff_t ptrdiff__max_n( size_t n, ptrdiff_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ptrdiff__min( ... ) \
    ptrdiff__min_n( PP_COUNT( __VA_ARGS__ ), ( ptrdiff_t[] ){ __VA_ARGS__ } )

// @public
#define ptrdiff__max( ... ) \
    ptrdiff__max_n( PP_COUNT( __VA_ARGS__ ), ( ptrdiff_t[] ){ __VA_ARGS__ } )

ptrdiff_t ptrdiff__clamp( ptrdiff_t lower, ptrdiff_t upper, ptrdiff_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`

bool ptrdiff__in_range( ptrdiff_t lower, ptrdiff_t upper, ptrdiff_t x );
// Returns `lower <= x && x <= upper`.

bool ptrdiff__in_range_x( ptrdiff_t lower, ptrdiff_t upper, ptrdiff_t x );
// Returns `lower < x && x < upper`.



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

ptrdiff_t ptrdiff__succ( ptrdiff_t x );
// Returns `x + 1`.
// @requires x != ptrdiff__max_bound()

ptrdiff_t ptrdiff__succ_b( ptrdiff_t x );
// Returns `x + 1`, or `ptrdiff__max_bound()` if
// `x == ptrdiff__max_bound()`.

ptrdiff_t ptrdiff__pred( ptrdiff_t x );
// Returns `x - 1`.
// @requires x != ptrdiff__min_bound()

ptrdiff_t ptrdiff__pred_b( ptrdiff_t x );
// Returns `x - 1`, or `ptrdiff__min_bound()` if
// `x == ptrdiff__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool ptrdiff__is_signed( void );
// Returns `true`, because `ptrdiff_t` values can be negative.

bool ptrdiff__add_would_underflow( ptrdiff_t, ptrdiff_t );
bool ptrdiff__add_would_overflow( ptrdiff_t, ptrdiff_t );

bool ptrdiff__can_add( ptrdiff_t x, ptrdiff_t y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool ptrdiff__sub_would_underflow( ptrdiff_t, ptrdiff_t );
bool ptrdiff__sub_would_overflow( ptrdiff_t, ptrdiff_t );

bool ptrdiff__can_sub( ptrdiff_t x, ptrdiff_t y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool ptrdiff__mul_would_underflow( ptrdiff_t, ptrdiff_t );
bool ptrdiff__mul_would_overflow( ptrdiff_t, ptrdiff_t );

bool ptrdiff__can_mul( ptrdiff_t x, ptrdiff_t y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool ptrdiff__div_would_underflow( ptrdiff_t, ptrdiff_t );
bool ptrdiff__div_would_overflow( ptrdiff_t, ptrdiff_t );

bool ptrdiff__can_div( ptrdiff_t x, ptrdiff_t y );
// Returns the boolean that the behavior of `x / y` is well-defined.

ptrdiff_t ptrdiff__add( ptrdiff_t x, ptrdiff_t y );
// Returns `x + y`.
// @requires ptrdiff__can_add( x, y )

ptrdiff_t ptrdiff__sub( ptrdiff_t x, ptrdiff_t y );
// Returns `x - y`.
// @requires ptrdiff__can_sub( x, y )

ptrdiff_t ptrdiff__mul( ptrdiff_t x, ptrdiff_t y );
// Returns `x * y`.
// @requires ptrdiff__can_mul( x, y )

ptrdiff_t ptrdiff__div( ptrdiff_t x, ptrdiff_t y );
// Returns `x / y`.
// @requires ptrdiff__can_div( x, y )

ptrdiff_t ptrdiff__mod( ptrdiff_t x, ptrdiff_t y );
// Returns `x % y`.
// @requires ptrdiff__can_div( x, y )

ptrdiff_t ptrdiff__negate( ptrdiff_t x );
// Returns `-x`.
// @requires x != ptrdiff__min_bound()

ptrdiff_t ptrdiff__abs( ptrdiff_t x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != ptrdiff__min_bound()

ptrdiff_t ptrdiff__add_b( ptrdiff_t x, ptrdiff_t y );
// Returns: - `ptrdiff__min_bound()` if `x + y` would underflow;
//          - `ptrdiff__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

ptrdiff_t ptrdiff__sub_b( ptrdiff_t x, ptrdiff_t y );
// Returns: - `ptrdiff__min_bound()` if `x - y` would underflow;
//          - `ptrdiff__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

ptrdiff_t ptrdiff__mul_b( ptrdiff_t x, ptrdiff_t y );
// Returns: - `ptrdiff__min_bound()` if `x * y` would underflow;
//          - `ptrdiff__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

ptrdiff_t ptrdiff__div_b( ptrdiff_t x, ptrdiff_t y );
// If `y == 0`, returns: - `ptrdiff__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `ptrdiff__max_bound()` if `x > 0`;
// Otherwise, returns: - `ptrdiff__min_bound()` if
//                         `ptrdiff__div_would_underflow( x, y )`;
//                     - `ptrdiff__max_bound()` if
//                         `ptrdiff__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

ptrdiff_t ptrdiff__mod_b( ptrdiff_t x, ptrdiff_t y );
// Returns: - `0` if `!ptrdiff__can_div( x, y )`;
//          - `x % y` otherwise.

ptrdiff_t ptrdiff__negate_b( ptrdiff_t x );
// Returns: - `ptrdiff__max_bound()` if `x == ptrdiff__min_bound()`;
//          - `-x` otherwise.

ptrdiff_t ptrdiff__abs_b( ptrdiff_t x );
// Returns: - `ptrdiff__max_bound()` if `x == ptrdiff__min_bound()`;
//          - `ptrdiff__abs( x )` otherwise.

bool ptrdiff__same_sign( ptrdiff_t x, ptrdiff_t y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool ptrdiff__in_delta( ptrdiff_t x, ptrdiff_t delta, ptrdiff_t y );
// Returns `( x - delta ) <= y && y <= ( x + delta )`, with the arithmetic
// being bounded.

bool ptrdiff__in_delta_x( ptrdiff_t x, ptrdiff_t delta, ptrdiff_t y );
// Returns `( x - delta ) < y && y < ( x + delta )`, with the arithmetic being
// bounded.

bool ptrdiff__is_negative( ptrdiff_t x );     // Returns `x < 0`.
bool ptrdiff__is_nonpositive( ptrdiff_t x );  // Returns `x <= 0`.
bool ptrdiff__is_zero( ptrdiff_t x );         // Returns `x == 0`.
bool ptrdiff__is_nonzero( ptrdiff_t x );      // Returns `x != 0`.
bool ptrdiff__is_nonnegative( ptrdiff_t x );  // Returns `x >= 0`.
bool ptrdiff__is_positive( ptrdiff_t x );     // Returns `x > 0`.

ord ptrdiff__compare_0( ptrdiff_t x );
// Returns `ptrdiff__compare( x, 0 )`.

bool ptrdiff__is_even( ptrdiff_t x );     // Returns `x % 2 == 0`.
bool ptrdiff__is_odd( ptrdiff_t x );      // Returns `x % 2 == 1`.

ptrdiff_t ptrdiff__add_2( ptrdiff_t );
ptrdiff_t ptrdiff__sub_2( ptrdiff_t );
ptrdiff_t ptrdiff__mul_2( ptrdiff_t );
ptrdiff_t ptrdiff__div_2( ptrdiff_t );
ptrdiff_t ptrdiff__mod_2( ptrdiff_t );

ptrdiff_t ptrdiff__mul_10( ptrdiff_t );
ptrdiff_t ptrdiff__div_10( ptrdiff_t );

ptrdiff_t ptrdiff__add_b_2( ptrdiff_t );
ptrdiff_t ptrdiff__sub_b_2( ptrdiff_t );
ptrdiff_t ptrdiff__mul_b_2( ptrdiff_t );
ptrdiff_t ptrdiff__mul_b_10( ptrdiff_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

ptrdiff_t ptrdiff__from_str( char const * str );
// Parses the given `str` to produce the contained `ptrdiff_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `ptrdiff_t`.


#endif // ifndef LIBBASE_PTRDIFF_H

