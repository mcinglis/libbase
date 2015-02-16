
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


#ifndef LIBBASE_BOOL_H
#define LIBBASE_BOOL_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_bool {
    bool value;
    bool nothing;
} Maybe_bool;


bool bool__id( bool x );
// The identity function; returns `x`.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

bool bool__min_bound( void );
// Returns the minimum value representable by the `bool` type.

bool bool__max_bound( void );
// Returns the maximum value representable by the `bool` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool bool__equal( bool x, bool y );
// Returns `true` if `x == y`, or `false` if not.

bool bool__not_equal( bool x, bool y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord bool__compare( bool x, bool y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool bool__less_than( bool x, bool y );
// Returns `true` if `x < y`, or `false` if not.

bool bool__less_than_or_eq( bool x, bool y );
// Returns `true` if `x <= y`, or `false` if not.

bool bool__greater_than_or_eq( bool x, bool y );
// Returns `true` if `x >= y`, or `false` if not.

bool bool__greater_than( bool x, bool y );
// Returns `true` if `x > y`, or `false` if not.

bool bool__min2( bool x, bool y );
// Returns `x` if `x < y`, or `y` otherwise.

bool bool__max2( bool x, bool y );
// Returns `x` if `x > y`, or `y` otherwise.

bool bool__min_n( size_t n, bool const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

bool bool__max_n( size_t n, bool const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define bool__min( ... ) \
    bool__min_n( PP_COUNT( __VA_ARGS__ ), ( bool[] ){ __VA_ARGS__ } )

// @public
#define bool__max( ... ) \
    bool__max_n( PP_COUNT( __VA_ARGS__ ), ( bool[] ){ __VA_ARGS__ } )

bool bool__clamp( bool lower, bool upper, bool x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

bool bool__succ( bool x );
// Returns `x + 1`.
// @requires x != bool__max_bound()

bool bool__succ_b( bool x );
// Returns `x + 1`, or `bool__max_bound()` if
// `x == bool__max_bound()`.

bool bool__pred( bool x );
// Returns `x - 1`.
// @requires x != bool__min_bound()

bool bool__pred_b( bool x );
// Returns `x - 1`, or `bool__min_bound()` if
// `x == bool__min_bound()`.



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

bool bool__from_str( char const * str );
// Returns `true` if the given `str` contains `"true"` surrounded only by
// whitespace, or `false` if it contains `"false"` surrounded only by
// whitespace. On error, returns `false` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if there was a parse error.



///////////////////////////////////
/// TYPECLASS: TO_CONSTSTR
///////////////////////////////////

char const *
bool__to_conststr( bool x );
// Returns `"true"` if `x == true`, or `"false"` otherwise.


#endif // ifndef LIBBASE_BOOL_H

