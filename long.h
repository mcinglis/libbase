
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


typedef struct {
    long value;
    bool nothing;
} Maybe_long;


typedef struct {
    long value;
    int error;
} Result_long;


long long__id( long x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

long long__min_bound( void );     // Returns `LONG_MIN`.
long long__max_bound( void );     // Returns `LONG_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool long__equal( long x, long y );        // Returns `x == y`.
bool long__not_equal( long x, long y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord long__compare( long x, long y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool long__less_than( long x, long y );            // Returns `x < y`.
bool long__less_than_or_eq( long x, long y );      // Returns `x <= y`.
bool long__greater_than_or_eq( long x, long y );   // Returns `x >= y`.
bool long__greater_than( long x, long y );         // Returns `x > y`.

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


/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

long long__succ( long x );
// Returns `x + 1`.
// @requires x != long__max_bound()

long long__succ_b( long x );
// Returns `x + 1`, or `long__max_bound()` if `x == long__max_bound()`.

long long__pred( long x );
// Returns `x - 1`.
// @requires x != long__min_bound()

long long__pred_b( long x );
// Returns `x - 1`, or `long__min_bound()` if `x == long__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool long__is_signed( void );
// Returns `true`, because `long` values can be negative.

bool long__can_add( long x, long y );
// Returns the boolean that the behavior of `x + y` is well-defined.
// Equivalent to:
//
//        implies( y > 0, x <= ( long__max_bound - y ) )
//     && implies( y < 0, x >= ( long__min_bound - y ) )

bool long__can_sub( long x, long y );
// Returns the boolean that the behavior of `x - y` is well-defined.
// Equivalent to:
//
//        implies( y > 0, x >= ( long__min_bound - y ) )
//     && implies( y < 0, x <= ( long__max_bound - y ) )

bool long__can_mul( long x, long y );
// Returns the boolean that the behavior of `x * y` is well-defined.
// Equivalent to:
//
//     ( x > 0 ) ? ( y > 0 ) ? ( x <= ( long__max_bound / y ) )
//                           : ( y >= ( long__min_bound / x ) )
//               : ( y > 0 ) ? ( x >= ( long__min_bound / y ) )
//                           : implies( x != 0, y >= ( long__max_bound / x ) )

bool long__can_div( long x, long y );
// Returns the boolean that the behavior of `x / y` is well-defined.
// Equivalent to:
//
//     ( y != 0 ) && !( ( x == long__min_bound ) && ( y == -1 ) )

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
// @requires x != long__min_bound

long long__abs( long x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != long__min_bound

bool long__same_sign( long x, long y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool long__is_negative( long x );     // Returns `x < 0`.
bool long__is_nonpositive( long x );  // Returns `x <= 0`.
bool long__is_zero( long x );         // Returns `x == 0`.
bool long__is_nonnegative( long x );  // Returns `x >= 0`.
bool long__is_positive( long x );     // Returns `x > 0`.
ord  long__compare_0( long x );       // Returns `long__compare( x, 0 )`.

bool long__is_even( long x );     // Returns `x % 2 == 0`.
bool long__is_odd( long x );      // Returns `x % 2 == 1`.

long long__add_2( long x );    // Returns `long__add( x, 2 )`.
long long__sub_2( long x );    // Returns `long__sub( x, 2 )`.
long long__mul_2( long x );    // Returns `long__mul( x, 2 )`.
long long__div_2( long x );    // Returns `long__div( x, 2 )`.
long long__mod_2( long x );    // Returns `long__mod( x, 2 )`.

long long__mul_10( long x );   // Returns `long__mul( x, 10 )`.
long long__div_10( long x );   // Returns `long__div( x, 10 )`.
long long__mod_10( long x );   // Returns `long__mod( x, 10 )`.


/////////////////////////////
/// READ TYPECLASS
/////////////////////////////

Result_long long__from_str( char const * str );
// Parses the given `str` to produce the contained `long` value. Errors:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but also a non-numeric suffix;
// - `ERANGE` if the resulting value is out of range of `long`;

long long__from_str_e( char const * str, int * err );
// Like `long__from_str()`, but setting the given `err` value to the error,
// or `0` if no error.


#endif

