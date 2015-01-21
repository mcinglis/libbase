
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


#ifndef LIBBASE_UCHAR_H
#define LIBBASE_UCHAR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord, uchar


typedef struct {
    uchar value;
    bool nothing;
} Maybe_uchar;


typedef struct {
    uchar value;
    int error;
} Result_uchar;


uchar uchar__id( uchar x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

uchar uchar__min_bound( void );     // Returns `0`.
uchar uchar__max_bound( void );     // Returns `UCHAR_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool uchar__equal( uchar x, uchar y );        // Returns `x == y`.
bool uchar__not_equal( uchar x, uchar y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord uchar__compare( uchar x, uchar y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool uchar__less_than( uchar x, uchar y );            // Returns `x < y`.
bool uchar__less_than_or_eq( uchar x, uchar y );      // Returns `x <= y`.
bool uchar__greater_than_or_eq( uchar x, uchar y );   // Returns `x >= y`.
bool uchar__greater_than( uchar x, uchar y );         // Returns `x > y`.

uchar uchar__min2( uchar x, uchar y );
// Returns `x` if `x < y`, or `y` otherwise.

uchar uchar__max2( uchar x, uchar y );
// Returns `x` if `x > y`, or `y` otherwise.

uchar uchar__min_n( size_t n, uchar const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uchar uchar__max_n( size_t n, uchar const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uchar__min( ... ) \
    uchar__min_n( PP_COUNT( __VA_ARGS__ ), ( uchar[] ){ __VA_ARGS__ } )

// @public
#define uchar__max( ... ) \
    uchar__max_n( PP_COUNT( __VA_ARGS__ ), ( uchar[] ){ __VA_ARGS__ } )

uchar uchar__clamp( uchar lower, uchar upper, uchar x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`


/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

uchar uchar__succ( uchar x );
// Returns `x + 1`.
// @requires x != uchar__max_bound()

uchar uchar__succ_b( uchar x );
// Returns `x + 1`, or `uchar__max_bound()` if `x == uchar__max_bound()`.

uchar uchar__pred( uchar x );
// Returns `x - 1`.
// @requires x != uchar__min_bound()

uchar uchar__pred_b( uchar x );
// Returns `x - 1`, or `uchar__min_bound()` if `x == uchar__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool uchar__is_signed( void );   // Returns `false`.

bool uchar__can_add( uchar x, uchar y );
// Returns the boolean that the expression `x + y` will not overflow;
// equivalent to `x <= ( uchar__max_bound() - y )`.

bool uchar__can_sub( uchar x, uchar y );
// Returns the boolean that the expression `x - y` will not underflow;
// equivalent to `x >= y`.

bool uchar__can_mul( uchar x, uchar y );
// Returns the boolean that the expression `x * y` will not overflow;
// equivalent to `x <= ( uchar__max_bound() / y )`.

bool uchar__can_div( uchar x, uchar y );
// Returns the boolean that the behavior of `x / y` is well-defined, i.e.,
// that `y != 0`.

uchar uchar__add( uchar x, uchar y );   // Returns `x + y`.
uchar uchar__sub( uchar x, uchar y );   // Returns `x - y`.
uchar uchar__mul( uchar x, uchar y );   // Returns `x * y`.

uchar uchar__div( uchar x, uchar y );
// Returns `x / y`.
// @requires y != 0

uchar uchar__mod( uchar x, uchar y );
// Returns `x % y`.
// @requires y != 0

uchar uchar__negate( uchar x );
// If `x == 0`, returns `0`. Otherwise, returns `uchar__max_bound() - x + 1`.

uchar uchar__abs( uchar x );
// Returns `x`, because it will never be negative.

bool uchar__same_sign( uchar x, uchar y );
// Returns `true`, because `uchar` values are never negative.

bool uchar__is_negative( uchar x );     // Returns `false`.
bool uchar__is_nonpositive( uchar x );  // Returns `x == 0`.
bool uchar__is_zero( uchar x );         // Returns `x == 0`.
bool uchar__is_nonnegative( uchar x );  // Returns `true`.
bool uchar__is_positive( uchar x );     // Returns `x > 0`.
ord  uchar__compare_0( uchar x );       // Returns `uchar__compare( x, 0 )`.

bool uchar__is_even( uchar x );     // Returns `x % 2 == 0`.
bool uchar__is_odd( uchar x );      // Returns `x % 2 == 1`.

uchar uchar__add_2( uchar x );    // Returns `uchar__add( x, 2 )`.
uchar uchar__sub_2( uchar x );    // Returns `uchar__sub( x, 2 )`.
uchar uchar__mul_2( uchar x );    // Returns `uchar__mul( x, 2 )`.
uchar uchar__div_2( uchar x );    // Returns `uchar__div( x, 2 )`.
uchar uchar__mod_2( uchar x );    // Returns `uchar__mod( x, 2 )`.

uchar uchar__mul_10( uchar x );   // Returns `uchar__mul( x, 10 )`.
uchar uchar__div_10( uchar x );   // Returns `uchar__div( x, 10 )`.
uchar uchar__mod_10( uchar x );   // Returns `uchar__mod( x, 10 )`.


/////////////////////////////
/// READ TYPECLASS
/////////////////////////////

Result_uchar uchar__from_str( char const * str );
// Parses the given `str` to produce the contained `uchar` value. Errors:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but also a non-numeric suffix;
// - `ERANGE` if the resulting value is out of range of `uchar`;

uchar uchar__from_str_e( char const * str, int * err );
// Like `uchar__from_str()`, but setting the given `err` value to the error,
// or `0` if no error.


#endif

