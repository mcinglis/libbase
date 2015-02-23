
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


#ifndef LIBBASE_SHORT_H
#define LIBBASE_SHORT_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_short {
    short value;
    bool nothing;
} Maybe_short;


typedef struct result_short {
    short value;
    int error;
} Result_short;


typedef struct arrayc_short {
    short const * e;
    size_t length;
} ArrayC_short;


typedef struct arraym_short {
    short * e;
    size_t length;
} ArrayM_short;


typedef struct vec_short {
    short * e;
    size_t length;
    size_t capacity;
} Vec_short;


short short__id( short x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

short short__min_bound( void );
// Returns the minimum value representable by the `short` type.

short short__max_bound( void );
// Returns the maximum value representable by the `short` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool short__equal( short x, short y );
// Returns `true` if `x == y`, or `false` if not.

bool short__not_equal( short x, short y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord short__compare( short x, short y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool short__less_than( short x, short y );
// Returns `true` if `x < y`, or `false` if not.

bool short__less_than_or_eq( short x, short y );
// Returns `true` if `x <= y`, or `false` if not.

bool short__greater_than_or_eq( short x, short y );
// Returns `true` if `x >= y`, or `false` if not.

bool short__greater_than( short x, short y );
// Returns `true` if `x > y`, or `false` if not.

short short__min2( short x, short y );
// Returns `x` if `x < y`, or `y` otherwise.

short short__max2( short x, short y );
// Returns `x` if `x > y`, or `y` otherwise.

short short__min_n( size_t n, short const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

short short__max_n( size_t n, short const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define short__min( ... ) \
    short__min_n( PP_COUNT( __VA_ARGS__ ), ( short[] ){ __VA_ARGS__ } )

// @public
#define short__max( ... ) \
    short__max_n( PP_COUNT( __VA_ARGS__ ), ( short[] ){ __VA_ARGS__ } )

short short__clamp( short lower, short upper, short x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`

bool short__in_range( short lower, short upper, short x );
// Returns `lower <= x && x <= upper`.

bool short__in_range_x( short lower, short upper, short x );
// Returns `lower < x && x < upper`.



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

short short__succ( short x );
// Returns `x + 1`.
// @requires x != short__max_bound()

short short__succ_b( short x );
// Returns `x + 1`, or `short__max_bound()` if
// `x == short__max_bound()`.

short short__pred( short x );
// Returns `x - 1`.
// @requires x != short__min_bound()

short short__pred_b( short x );
// Returns `x - 1`, or `short__min_bound()` if
// `x == short__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool short__is_signed( void );
// Returns `true`, because `short` values can be negative.

bool short__add_would_underflow( short, short );
bool short__add_would_overflow( short, short );

bool short__can_add( short x, short y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool short__sub_would_underflow( short, short );
bool short__sub_would_overflow( short, short );

bool short__can_sub( short x, short y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool short__mul_would_underflow( short, short );
bool short__mul_would_overflow( short, short );

bool short__can_mul( short x, short y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool short__div_would_underflow( short, short );
bool short__div_would_overflow( short, short );

bool short__can_div( short x, short y );
// Returns the boolean that the behavior of `x / y` is well-defined.

short short__add( short x, short y );
// Returns `x + y`.
// @requires short__can_add( x, y )

short short__sub( short x, short y );
// Returns `x - y`.
// @requires short__can_sub( x, y )

short short__mul( short x, short y );
// Returns `x * y`.
// @requires short__can_mul( x, y )

short short__div( short x, short y );
// Returns `x / y`.
// @requires short__can_div( x, y )

short short__mod( short x, short y );
// Returns `x % y`.
// @requires short__can_div( x, y )

short short__negate( short x );
// Returns `-x`.
// @requires x != short__min_bound()

short short__abs( short x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != short__min_bound()

short short__add_b( short x, short y );
// Returns: - `short__min_bound()` if `x + y` would underflow;
//          - `short__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

short short__sub_b( short x, short y );
// Returns: - `short__min_bound()` if `x - y` would underflow;
//          - `short__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

short short__mul_b( short x, short y );
// Returns: - `short__min_bound()` if `x * y` would underflow;
//          - `short__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

short short__div_b( short x, short y );
// If `y == 0`, returns: - `short__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `short__max_bound()` if `x > 0`;
// Otherwise, returns: - `short__min_bound()` if
//                         `short__div_would_underflow( x, y )`;
//                     - `short__max_bound()` if
//                         `short__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

short short__mod_b( short x, short y );
// Returns: - `0` if `!short__can_div( x, y )`;
//          - `x % y` otherwise.

short short__negate_b( short x );
// Returns: - `short__max_bound()` if `x == short__min_bound()`;
//          - `-x` otherwise.

short short__abs_b( short x );
// Returns: - `short__max_bound()` if `x == short__min_bound()`;
//          - `short__abs( x )` otherwise.

bool short__same_sign( short x, short y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool short__in_delta( short x, short delta, short y );
// Returns `( x - delta ) <= y && y <= ( x + delta )`, with the arithmetic
// being bounded.

bool short__in_delta_x( short x, short delta, short y );
// Returns `( x - delta ) < y && y < ( x + delta )`, with the arithmetic being
// bounded.

bool short__is_negative( short x );     // Returns `x < 0`.
bool short__is_nonpositive( short x );  // Returns `x <= 0`.
bool short__is_zero( short x );         // Returns `x == 0`.
bool short__is_nonzero( short x );      // Returns `x != 0`.
bool short__is_nonnegative( short x );  // Returns `x >= 0`.
bool short__is_positive( short x );     // Returns `x > 0`.

ord short__compare_0( short x );
// Returns `short__compare( x, 0 )`.

bool short__is_even( short x );     // Returns `x % 2 == 0`.
bool short__is_odd( short x );      // Returns `x % 2 == 1`.

short short__add_2( short );
short short__sub_2( short );
short short__mul_2( short );
short short__div_2( short );
short short__mod_2( short );

short short__mul_10( short );
short short__div_10( short );

short short__add_b_2( short );
short short__sub_b_2( short );
short short__mul_b_2( short );
short short__mul_b_10( short );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

short short__from_str( char const * str );
// Parses the given `str` to produce the contained `short` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `short`.


#endif // ifndef LIBBASE_SHORT_H

