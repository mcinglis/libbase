
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


#ifndef LIBBASE_MUTSTR_H
#define LIBBASE_MUTSTR_H


#include <libtypes/types.h>


// A "mutstr" is a mutable `char` array terminated by a null character.


typedef struct maybe_mutstr {
    char * value;
    bool nothing;
} Maybe_mutstr;


typedef struct result_mutstr {
    char * value;
    int error;
} Result_mutstr;


typedef struct arrayc_mutstr {
    char * const * e;
    size_t capacity;
} ArrayC_mutstr;


typedef struct arraym_mutstr {
    char * * e;
    size_t capacity;
} ArrayM_mutstr;


typedef struct vec_mutstr {
    char * * e;
    size_t length;
    size_t capacity;
} Vec_mutstr;


char *
mutstr__id( char * xs );
// The identity function; returns `xs`.


size_t
mutstr__length( char * xs );
// Returns the index of the first `'\0'` byte in `xs`.
// @require xs != NULL


size_t
mutstr__size( char * xs );
// Returns the byte size of `xs` - i.e. `mutstr__length( xs ) + 1`.
// @require xs != NULL


bool
mutstr__equal( char * xs,
               char * ys );
// Returns `true` if every `i`th character in `xs` is equal to the `i`th
// character in `ys`, including the null byte.
// @require xs != NULL, ys != NULL


bool
mutstr__not_equal( char * xs,
                   char * ys );
// Returns `!mutstr__equal( xs, ys )`.
// @require xs != NULL, ys != NULL


bool
mutstr__equal_i( char * xs,
                 char * ys );
// Like `mutstr__equal()`, except case-insensitive.
// @require xs != NULL, ys != NULL


bool
mutstr__not_equal_i( char * xs,
                     char * ys );
// Returns `!mutstr__equal_i( xs, ys )`.
// @require xs != NULL, ys != NULL


bool
mutstr__starts_with( char * xs,
                     char * prefix );
// Returns `true` if `prefix` is a prefix of `xs`, or `false` otherwise.
// @require xs != NULL, prefix != NULL


bool
mutstr__ends_with( char * xs,
                   char * suffix );
// Returns `true` if `suffix` is a suffix of `xs`, or `false` otherwise.
// @require xs != NULL, suffix != NULL


ord
mutstr__compare( char * xs,
                 char * ys );
// Returns the lexicographical comparison of `xs` and `ys`.
// @require xs != NULL, ys != NULL


ord
mutstr__compare_i( char * xs,
                   char * ys );
// Returns the lexicographical comparison of `xs` and `ys`.
// @require xs != NULL, ys != NULL


bool
mutstr__less_than( char * xs,
                   char * ys );
// Returns `mutstr__compare( xs, ys ) == LT`.
// @require xs != NULL, ys != NULL


bool
mutstr__less_than_or_eq( char * xs,
                         char * ys );
// Returns `mutstr__compare( xs, ys ) <= EQ`.
// @require xs != NULL, ys != NULL


bool
mutstr__greater_than_or_eq( char * xs,
                            char * ys );
// Returns `mutstr__compare( xs, ys ) >= EQ`.
// @require xs != NULL, ys != NULL


bool
mutstr__greater_than( char * xs,
                      char * ys );
// Returns `mutstr__compare( xs, ys ) == GT`.
// @require xs != NULL, ys != NULL


char *
mutstr__min2( char * xs,
              char * ys );
// If `mutstr__less_than( xs, ys )`, returns `xs`, otherwise returns `ys`.
// @require xs != NULL, ys != NULL


char *
mutstr__max2( char * xs,
              char * ys );
// If `mutstr__greater_than( xs, ys )`, returns `xs`, otherwise returns `ys`.
// @require xs != NULL, ys != NULL


char *
mutstr__min_n( size_t n,
               char * const * xss );
// Returns the minimum mutstr of the first `n` elements in the array `xss`.
// @requires n != 0, xss != NULL, xss[ i ] != NULL for i in 0..n-1


char *
mutstr__max_n( size_t n,
               char * const * xss );
// Returns the maximum mutstr of the first `n` elements in the array `xss`.
// @requires n != 0, xss != NULL, xss[ i ] != NULL for i in 0..n-1


// @public
#define mutstr__min( ... ) \
    mutstr__min_n( PP_COUNT( __VA_ARGS__ ), \
                   ( char * [] ){ __VA_ARGS__ } )


// @public
#define mutstr__max( ... ) \
    mutstr__max_n( PP_COUNT( __VA_ARGS__ ), \
                   ( char * [] ){ __VA_ARGS__ } )


char *
mutstr__clamp( char * lower,
               char * upper,
               char * xs );
// Returns: - `lower` if `mutstr__greater_than( lower, xs )`;
//          - `upper` if `mutstr__less_than( upper, xs )`;
//          - `xs` otherwise
// @requires lower != NULL, upper != NULL, xs != NULL


#endif // ifndef LIBBASE_MUTSTR_H

