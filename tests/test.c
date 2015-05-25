
#include <errno.h>
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

    ulong__into_strm( 0, x, sizeof x );
    ASSERT( streq( x, "0" ) );
    ulong__into_strm( 5, x, sizeof x );
    ASSERT( streq( x, "5" ) );
    ulong__into_strm( 10, x, sizeof x );
    ASSERT( streq( x, "10" ) );
    ulong__into_strm( 20, x, sizeof x );
    ASSERT( streq( x, "20" ) );
    ulong__into_strm( 100, x, sizeof x );
    ASSERT( streq( x, "100" ) );
    ulong__into_strm( 123456789, x, sizeof x );
    ASSERT( streq( x, "123456789" ) );

    char y[ 4 ];

    int__into_strm( 12345678, y, sizeof y );
    ASSERT( streq( y, "123" ) );
    int__into_strm( -12345678, y, sizeof y );
    ASSERT( streq( y, "-12" ) );

    ulong__into_strm( 12345678, y, sizeof y );
    ASSERT( streq( y, "123" ) );

    errno = 0;
    char * const a = int__to_strm( 0 );
    ASSERT( errno == 0, streq( a, "0" ) );
    char * const b = int__to_strm( 9999 );
    ASSERT( errno == 0, streq( b, "9999" ) );
    char * const c = int__to_strm( -123 );
    ASSERT( errno == 0, streq( c, "-123" ) );
    char * const d = ulong__to_strm( 0 );
    ASSERT( errno == 0, streq( d, "0" ) );
    char * const e = ulong__to_strm( 9999 );
    ASSERT( errno == 0, streq( e, "9999" ) );

    free( a ); free( b ); free( c ); free( d ); free( e );
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

    test_to_str();
    printf( "  to_str assertions passed\n" );

}



