
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


#ifndef LIBBASE_ORD_H
#define LIBBASE_ORD_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_ord {
    ord value;
    bool nothing;
} Maybe_ord;


typedef struct result_ord {
    ord value;
    int error;
} Result_ord;


typedef struct arrayc_ord {
    ord const * e;
    size_t capacity;
} ArrayC_ord;


typedef struct arraym_ord {
    ord * e;
    size_t capacity;
} ArrayM_ord;


typedef struct vec_ord {
    ord * e;
    size_t length;
    size_t capacity;
} Vec_ord;


ord ord__id( ord x );
// The identity function; returns `x`.


ord ord__normalize( ord x );
// `ord` values may be less than `LT` or greater than `GT`. Although
// developers should avoid letting their `ord` variables take those values,
// these provided functions do their best to handle them sensibly -- values
// `<= LT` are taken to be `LT`, and values `>= GT` are taken to be `GT`.
// This function is the equivalent of `ord__clamp( LT, GT, x )`, and is used
// to provide that functionality.



///////////////////////////////////
/// TYPECLASS: BOUNDED
///////////////////////////////////

ord ord__min_bound( void );
// Returns the minimum value representable by the `ord` type.

ord ord__max_bound( void );
// Returns the maximum value representable by the `ord` type.



///////////////////////////////////
/// TYPECLASS: EQ
///////////////////////////////////

bool ord__equal( ord x, ord y );
// Returns `true` if `x == y`, or `false` if not.

bool ord__not_equal( ord x, ord y );
// Returns `true` if `x != y`, or `false` if not.



///////////////////////////////////
/// TYPECLASS: ORD
///////////////////////////////////

ord ord__compare( ord x, ord y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool ord__less_than( ord x, ord y );
// Returns `true` if `x < y`, or `false` if not.

bool ord__less_than_or_eq( ord x, ord y );
// Returns `true` if `x <= y`, or `false` if not.

bool ord__greater_than_or_eq( ord x, ord y );
// Returns `true` if `x >= y`, or `false` if not.

bool ord__greater_than( ord x, ord y );
// Returns `true` if `x > y`, or `false` if not.

ord ord__min2( ord x, ord y );
// Returns `x` if `x < y`, or `y` otherwise.

ord ord__max2( ord x, ord y );
// Returns `x` if `x > y`, or `y` otherwise.

ord ord__min_n( size_t n, ord const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ord ord__max_n( size_t n, ord const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define ord__min( ... ) \
    ord__min_n( PP_COUNT( __VA_ARGS__ ), ( ord[] ){ __VA_ARGS__ } )

// @public
#define ord__max( ... ) \
    ord__max_n( PP_COUNT( __VA_ARGS__ ), ( ord[] ){ __VA_ARGS__ } )

ord ord__clamp( ord lower, ord upper, ord x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



///////////////////////////////////
/// TYPECLASS: ENUM
///////////////////////////////////

ord ord__succ( ord x );
// Returns `x + 1`.
// @requires x != ord__max_bound()

ord ord__succ_b( ord x );
// Returns `x + 1`, or `ord__max_bound()` if
// `x == ord__max_bound()`.

ord ord__pred( ord x );
// Returns `x - 1`.
// @requires x != ord__min_bound()

ord ord__pred_b( ord x );
// Returns `x - 1`, or `ord__min_bound()` if
// `x == ord__min_bound()`.



///////////////////////////////////
/// TYPECLASS: READ
///////////////////////////////////

ord ord__from_str( char const * str );
// Returns `LT` if the given `str` contains `"LT"` surrounded only by
// whitespace, or `EQ` if it contains `"EQ"` surrounded only by whitespace, or
// `GT` if it contains `"GT"` surrounded only by whitespace. On error, returns
// `EQ` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if there was a parse error.



///////////////////////////////////
/// TYPECLASS: TO_CONSTSTR
///////////////////////////////////

char const *
ord__to_conststr( ord );
// Returns `"LT"` if `x == LT`, `"EQ"` if `x == EQ`, or `"GT"` if `x == GT`.


#endif // ifndef LIBBASE_ORD_H

