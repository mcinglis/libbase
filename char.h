
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


#ifndef LIBBASE_CHAR_H
#define LIBBASE_CHAR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct {
    char value;
    bool nothing;
} Maybe_char;


typedef struct {
    char value;
    int error;
} Result_char;


char char__id( char x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

char char__min_bound( void );     // Returns `CHAR_MIN`.
char char__max_bound( void );     // Returns `CHAR_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool char__equal( char x, char y );        // Returns `x == y`.
bool char__not_equal( char x, char y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord char__compare( char x, char y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool char__less_than( char x, char y );            // Returns `x < y`.
bool char__less_than_or_eq( char x, char y );      // Returns `x <= y`.
bool char__greater_than_or_eq( char x, char y );   // Returns `x >= y`.
bool char__greater_than( char x, char y );         // Returns `x > y`.

char char__min2( char x, char y );
// Returns `x` if `x < y`, or `y` otherwise.

char char__max2( char x, char y );
// Returns `x` if `x > y`, or `y` otherwise.

char char__min_n( size_t n, char const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

char char__max_n( size_t n, char const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define char__min( ... ) \
    char__min_n( PP_COUNT( __VA_ARGS__ ), ( char[] ){ __VA_ARGS__ } )

// @public
#define char__max( ... ) \
    char__max_n( PP_COUNT( __VA_ARGS__ ), ( char[] ){ __VA_ARGS__ } )

char char__clamp( char lower, char upper, char x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`


/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

char char__succ( char x );
// Returns `x + 1`.
// @requires x != char__max_bound()

char char__succ_b( char x );
// Returns `x + 1`, or `char__max_bound()` if `x == char__max_bound()`.

char char__pred( char x );
// Returns `x - 1`.
// @requires x != char__min_bound()

char char__pred_b( char x );
// Returns `x - 1`, or `char__min_bound()` if `x == char__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool char__is_signed( void );
// Returns `true`, because `char` values can be negative.

bool char__can_add( char x, char y );
// Returns the boolean that the behavior of `x + y` is well-defined.
// Equivalent to:
//
//        implies( y > 0, x <= ( char__max_bound - y ) )
//     && implies( y < 0, x >= ( char__min_bound - y ) )

bool char__can_sub( char x, char y );
// Returns the boolean that the behavior of `x - y` is well-defined.
// Equivalent to:
//
//        implies( y > 0, x >= ( char__min_bound - y ) )
//     && implies( y < 0, x <= ( char__max_bound - y ) )

bool char__can_mul( char x, char y );
// Returns the boolean that the behavior of `x * y` is well-defined.
// Equivalent to:
//
//     ( x > 0 ) ? ( y > 0 ) ? ( x <= ( char__max_bound / y ) )
//                           : ( y >= ( char__min_bound / x ) )
//               : ( y > 0 ) ? ( x >= ( char__min_bound / y ) )
//                           : implies( x != 0, y >= ( char__max_bound / x ) )

bool char__can_div( char x, char y );
// Returns the boolean that the behavior of `x / y` is well-defined.
// Equivalent to:
//
//     ( y != 0 ) && !( ( x == char__min_bound ) && ( y == -1 ) )

char char__add( char x, char y );
// Returns `x + y`.
// @requires char__can_add( x, y )

char char__sub( char x, char y );
// Returns `x - y`.
// @requires char__can_sub( x, y )

char char__mul( char x, char y );
// Returns `x * y`.
// @requires char__can_mul( x, y )

char char__div( char x, char y );
// Returns `x / y`.
// @requires char__can_div( x, y )

char char__mod( char x, char y );
// Returns `x % y`.
// @requires char__can_div( x, y )

char char__negate( char x );
// Returns `-x`.
// @requires x != char__min_bound

char char__abs( char x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != char__min_bound

bool char__same_sign( char x, char y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool char__is_negative( char x );     // Returns `x < 0`.
bool char__is_nonpositive( char x );  // Returns `x <= 0`.
bool char__is_zero( char x );         // Returns `x == 0`.
bool char__is_nonnegative( char x );  // Returns `x >= 0`.
bool char__is_positive( char x );     // Returns `x > 0`.
ord  char__compare_0( char x );       // Returns `char__compare( x, 0 )`.

bool char__is_even( char x );     // Returns `x % 2 == 0`.
bool char__is_odd( char x );      // Returns `x % 2 == 1`.

char char__add_2( char x );    // Returns `char__add( x, 2 )`.
char char__sub_2( char x );    // Returns `char__sub( x, 2 )`.
char char__mul_2( char x );    // Returns `char__mul( x, 2 )`.
char char__div_2( char x );    // Returns `char__div( x, 2 )`.
char char__mod_2( char x );    // Returns `char__mod( x, 2 )`.

char char__mul_10( char x );   // Returns `char__mul( x, 10 )`.
char char__div_10( char x );   // Returns `char__div( x, 10 )`.
char char__mod_10( char x );   // Returns `char__mod( x, 10 )`.


/////////////////////////////
/// READ TYPECLASS
/////////////////////////////

Result_char char__from_str( char const * str );
// Parses the given `str` to produce the contained `char` value. Errors:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but also a non-numeric suffix;
// - `ERANGE` if the resulting value is out of range of `char`;

char char__from_str_e( char const * str, int * err );
// Like `char__from_str()`, but setting the given `err` value to the error,
// or `0` if no error.


#endif

