
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


#ifndef LIBBASE_CONSTPTR_H
#define LIBBASE_CONSTPTR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_constptr {
    void const * value;
    bool nothing;
} Maybe_constptr;


typedef struct result_constptr {
    void const * value;
    int error;
} Result_constptr;


typedef struct arrayc_constptr {
    void const * const * e;
    size_t length;
} ArrayC_constptr;


typedef struct arraym_constptr {
    void const * * e;
    size_t length;
} ArrayM_constptr;


typedef struct vec_constptr {
    void const * * e;
    size_t length;
    size_t capacity;
} Vec_constptr;


void const * constptr__id( void const * x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool constptr__equal( void const * x, void const * y );
// Returns `true` if `x == y`, or `false` if not.

bool constptr__not_equal( void const * x, void const * y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord constptr__compare( void const * x, void const * y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool constptr__less_than( void const * x, void const * y );
// Returns `true` if `x < y`, or `false` if not.

bool constptr__less_than_or_eq( void const * x, void const * y );
// Returns `true` if `x <= y`, or `false` if not.

bool constptr__greater_than_or_eq( void const * x, void const * y );
// Returns `true` if `x >= y`, or `false` if not.

bool constptr__greater_than( void const * x, void const * y );
// Returns `true` if `x > y`, or `false` if not.

void const * constptr__min2( void const * x, void const * y );
// Returns `x` if `x < y`, or `y` otherwise.

void const * constptr__max2( void const * x, void const * y );
// Returns `x` if `x > y`, or `y` otherwise.

void const * constptr__min_n( size_t n, void const * const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

void const * constptr__max_n( size_t n, void const * const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define constptr__min( ... ) \
    constptr__min_n( PP_COUNT( __VA_ARGS__ ), ( void const *[] ){ __VA_ARGS__ } )

// @public
#define constptr__max( ... ) \
    constptr__max_n( PP_COUNT( __VA_ARGS__ ), ( void const *[] ){ __VA_ARGS__ } )

void const * constptr__clamp( void const * lower, void const * upper, void const * x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`


#endif // ifndef LIBBASE_CONSTPTR_H

