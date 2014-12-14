
#ifndef LIBBASE_STR_H
#define LIBBASE_STR_H


#include <libtypes/types.h>


// A "str" is an array of `char`s terminated by the null character `\0`.


char const * str__id( char const * xs );         // Returns `xs`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool str__equal( char const * xs, char const * ys );
// Returns `true` if every `i`th character in `xs` is equal to the `i`th
// character in `ys`, including the null byte.

bool str__not_equal( char const * xs, char const * ys );
// Returns `!str__equal( xs, ys )`.


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


#endif

