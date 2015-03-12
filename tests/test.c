
#include <stdio.h>
#include <stdlib.h>

#include <libtypes/types.h>
#include <libmacro/assert.h>
#include <libmacro/logic.h>

#include "../int.h"
#include "../uchar.h"


int
main( void )
{
    size_t const num_tests = 1000;
    for ( size_t i = 0; i < num_tests; i++ ) {
        int const x = random() % int__max_bound();
        int const y = random() % int__max_bound();
        int const z = random() % int__max_bound();
        // To avoid warnings when compiling without assertions:
        ( void ) x;
        ( void ) y;
        ( void ) z;
        ASSERT( int__equal( x, x ),
                int__equal( y, y ),
                IMPLIES( int__compare( x, y ) == LT,
                         int__compare( y, x ) == GT
                         && int__min( x, y ) == x
                         && int__max( x, y ) == y ),
                IMPLIES( int__compare( x, y ) == EQ,
                         int__equal( x, y ) ),
                IMPLIES( int__compare( x, y ) == GT,
                         int__compare( y, x ) == LT
                         && int__min( x, y ) == y
                         && int__max( x, y ) == x ),
                int__min( x, y, z ) == int__min2( x, int__min2( y, z ) ),
                int__min( x, y, z ) <= int__max( x, y, z ) );
    }
    printf( "All `int` assertions passed.\n" );
    for ( size_t i = 0; i < num_tests; i++ ) {
        uchar const x = random() % uchar__max_bound();
        uchar const y = random() % uchar__max_bound();
        uchar const z = random() % uchar__max_bound();
        // To avoid warnings when compiling without assertions:
        ( void ) x;
        ( void ) y;
        ( void ) z;
        ASSERT( uchar__equal( x, x ),
                uchar__equal( y, y ),
                IMPLIES( uchar__compare( x, y ) == LT,
                         uchar__compare( y, x ) == GT
                         && uchar__min( x, y ) == x
                         && uchar__max( x, y ) == y ),
                IMPLIES( uchar__compare( x, y ) == EQ,
                         uchar__equal( x, y ) ),
                IMPLIES( uchar__compare( x, y ) == GT,
                         uchar__compare( y, x ) == LT
                         && uchar__min( x, y ) == y
                         && uchar__max( x, y ) == x ),
                uchar__min( x, y, z ) == uchar__min2( x, uchar__min2( y, z ) ),
                uchar__min( x, y, z ) <= uchar__max( x, y, z ),
                uchar__equal_i( 'i', 'I' ),
                uchar__compare_i( 'x', 'X' ) == EQ,
                uchar__compare_i( 'x', 'Y' ) == LT );
    }
    printf( "All `uchar` assertions passed.\n" );
}



