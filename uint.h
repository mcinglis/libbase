
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


#ifndef LIBBASE_UINT_H
#define LIBBASE_UINT_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord, uint


typedef struct {
    uint value;
    bool nothing;
} Maybe_uint;


uint uint__id( uint x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

uint uint__min_bound( void );     // Returns `uint_MIN`.
uint uint__max_bound( void );     // Returns `uint_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool uint__equal( uint x, uint y );        // Returns `x == y`.
bool uint__not_equal( uint x, uint y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord uint__compare( uint x, uint y );   // Returns: `LT` if `x < y`,
                                       //          `EQ` if `x == y`, or
                                       //          `GT` if `x > y`.

bool uint__less_than( uint x, uint y );            // Returns `x < y`.
bool uint__less_than_or_eq( uint x, uint y );      // Returns `x <= y`.
bool uint__greater_than_or_eq( uint x, uint y );   // Returns `x >= y`.
bool uint__greater_than( uint x, uint y );         // Returns `x > y`.

uint uint__min2( uint x, uint y ); // Returns `x` if `x < y`, or `y` otherwise.
uint uint__max2( uint x, uint y ); // Returns `x` if `x > y`, or `y` otherwise.

uint uint__min_n( size_t n, uint const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

uint uint__max_n( size_t n, uint const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define uint__min( ... ) \
    uint__min_n( PP_COUNT( __VA_ARGS__ ), ( uint[] ){ __VA_ARGS__ } )

// @public
#define uint__max( ... ) \
    uint__max_n( PP_COUNT( __VA_ARGS__ ), ( uint[] ){ __VA_ARGS__ } )

uint uint__clamp( uint lower, uint upper, uint x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`


/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

uint uint__succ( uint x );   // Returns `x + 1`.
                             // @requires x != uint__max_bound()

uint uint__succ_b( uint x ); // Returns `x + 1`, or `uint__max_bound()`
                             // if `x == uint__max_bound()`.

uint uint__pred( uint x );   // Returns `x - 1`.
                             // @requires x != uint__min_bound()

uint uint__pred_b( uint x ); // Returns `x - 1`, or `uint__min_bound()`
                             // if `x == uint__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool uint__is_signed( void );
// Returns `false`, because `uint` values can't be negative.

// Addition, subtraction and multiplication of `uint` values is always
// well-defined:

bool uint__can_add( uint x, uint y );        // Returns `true`.
bool uint__can_sub( uint x, uint y );        // Returns `true`.
bool uint__can_mul( uint x, uint y );        // Returns `true`.

bool uint__can_div( uint x, uint y );
// Returns the boolean that the behavior of `x / y` is well-defined, i.e.,
// that `y != 0`.

uint uint__add( uint x, uint y );   // Returns `x + y`.
uint uint__sub( uint x, uint y );   // Returns `x - y`.
uint uint__mul( uint x, uint y );   // Returns `x * y`.

uint uint__div( uint x, uint y );   // Returns `x / y`.
                                    // @requires y != 0

uint uint__mod( uint x, uint y );   // Returns `x % y`.
                                    // @requires y != 0

uint uint__negate( uint x );
// If `x == 0`, returns `0`.  Otherwise, returns `uint__max_bound() - x + 1`.

uint uint__abs( uint x );
// Returns `x`, because it will never be negative.

bool uint__same_sign( uint x, uint y );
// Returns `true`, because `uint` values are never negative.

bool uint__is_negative( uint x );     // Returns `false`.
bool uint__is_nonpositive( uint x );  // Returns `x == 0`.
bool uint__is_zero( uint x );         // Returns `x == 0`.
bool uint__is_nonnegative( uint x );  // Returns `true`.
bool uint__is_positive( uint x );     // Returns `x > 0`.
ord  uint__compare_0( uint x );       // Returns `uint__compare( x, 0 )`.

bool uint__is_even( uint x );     // Returns `x % 2 == 0`.
bool uint__is_odd( uint x );      // Returns `x % 2 == 1`.

uint uint__add_2( uint x );    // Returns `uint__add( x, 2 )`.
uint uint__sub_2( uint x );    // Returns `uint__sub( x, 2 )`.
uint uint__mul_2( uint x );    // Returns `uint__mul( x, 2 )`.
uint uint__div_2( uint x );    // Returns `uint__div( x, 2 )`.
uint uint__mod_2( uint x );    // Returns `uint__mod( x, 2 )`.

uint uint__mul_10( uint x );   // Returns `uint__mul( x, 10 )`.
uint uint__div_10( uint x );   // Returns `uint__div( x, 10 )`.
uint uint__mod_10( uint x );   // Returns `uint__mod( x, 10 )`.


/////////////////////////////
/// READ TYPECLASS
/////////////////////////////

Maybe_uint uint__from_str( char const * str );
// Parses the given `str` to produce the contained `uint` value. The string
// must contain exactly a valid representation, but may have whitespacing on
// either side of the value. If `str == NULL` or there was a parsing error,
// returns `( Maybe_uint ){ .nothing = true }`.


#endif

