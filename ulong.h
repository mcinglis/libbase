
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


#ifndef LIBBASE_ULONG_H
#define LIBBASE_ULONG_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord, ulong


typedef struct {
    ulong value;
    bool nothing;
} Maybe_ulong;


typedef struct {
    ulong value;
    int error;
} Result_ulong;


ulong ulong__id( ulong x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

ulong ulong__min_bound( void );     // Returns `0`.
ulong ulong__max_bound( void );     // Returns `ULONG_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool ulong__equal( ulong x, ulong y );        // Returns `x == y`.
bool ulong__not_equal( ulong x, ulong y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord ulong__compare( ulong x, ulong y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ulong__less_than( ulong x, ulong y );            // Returns `x < y`.
bool ulong__less_than_or_eq( ulong x, ulong y );      // Returns `x <= y`.
bool ulong__greater_than_or_eq( ulong x, ulong y );   // Returns `x >= y`.
bool ulong__greater_than( ulong x, ulong y );         // Returns `x > y`.

ulong ulong__min2( ulong x, ulong y );
// Returns `x` if `x < y`, or `y` otherwise.

ulong ulong__max2( ulong x, ulong y );
// Returns `x` if `x > y`, or `y` otherwise.

ulong ulong__min_n( size_t n, ulong const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ulong ulong__max_n( size_t n, ulong const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ulong__min( ... ) \
    ulong__min_n( PP_COUNT( __VA_ARGS__ ), ( ulong[] ){ __VA_ARGS__ } )

// @public
#define ulong__max( ... ) \
    ulong__max_n( PP_COUNT( __VA_ARGS__ ), ( ulong[] ){ __VA_ARGS__ } )

ulong ulong__clamp( ulong lower, ulong upper, ulong x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`


/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

ulong ulong__succ( ulong x );
// Returns `x + 1`.
// @requires x != ulong__max_bound()

ulong ulong__succ_b( ulong x );
// Returns `x + 1`, or `ulong__max_bound()` if `x == ulong__max_bound()`.

ulong ulong__pred( ulong x );
// Returns `x - 1`.
// @requires x != ulong__min_bound()

ulong ulong__pred_b( ulong x );
// Returns `x - 1`, or `ulong__min_bound()` if `x == ulong__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool ulong__is_signed( void );   // Returns `false`.

bool ulong__can_add( ulong x, ulong y );
// Returns the boolean that the expression `x + y` will not overflow;
// equivalent to `x <= ( ulong__max_bound() - y )`.

bool ulong__can_sub( ulong x, ulong y );
// Returns the boolean that the expression `x - y` will not underflow;
// equivalent to `x >= y`.

bool ulong__can_mul( ulong x, ulong y );
// Returns the boolean that the expression `x * y` will not overflow;
// equivalent to `x <= ( ulong__max_bound() / y )`.

bool ulong__can_div( ulong x, ulong y );
// Returns the boolean that the behavior of `x / y` is well-defined, i.e.,
// that `y != 0`.

ulong ulong__add( ulong x, ulong y );   // Returns `x + y`.
ulong ulong__sub( ulong x, ulong y );   // Returns `x - y`.
ulong ulong__mul( ulong x, ulong y );   // Returns `x * y`.

ulong ulong__div( ulong x, ulong y );
// Returns `x / y`.
// @requires y != 0

ulong ulong__mod( ulong x, ulong y );
// Returns `x % y`.
// @requires y != 0

ulong ulong__negate( ulong x );
// If `x == 0`, returns `0`. Otherwise, returns `ulong__max_bound() - x + 1`.

ulong ulong__abs( ulong x );
// Returns `x`, because it will never be negative.

bool ulong__same_sign( ulong x, ulong y );
// Returns `true`, because `ulong` values are never negative.

bool ulong__is_negative( ulong x );     // Returns `false`.
bool ulong__is_nonpositive( ulong x );  // Returns `x == 0`.
bool ulong__is_zero( ulong x );         // Returns `x == 0`.
bool ulong__is_nonnegative( ulong x );  // Returns `true`.
bool ulong__is_positive( ulong x );     // Returns `x > 0`.
ord  ulong__compare_0( ulong x );       // Returns `ulong__compare( x, 0 )`.

bool ulong__is_even( ulong x );     // Returns `x % 2 == 0`.
bool ulong__is_odd( ulong x );      // Returns `x % 2 == 1`.

ulong ulong__add_2( ulong x );    // Returns `ulong__add( x, 2 )`.
ulong ulong__sub_2( ulong x );    // Returns `ulong__sub( x, 2 )`.
ulong ulong__mul_2( ulong x );    // Returns `ulong__mul( x, 2 )`.
ulong ulong__div_2( ulong x );    // Returns `ulong__div( x, 2 )`.
ulong ulong__mod_2( ulong x );    // Returns `ulong__mod( x, 2 )`.

ulong ulong__mul_10( ulong x );   // Returns `ulong__mul( x, 10 )`.
ulong ulong__div_10( ulong x );   // Returns `ulong__div( x, 10 )`.
ulong ulong__mod_10( ulong x );   // Returns `ulong__mod( x, 10 )`.


/////////////////////////////
/// READ TYPECLASS
/////////////////////////////

Result_ulong ulong__from_str( char const * str );
// Parses the given `str` to produce the contained `ulong` value. Errors:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but also a non-numeric suffix;
// - `ERANGE` if the resulting value is out of range of `ulong`;


#endif

