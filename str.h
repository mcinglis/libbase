
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


#ifndef LIBBASE_STR_H
#define LIBBASE_STR_H


#include <libtypes/types.h>


// A "str" is an array of `char`s terminated by the null character `\0`.


typedef struct {
    char const * value;
    bool nothing;
} Maybe_str;


typedef struct {
    char const * value;
    int error;
} Result_str;


char const * str__id( char const * xs );         // Returns `xs`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool str__equal( char const * xs, char const * ys );
// Returns `true` if every `i`th character in `xs` is equal to the `i`th
// character in `ys`, including the null byte.

bool str__not_equal( char const * xs, char const * ys );
// Returns `!str__equal( xs, ys )`.

// EXTENSIONS:

bool str__equal_i( char const * xs, char const * ys );
// Like `str__equal()`, except case-insensitive.

bool str__not_equal_i( char const * xs, char const * ys );
// Returns `!str__equal_i( xs, ys )`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord str__compare( char const * xs, char const * ys );
// Returns the lexicographical comparison of `xs` and `ys`.

bool str__less_than( char const * xs, char const * ys );
// Returns `str__compare( xs, ys ) == LT`.

bool str__less_than_or_eq( char const * xs, char const * ys );
// Returns `str__compare( xs, ys ) <= EQ`.

bool str__greater_than_or_eq( char const * xs, char const * ys );
// Returns `str__compare( xs, ys ) >= EQ`.

bool str__greater_than( char const * xs, char const * ys );
// Returns `str__compare( xs, ys ) == GT`.

char const * str__min2( char const * xs, char const * ys );
// If `str__less_than( xs, ys )`, returns `xs`, otherwise returns `ys`.

char const * str__max2( char const * xs, char const * ys );
// If `str__greater_than( xs, ys )`, returns `xs`, otherwise returns `ys`.

char const * str__min_n( size_t n, char const * const * xss );
// Returns the minimum str of the first `n` elements in the array `xss`.
// @requires n > 0, xss != NULL, xss[ i ] != NULL for i in 0..n-1

char const * str__max_n( size_t n, char const * const * xss );
// Returns the maximum str of the first `n` elements in the array `xss`.
// @requires n > 0, xss != NULL

// @public
#define str__min( ... ) \
    str__min_n( PP_COUNT( __VA_ARGS__ ), ( char const * [] ){ __VA_ARGS__ } )

// @public
#define str__max( ... ) \
    str__max_n( PP_COUNT( __VA_ARGS__ ), ( char const * [] ){ __VA_ARGS__ } )

char const * str__clamp( char const * lower,
                         char const * upper,
                         char const * xs );
// Returns: - `lower` if `str__greater_than( lower, xs )`;
//          - `upper` if `str__less_than( upper, xs )`;
//          - `xs` otherwise

// EXTENSIONS:

ord str__compare_i( char const * xs, char const * ys );
// Returns the lexicographical comparison of `xs` and `ys`.


#endif

