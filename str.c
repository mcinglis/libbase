
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


#include "str.h"

#include <ctype.h>

#include <libmacro/require.h>


char const *
str__id( char const * const xs ) {
    return xs;
}


bool
str__equal( char const * const xs,
            char const * const ys )
{
    return str__compare( xs, ys ) == EQ;
}


bool
str__not_equal( char const * const xs,
                char const * const ys )
{
    return !str__equal( xs, ys );
}


bool
str__equal_i( char const * const xs,
              char const * const ys )
{
    return str__compare_i( xs, ys ) == EQ;
}


bool
str__not_equal_i( char const * const xs,
                  char const * const ys )
{
    return !str__equal_i( xs, ys );
}


ord
str__compare( char const * const xs,
              char const * const ys )
{
    REQUIRE( xs != NULL, ys != NULL );

    size_t i = 0;
    while ( xs[ i ] == ys[ i ]
         && xs[ i ] != '\0' ) {
        i++;
    }
    return ( xs[ i ] > ys[ i ] ) - ( xs[ i ] < ys[ i ] );
}


ord
str__compare_i( char const * const xs,
                char const * const ys )
{
    REQUIRE( xs != NULL, ys != NULL );

    size_t i = 0;
    char x, y;
    while ( x = tolower( xs[ i ] ),
            y = tolower( ys[ i ] ),
            x == y && x != '\0' ) {
        i++;
    }
    return ( x > y ) - ( x < y );
}


bool
str__less_than( char const * const xs,
                char const * const ys )
{
    return str__compare( xs, ys ) == LT;
}


bool
str__less_than_or_eq( char const * const xs,
                      char const * const ys )
{
    return str__compare( xs, ys ) <= EQ;
}


bool
str__greater_than_or_eq( char const * const xs,
                         char const * const ys )
{
    return str__compare( xs, ys ) >= EQ;
}


bool
str__greater_than( char const * const xs,
                   char const * const ys )
{
    return str__compare( xs, ys ) == GT;
}


char const *
str__min2( char const * const xs,
           char const * const ys )
{
    return str__less_than( xs, ys ) ? xs : ys;
}


char const *
str__max2( char const * const xs,
           char const * const ys )
{
    return str__greater_than( xs, ys ) ? xs : ys;
}


char const *
str__min_n( size_t const n,
            char const * const * const xss )
{
    REQUIRE( n > 0, xss != NULL );

    char const * min = xss[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        if ( str__less_than( xss[ i ], min ) ) {
            min = xss[ i ];
        }
    }
    return min;
}


char const *
str__max_n( size_t const n,
            char const * const * const xss )
{
    REQUIRE( n > 0, xss != NULL );

    char const * max = xss[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        if ( str__greater_than( xss[ i ], max ) ) {
            max = xss[ i ];
        }
    }
    return max;
}


char const *
str__clamp( char const * const lower,
            char const * const upper,
            char const * const xs )
{
    return str__greater_than( lower, xs ) ? lower
         : str__less_than( upper, xs ) ? upper
         : xs;
}


