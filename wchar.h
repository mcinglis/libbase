
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


#ifndef LIBBASE_WCHAR_H
#define LIBBASE_WCHAR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_wchar {
    wchar_t value;
    bool nothing;
} Maybe_wchar;


wchar_t wchar__id( wchar_t x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

wchar_t wchar__min_bound( void );
// Returns the minimum value representable by the `wchar_t` type.

wchar_t wchar__max_bound( void );
// Returns the maximum value representable by the `wchar_t` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool wchar__equal( wchar_t x, wchar_t y );
// Returns `true` if `x == y`, or `false` if not.

bool wchar__not_equal( wchar_t x, wchar_t y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord wchar__compare( wchar_t x, wchar_t y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool wchar__less_than( wchar_t x, wchar_t y );
// Returns `true` if `x < y`, or `false` if not.

bool wchar__less_than_or_eq( wchar_t x, wchar_t y );
// Returns `true` if `x <= y`, or `false` if not.

bool wchar__greater_than_or_eq( wchar_t x, wchar_t y );
// Returns `true` if `x >= y`, or `false` if not.

bool wchar__greater_than( wchar_t x, wchar_t y );
// Returns `true` if `x > y`, or `false` if not.

wchar_t wchar__min2( wchar_t x, wchar_t y );
// Returns `x` if `x < y`, or `y` otherwise.

wchar_t wchar__max2( wchar_t x, wchar_t y );
// Returns `x` if `x > y`, or `y` otherwise.

wchar_t wchar__min_n( size_t n, wchar_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

wchar_t wchar__max_n( size_t n, wchar_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define wchar__min( ... ) \
    wchar__min_n( PP_COUNT( __VA_ARGS__ ), ( wchar_t[] ){ __VA_ARGS__ } )

// @public
#define wchar__max( ... ) \
    wchar__max_n( PP_COUNT( __VA_ARGS__ ), ( wchar_t[] ){ __VA_ARGS__ } )

wchar_t wchar__clamp( wchar_t lower, wchar_t upper, wchar_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

wchar_t wchar__succ( wchar_t x );
// Returns `x + 1`.
// @requires x != wchar__max_bound()

wchar_t wchar__succ_b( wchar_t x );
// Returns `x + 1`, or `wchar__max_bound()` if
// `x == wchar__max_bound()`.

wchar_t wchar__pred( wchar_t x );
// Returns `x - 1`.
// @requires x != wchar__min_bound()

wchar_t wchar__pred_b( wchar_t x );
// Returns `x - 1`, or `wchar__min_bound()` if
// `x == wchar__min_bound()`.



///////////////////////////////////
/// TYPECLASS: NUM
///////////////////////////////////

bool wchar__is_signed( void );
// Returns `true`, because `wchar_t` values can be negative.

bool wchar__add_would_underflow( wchar_t, wchar_t );
bool wchar__add_would_overflow( wchar_t, wchar_t );

bool wchar__can_add( wchar_t x, wchar_t y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool wchar__sub_would_underflow( wchar_t, wchar_t );
bool wchar__sub_would_overflow( wchar_t, wchar_t );

bool wchar__can_sub( wchar_t x, wchar_t y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool wchar__mul_would_underflow( wchar_t, wchar_t );
bool wchar__mul_would_overflow( wchar_t, wchar_t );

bool wchar__can_mul( wchar_t x, wchar_t y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool wchar__div_would_underflow( wchar_t, wchar_t );
bool wchar__div_would_overflow( wchar_t, wchar_t );

bool wchar__can_div( wchar_t x, wchar_t y );
// Returns the boolean that the behavior of `x / y` is well-defined.

wchar_t wchar__add( wchar_t x, wchar_t y );
// Returns `x + y`.
// @requires wchar__can_add( x, y )

wchar_t wchar__sub( wchar_t x, wchar_t y );
// Returns `x - y`.
// @requires wchar__can_sub( x, y )

wchar_t wchar__mul( wchar_t x, wchar_t y );
// Returns `x * y`.
// @requires wchar__can_mul( x, y )

wchar_t wchar__div( wchar_t x, wchar_t y );
// Returns `x / y`.
// @requires wchar__can_div( x, y )

wchar_t wchar__mod( wchar_t x, wchar_t y );
// Returns `x % y`.
// @requires wchar__can_div( x, y )

wchar_t wchar__negate( wchar_t x );
// Returns `-x`.
// @requires x != wchar__min_bound()

wchar_t wchar__abs( wchar_t x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != wchar__min_bound()

wchar_t wchar__add_b( wchar_t x, wchar_t y );
// Returns: - `wchar__min_bound()` if `x + y` would underflow;
//          - `wchar__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

wchar_t wchar__sub_b( wchar_t x, wchar_t y );
// Returns: - `wchar__min_bound()` if `x - y` would underflow;
//          - `wchar__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

wchar_t wchar__mul_b( wchar_t x, wchar_t y );
// Returns: - `wchar__min_bound()` if `x * y` would underflow;
//          - `wchar__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

wchar_t wchar__div_b( wchar_t x, wchar_t y );
// If `y == 0`, returns: - `wchar__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `wchar__max_bound()` if `x > 0`;
// Otherwise, returns: - `wchar__min_bound()` if
//                         `wchar__div_would_underflow( x, y )`;
//                     - `wchar__max_bound()` if
//                         `wchar__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

wchar_t wchar__mod_b( wchar_t x, wchar_t y );
// Returns: - `0` if `!wchar__can_div( x, y )`;
//          - `x % y` otherwise.

wchar_t wchar__negate_b( wchar_t x );
// Returns: - `wchar__max_bound()` if `x == wchar__min_bound()`;
//          - `-x` otherwise.

wchar_t wchar__abs_b( wchar_t x );
// Returns: - `wchar__max_bound()` if `x == wchar__min_bound()`;
//          - `wchar__abs( x )` otherwise.

bool wchar__same_sign( wchar_t x, wchar_t y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool wchar__is_negative( wchar_t x );     // Returns `x < 0`.
bool wchar__is_nonpositive( wchar_t x );  // Returns `x <= 0`.
bool wchar__is_zero( wchar_t x );         // Returns `x == 0`.
bool wchar__is_nonnegative( wchar_t x );  // Returns `x >= 0`.
bool wchar__is_positive( wchar_t x );     // Returns `x > 0`.

ord wchar__compare_0( wchar_t x );
// Returns `wchar__compare( x, 0 )`.

bool wchar__is_even( wchar_t x );     // Returns `x % 2 == 0`.
bool wchar__is_odd( wchar_t x );      // Returns `x % 2 == 1`.

wchar_t wchar__add_2( wchar_t );
wchar_t wchar__sub_2( wchar_t );
wchar_t wchar__mul_2( wchar_t );
wchar_t wchar__div_2( wchar_t );
wchar_t wchar__mod_2( wchar_t );

wchar_t wchar__mul_10( wchar_t );
wchar_t wchar__div_10( wchar_t );

wchar_t wchar__add_b_2( wchar_t );
wchar_t wchar__sub_b_2( wchar_t );
wchar_t wchar__mul_b_2( wchar_t );
wchar_t wchar__mul_b_10( wchar_t );



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

wchar_t wchar__from_str( char const * str );
// Parses the given `str` to produce the contained `wchar_t` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `wchar_t`.


#endif // ifndef LIBBASE_WCHAR_H

