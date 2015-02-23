
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


#ifndef LIBBASE_PTR_H
#define LIBBASE_PTR_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_ptr {
    void * value;
    bool nothing;
} Maybe_ptr;


typedef struct result_ptr {
    void * value;
    int error;
} Result_ptr;


typedef struct arrayc_ptr {
    void * const * e;
    size_t length;
} ArrayC_ptr;


typedef struct arraym_ptr {
    void * * e;
    size_t length;
} ArrayM_ptr;


typedef struct vec_ptr {
    void * * e;
    size_t length;
    size_t capacity;
} Vec_ptr;


void * ptr__id( void * x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool ptr__equal( void * x, void * y );
// Returns `true` if `x == y`, or `false` if not.

bool ptr__not_equal( void * x, void * y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord ptr__compare( void * x, void * y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ptr__less_than( void * x, void * y );
// Returns `true` if `x < y`, or `false` if not.

bool ptr__less_than_or_eq( void * x, void * y );
// Returns `true` if `x <= y`, or `false` if not.

bool ptr__greater_than_or_eq( void * x, void * y );
// Returns `true` if `x >= y`, or `false` if not.

bool ptr__greater_than( void * x, void * y );
// Returns `true` if `x > y`, or `false` if not.

void * ptr__min2( void * x, void * y );
// Returns `x` if `x < y`, or `y` otherwise.

void * ptr__max2( void * x, void * y );
// Returns `x` if `x > y`, or `y` otherwise.

void * ptr__min_n( size_t n, void * const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

void * ptr__max_n( size_t n, void * const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ptr__min( ... ) \
    ptr__min_n( PP_COUNT( __VA_ARGS__ ), ( void *[] ){ __VA_ARGS__ } )

// @public
#define ptr__max( ... ) \
    ptr__max_n( PP_COUNT( __VA_ARGS__ ), ( void *[] ){ __VA_ARGS__ } )

void * ptr__clamp( void * lower, void * upper, void * x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`

bool ptr__in_range( void * lower, void * upper, void * x );
// Returns `lower <= x && x <= upper`.

bool ptr__in_range_x( void * lower, void * upper, void * x );
// Returns `lower < x && x < upper`.


#endif // ifndef LIBBASE_PTR_H

