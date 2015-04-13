
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libtypes/types.h>
#include <libmacro/assert.h>
#include <libmacro/logic.h>

#include "../uchar.h"
#include "../int.h"
#include "../ulong.h"


static
bool
streq( char const * const xs,
       char const * const ys )
{
    return strcmp( xs, ys ) == 0;
}


static
void
test_update_average_unsigned( void )
{
    ulong average = 100;
    intmax_t num = 0;
    average = ulong__update_average( average, num++, 3 );
    ASSERT( average == 3 );
    average = ulong__update_average( average, num++, 5 );
    ASSERT( average == 4 );
    average = ulong__update_average( average, num++, 7 );
    ASSERT( average == 5 );
    average = ulong__update_average( average, num++, 25 );
    ASSERT( average == 10 );
    average = ulong__update_average( average, num++, 11 );
    ASSERT( average == 10 );
    average = ulong__update_average( average, num++, 2 );
    ASSERT( average == 8 );
}


static
void
test_update_average_signed( void )
{
    int average = 100;
    intmax_t num = 0;
    average = int__update_average( average, num++, 3 );
    ASSERT( average == 3 );
    average = int__update_average( average, num++, 5 );
    ASSERT( average == 4 );
    average = int__update_average( average, num++, 7 );
    ASSERT( average == 5 );
    average = int__update_average( average, num++, 25 );
    ASSERT( average == 10 );
    average = int__update_average( average, num++, 11 );
    ASSERT( average == 10 );
    average = int__update_average( average, num++, 2 );
    ASSERT( average == 8 );
    average = int__update_average( average, num++, -20 );
    ASSERT( average == 4 );
    average = int__update_average( average, num++, -50 );
    ASSERT( average == -2 );
    average = int__update_average( average, num++, -100 );
    ASSERT( average == -12 );
}


static
void
test_update_average( void )
{
    test_update_average_unsigned();
    test_update_average_signed();
}


static
void
test_to_str( void )
{
    char x[ 32 ];
    int__into_strm( 0, x, sizeof x );
    ASSERT( streq( x, "0" ) );
    int__into_strm( 5, x, sizeof x );
    ASSERT( streq( x, "5" ) );
    int__into_strm( 10, x, sizeof x );
    ASSERT( streq( x, "10" ) );
    int__into_strm( 20, x, sizeof x );
    ASSERT( streq( x, "20" ) );
    int__into_strm( 100, x, sizeof x );
    ASSERT( streq( x, "100" ) );
    int__into_strm( 123456789, x, sizeof x );
    ASSERT( streq( x, "123456789" ) );
    int__into_strm( -5, x, sizeof x );
    ASSERT( streq( x, "-5" ) );
    int__into_strm( -10, x, sizeof x );
    ASSERT( streq( x, "-10" ) );
    int__into_strm( -20, x, sizeof x );
    ASSERT( streq( x, "-20" ) );
    int__into_strm( -100, x, sizeof x );
    ASSERT( streq( x, "-100" ) );
    int__into_strm( -123456789, x, sizeof x );
    ASSERT( streq( x, "-123456789" ) );
}


int
main( void )
{

    printf( "Running tests...\n" );

    size_t const num_tests = 1000;

    for ( size_t i = 0; i < num_tests; i++ ) {
        int const x = rand();
        int const y = rand();
        int const z = rand();
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
    printf( "  int assertions passed\n" );

    for ( size_t i = 0; i < num_tests; i++ ) {
        uchar const x = rand() % uchar__max_bound();
        uchar const y = rand() % uchar__max_bound();
        uchar const z = rand() % uchar__max_bound();
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
    printf( "  uchar assertions passed\n" );

    ASSERT( int__clamp( 5, 0, 10 ) == 5,
            int__clamp( 0, 0, 10 ) == 0,
            int__clamp( -1, 0, 10 ) == 0,
            int__clamp( -1, -1, 10 ) == -1,
            int__clamp( 9, 0, 10 ) == 9,
            int__clamp( 10, 0, 10 ) == 10,
            int__clamp( 11, 0, 10 ) == 10,
            int__clamp( INT_MIN, 0, 10 ) == 0,
            int__clamp( INT_MAX, 0, 10 ) == 10,
            uchar__clamp( 5, 0, 10 ) == 5,
            uchar__clamp( 0, 0, 10 ) == 0,
            uchar__clamp( 1, 0, 10 ) == 1,
            uchar__clamp( 9, 0, 10 ) == 9,
            uchar__clamp( 10, 0, 10 ) == 10,
            uchar__clamp( 11, 0, 10 ) == 10,
            uchar__clamp( UCHAR_MAX, 0, 10 ) == 10 );
    printf( "  clamp assertions passed\n" );

    test_update_average();
    printf( "  update_average assertions passed\n" );

    test_to_str();
    printf( "  to_str assertions passed\n" );

}



