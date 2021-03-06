
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
#include "../double.h"


static
bool
streq( char const * const xs,
       char const * const ys )
{
    return strcmp( xs, ys ) == 0;
}


static
void
test_from_str( void )
{
    ASSERT( double__from_str( "0" ) == 0,
            double__from_str( "3.14" ) == 3.14,
            double__from_str( "-98.123" ) == -98.123 );
}


static
void
test_to_strm( void )
{
    {
        char buf[ 32 ];
        int__into_strm( 0, buf, sizeof buf );
        ASSERT( streq( buf, "0" ) );
        int__into_strm( 5, buf, sizeof buf );
        ASSERT( streq( buf, "5" ) );
        int__into_strm( 10, buf, sizeof buf );
        ASSERT( streq( buf, "10" ) );
        int__into_strm( 20, buf, sizeof buf );
        ASSERT( streq( buf, "20" ) );
        int__into_strm( 100, buf, sizeof buf );
        ASSERT( streq( buf, "100" ) );
        int__into_strm( 123456789, buf, sizeof buf );
        ASSERT( streq( buf, "123456789" ) );
        int__into_strm( -5, buf, sizeof buf );
        ASSERT( streq( buf, "-5" ) );
        int__into_strm( -10, buf, sizeof buf );
        ASSERT( streq( buf, "-10" ) );
        int__into_strm( -20, buf, sizeof buf );
        ASSERT( streq( buf, "-20" ) );
        int__into_strm( -100, buf, sizeof buf );
        ASSERT( streq( buf, "-100" ) );
        int__into_strm( -123456789, buf, sizeof buf );
        ASSERT( streq( buf, "-123456789" ) );
    }
    {
        char buf[ 32 ];
        ulong__into_strm( 0, buf, sizeof buf );
        ASSERT( streq( buf, "0" ) );
        ulong__into_strm( 5, buf, sizeof buf );
        ASSERT( streq( buf, "5" ) );
        ulong__into_strm( 10, buf, sizeof buf );
        ASSERT( streq( buf, "10" ) );
        ulong__into_strm( 20, buf, sizeof buf );
        ASSERT( streq( buf, "20" ) );
        ulong__into_strm( 100, buf, sizeof buf );
        ASSERT( streq( buf, "100" ) );
        ulong__into_strm( 123456789, buf, sizeof buf );
        ASSERT( streq( buf, "123456789" ) );
    }
    {
        char buf[ 4 ];
        int__into_strm( 12345678, buf, sizeof buf );
        ASSERT( streq( buf, "123" ) );
        int__into_strm( -12345678, buf, sizeof buf );
        ASSERT( streq( buf, "-12" ) );
        ulong__into_strm( 12345678, buf, sizeof buf );
        ASSERT( streq( buf, "123" ) );
    }
    {
        char * const str = int__to_strm( 0 );
        ASSERT( errno == 0, streq( str, "0" ) );
        free( str );
    }
    {
        char * const str = int__to_strm( 9999 );
        ASSERT( errno == 0, streq( str, "9999" ) );
        free( str );
    }
    {
        char * const str = int__to_strm( -123 );
        ASSERT( errno == 0, streq( str, "-123" ) );
        free( str );
    }
    {
        char * const str = ulong__to_strm( 0 );
        ASSERT( errno == 0, streq( str, "0" ) );
        free( str );
    }
    {
        char * const str = ulong__to_strm( 9999 );
        ASSERT( errno == 0, streq( str, "9999" ) );
        free( str );
    }
    {
        double const x = 3.14;
        char * const str = double__to_strm( x );
        ASSERT( errno == 0, streq( str, "3.140000" ) );
        free( str );
    }
    {
        double const x = 6;
        char * const str = double__to_strm( x );
        ASSERT( errno == 0, streq( str, "6.000000" ) );
        free( str );
    }
}


static
void
test_bounded( void )
{
    ASSERT( int__from_float( 3.5 )    == 4,
            int__from_float( 0.1 )    == 0,
            int__from_float( 0 )      == 0,
            int__from_float( -0.1 )   == 0,
            int__from_float( -0.5 )   == -1,
            int__from_float( 1 )      == 1,
            int__from_float( -8 )     == -8,
            int__from_float( 1.9999 ) == 2 );
}


static
void
test_null( void )
{
    ASSERT( uchar__null() == '\0',
            !uchar__is_null( 'a' ),
            !uchar__is_null( 'x' ),
            uchar__is_null( '\0' ),
            double__null() == 0,
            !double__is_null( 0.001 ),
            !double__is_null( -0.001 ),
            double__is_null( 0 ) );
}


static
void
test_float( void )
{
    double const epsilon = 0.000001;
    size_t n = 0;
    double avg = double__update_average( 0, n++, 5 );
    ASSERT( double__equal_e( avg, 5, epsilon ) );
    avg = double__update_average( avg, n++, 10 );
    ASSERT( double__equal_e( avg, 7.5, epsilon ) );
    avg = double__update_average( avg, n++, 15 );
    ASSERT( double__equal_e( avg, 10, epsilon ) );
    avg = double__update_average( avg, n++, -10 );
    ASSERT( double__equal_e( avg, 5, epsilon ) );
    avg = double__update_average( avg, n++, -30 );
    ASSERT( double__equal_e( avg, -2, epsilon ) );

    ASSERT( double__equal_e( double__sum( 1, 2, 3 ), 6, epsilon ),
            double__equal_e( double__sum( 8 ), 8, epsilon ),
            double__equal_e( double__average( 1, 2, 3 ), 2, epsilon ),
            double__equal_e( double__average( 0.5, 1 ), 0.75, epsilon ),
            double__equal_e( double__average( 3 ), 3, epsilon ),
            double__equal_e( double__average( -5, 0, 0, 5 ), 0, epsilon ) );

    errno = 0;
    ASSERT( double__to_intmax( 0 ) == 0 && errno == 0,
            double__to_uintmax( 0 ) == 0 && errno == 0,
            double__to_intmax( 123.4567 ) == 123 && errno == 0,
            double__to_uintmax( 123.4567 ) == 123 && errno == 0,
            double__to_intmax( 0.999999 ) == 1 && errno == 0,
            double__to_intmax( -0.999999 ) == -1 && errno == 0,
            double__to_intmax( -0.5 ) == -1 && errno == 0,
            double__to_intmax( 0.5 ) == 1 && errno == 0,
            double__to_intmax( 12345678901234567890123.123 ) == INTMAX_MAX
            && errno == EOVERFLOW );
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

    test_from_str();
    printf( "  from_str tests passed\n" );

    test_to_strm();     puts( "  TO_STRM typeclass tests passed" );
    test_bounded();     puts( "  BOUNDED typeclass tests passed" );
    test_null();        puts( "  NULL typeclass tests passed" );
    test_float();       puts( "  FLOAT typeclass tests passed" );

    puts( "All tests passed!" );
}

