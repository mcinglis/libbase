
#ifndef LIBBASE_SHOWSTR_INTEGRAL_SIGNED_H
#define LIBBASE_SHOWSTR_INTEGRAL_SIGNED_H


#include "../types.h"


#define DERIVING_SHOWSTR_INTEGRAL_SIGNED( T, TF ) \


static
size_t
count_digits( T x,
              uint const base )
{
    REQUIRE( 2 <= base && base <= 16 );

    assert( TF##__can_div( x, base ) );
    if ( x == 0 ) {
        return 1;
    } else {
        size_t c = 0;
        while ( x != 0 ) {
            x /= base;
            c++;
        }
        return c;
    }
}


size_t
TF##__str_length( T const x,
                  uint const base )
{
    REQUIRE( 2 <= base && base <= 16 );

    return count_digits( x, base ) + ( x < 0 );
}


void
TF##__into_str( T x,
                char * const str,
                size_t const size,
                uint const base )
{
    if ( str == NULL || size == 0 ) {
        return;
    } else if ( size == 1 ) {
        str[ 0 ] = '\0';
        return;
    } else if ( x == 0 ) {
        str[ 0 ] = '0';
        str[ 1 ] = '\0';
        return;
    }

    char buf[ 64 ] = { 0 };
    bool negative = ( x < 0 );
    size_t i = TF##__str_length( x, base ) + 1;
    assert( i < sizeof buf );
    for ( ; ( i > 0 ) && ( x != 0 ); i--, x /= base ) {
        buf[ i - 1 ] = "0123456789abcdef"[ x % base ];
    }
    if ( negative ) {
        assert( i == 2 );
        buf[ 0 ] = '-';
    }

    mem_copy( buf, size, str );
}


#endif

