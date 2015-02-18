
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


#include "mutstr.h"

#include <ctype.h>

#include <libtypes/types.h>
#include <libmacro/assert.h>


char *
mutstr__id( char * const xs ) {
    return xs;
}


size_t
mutstr__length( char * const xs )
{
    ASSERT( xs != NULL );

    size_t len = 0;
    while ( xs[ len ] != '\0' ) {
        len++;
    }
    return len;
}


size_t
mutstr__size( char * const xs )
{
    return mutstr__length( xs ) + 1;
}


bool
mutstr__equal( char * const xs,
               char * const ys )
{
    return mutstr__compare( xs, ys ) == EQ;
}


bool
mutstr__not_equal( char * const xs,
                   char * const ys )
{
    return !mutstr__equal( xs, ys );
}


bool
mutstr__equal_i( char * const xs,
                 char * const ys )
{
    return mutstr__compare_i( xs, ys ) == EQ;
}


bool
mutstr__not_equal_i( char * const xs,
                     char * const ys )
{
    return !mutstr__equal_i( xs, ys );
}


bool
mutstr__starts_with( char * const xs,
                     char * const prefix )
{
    ASSERT( xs != NULL, prefix != NULL );

    for ( size_t i = 0; prefix[ i ] != '\0'; i++ ) {
        if ( xs[ i ] != prefix[ i ] ) {
            return false;
        }
    }
    return true;
}


bool
mutstr__ends_with( char * const xs,
                   char * const suffix )
{
    ASSERT( xs != NULL, suffix != NULL );

    size_t const xs_len = mutstr__length( xs );
    size_t const suf_len = mutstr__length( suffix );
    if ( suf_len > xs_len ) {
        return false;
    }
    for ( size_t i = 0; suffix[ i ] != '\0'; i++ ) {
        if ( xs[ i + ( xs_len - suf_len ) ] != suffix[ i ] ) {
            return false;
        }
    }
    return true;
}


ord
mutstr__compare( char * const xs,
                 char * const ys )
{
    ASSERT( xs != NULL, ys != NULL );

    size_t i = 0;
    while ( xs[ i ] == ys[ i ]
         && xs[ i ] != '\0' ) {
        i++;
    }
    return ( xs[ i ] > ys[ i ] ) - ( xs[ i ] < ys[ i ] );
}


ord
mutstr__compare_i( char * const xs,
                   char * const ys )
{
    ASSERT( xs != NULL, ys != NULL );

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
mutstr__less_than( char * const xs,
                   char * const ys )
{
    return mutstr__compare( xs, ys ) == LT;
}


bool
mutstr__less_than_or_eq( char * const xs,
                         char * const ys )
{
    return mutstr__compare( xs, ys ) <= EQ;
}


bool
mutstr__greater_than_or_eq( char * const xs,
                            char * const ys )
{
    return mutstr__compare( xs, ys ) >= EQ;
}


bool
mutstr__greater_than( char * const xs,
                      char * const ys )
{
    return mutstr__compare( xs, ys ) == GT;
}


char *
mutstr__min2( char * const xs,
              char * const ys )
{
    return mutstr__less_than( xs, ys ) ? xs : ys;
}


char *
mutstr__max2( char * const xs,
              char * const ys )
{
    return mutstr__greater_than( xs, ys ) ? xs : ys;
}


char *
mutstr__min_n( size_t const n,
               char * const * const xss )
{
    ASSERT( n != 0, xss != NULL );

    char * min = xss[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        if ( mutstr__less_than( xss[ i ], min ) ) {
            min = xss[ i ];
        }
    }
    return min;
}


char *
mutstr__max_n( size_t const n,
               char * const * const xss )
{
    ASSERT( n != 0, xss != NULL );

    char * max = xss[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {
        if ( mutstr__greater_than( xss[ i ], max ) ) {
            max = xss[ i ];
        }
    }
    return max;
}


char *
mutstr__clamp( char * const lower,
               char * const upper,
               char * const xs )
{
    ASSERT( lower != NULL, upper != NULL, xs != NULL );

    return mutstr__greater_than( lower, xs ) ? lower
         : mutstr__less_than( upper, xs )    ? upper
                                             : xs;
}


