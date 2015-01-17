
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


#ifndef LIBBASE_UINT16_H
#define LIBBASE_UINT16_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord, uint16_t


typedef struct {
    uint16_t value;
    bool nothing;
} Maybe_uint16;


uint16_t uint16__id( uint16_t x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

uint16_t uint16__min_bound( void );     // Returns `uint16_MIN`.
uint16_t uint16__max_bound( void );     // Returns `uint16_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool uint16__equal( uint16_t x, uint16_t y );        // Returns `x == y`.
bool uint16__not_equal( uint16_t x, uint16_t y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord uint16__compare( uint16_t x, uint16_t y );   // Returns:
                                                 // - `LT` if `x < y`;
                                                 // - `EQ` if `x == y`; or
                                                 // - `GT` if `x > y`.

bool uint16__less_than( uint16_t x, uint16_t y );
// Returns `x < y`.

bool uint16__less_than_or_eq( uint16_t x, uint16_t y );
// Returns `x <= y`.

bool uint16__greater_than_or_eq( uint16_t x, uint16_t y );
// Returns `x >= y`.

bool uint16__greater_than( uint16_t x, uint16_t y );
// Returns `x > y`.

uint16_t uint16__min2( uint16_t x, uint16_t y );
// Returns `x` if `x < y`, or `y` otherwise.

uint16_t uint16__max2( uint16_t x, uint16_t y );
// Returns `x` if `x > y`, or `y` otherwise.

uint16_t uint16__min_n( size_t n, uint16_t const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uint16_t uint16__max_n( size_t n, uint16_t const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uint16__min( ... ) \
    uint16__min_n( PP_COUNT( __VA_ARGS__ ), ( uint16_t[] ){ __VA_ARGS__ } )

// @public
#define uint16__max( ... ) \
    uint16__max_n( PP_COUNT( __VA_ARGS__ ), ( uint16_t[] ){ __VA_ARGS__ } )

uint16_t uint16__clamp( uint16_t lower, uint16_t upper, uint16_t x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`


/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

uint16_t uint16__succ( uint16_t x );
// Returns `x + 1`.
// @requires x != uint16__max_bound()

uint16_t uint16__succ_b( uint16_t x );
// Returns `x + 1`, or `uint16__max_bound()`
// if `x == uint16__max_bound()`.

uint16_t uint16__pred( uint16_t x );
// Returns `x - 1`.
// @requires x != uint16__min_bound()

uint16_t uint16__pred_b( uint16_t x );
// Returns `x - 1`, or `uint16__min_bound()`
// if `x == uint16__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool uint16__is_signed( void );
// Returns `false`, because `uint16_t` values can't be negative.

// Addition, subtraction and multiplication of `uint16_t` values is always
// well-defined:

bool uint16__can_add( uint16_t x, uint16_t y );        // Returns `true`.
bool uint16__can_sub( uint16_t x, uint16_t y );        // Returns `true`.
bool uint16__can_mul( uint16_t x, uint16_t y );        // Returns `true`.

bool uint16__can_div( uint16_t x, uint16_t y );
// Returns the boolean that the behavior of `x / y` is well-defined, i.e.,
// that `y != 0`.

uint16_t uint16__add( uint16_t x, uint16_t y );   // Returns `x + y`.
uint16_t uint16__sub( uint16_t x, uint16_t y );   // Returns `x - y`.
uint16_t uint16__mul( uint16_t x, uint16_t y );   // Returns `x * y`.

uint16_t uint16__div( uint16_t x, uint16_t y );   // Returns `x / y`.
                                                  // @requires y != 0

uint16_t uint16__mod( uint16_t x, uint16_t y );   // Returns `x % y`.
                                                  // @requires y != 0

uint16_t uint16__negate( uint16_t x );
// If `x == 0`, returns `0`. Otherwise, returns `uint16__max_bound() - x + 1`.

uint16_t uint16__abs( uint16_t x );
// Returns `x`, because it will never be negative.

bool uint16__same_sign( uint16_t x, uint16_t y );
// Returns `true`, because `uint16_t` values are never negative.

bool uint16__is_negative( uint16_t x );     // Returns `false`.
bool uint16__is_nonpositive( uint16_t x );  // Returns `x == 0`.
bool uint16__is_zero( uint16_t x );         // Returns `x == 0`.
bool uint16__is_nonnegative( uint16_t x );  // Returns `true`.
bool uint16__is_positive( uint16_t x );     // Returns `x > 0`.
ord  uint16__compare_0( uint16_t x );    // Returns `uint16__compare( x, 0 )`.

bool uint16__is_even( uint16_t x );     // Returns `x % 2 == 0`.
bool uint16__is_odd( uint16_t x );      // Returns `x % 2 == 1`.

uint16_t uint16__add_2( uint16_t x );    // Returns `uint16__add( x, 2 )`.
uint16_t uint16__sub_2( uint16_t x );    // Returns `uint16__sub( x, 2 )`.
uint16_t uint16__mul_2( uint16_t x );    // Returns `uint16__mul( x, 2 )`.
uint16_t uint16__div_2( uint16_t x );    // Returns `uint16__div( x, 2 )`.
uint16_t uint16__mod_2( uint16_t x );    // Returns `uint16__mod( x, 2 )`.

uint16_t uint16__mul_10( uint16_t x );   // Returns `uint16__mul( x, 10 )`.
uint16_t uint16__div_10( uint16_t x );   // Returns `uint16__div( x, 10 )`.
uint16_t uint16__mod_10( uint16_t x );   // Returns `uint16__mod( x, 10 )`.


/////////////////////////////
/// READ TYPECLASS
/////////////////////////////

Maybe_uint16 uint16__from_str( char const * str );
// Parses the given `str` to produce the contained `uint16_t` value. The
// string must contain exactly a valid representation, but may have
// whitespacing on either side of the value. If `str == NULL` or there was a
// parsing error, returns `( Maybe_uint16 ){ .nothing = true }`.


#endif

