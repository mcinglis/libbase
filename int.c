
#include "int.h"

#include "types.h"      // bool, ord, lssize_t, uchar
#include "logic.h"      // implies
#include "require.h"    // REQUIRE
#include "pop-count.h"  // pop_count

#include "eq/scalar.h"      // EQ_SCALAR_SOURCE
#include "ord/scalar.h"     // ORD_SCALAR_SOURCE
#include "enum/scalar.h"    // ENUM_SCALAR_SOURCE



int int__id( int const x ) { return x; }


// Bounded typeclass:
int int__min_bound( void ) { return INT_MIN; }
int int__max_bound( void ) { return INT_MAX; }


PP_CALL( ( int, int ), DERIVING_EQ_SCALAR,              // Eq typeclass
                       DERIVING_ORD_SCALAR,             // Ord typeclass
                       DERIVING_ENUM_SCALAR,            // Enum typeclass
                       DERIVING_NUM_INTEGRAL_SIGNED     // Num typeclass
       );




/////////////////////////////
/// SHOWSTR TYPECLASS
/////////////////////////////


size_t
int__str_length( int const x )
{
    return int__count_digits( x ) + ( ( x < 0 ) ? 1 : 0 );
}


void
int__into_str( int const x,
               char * const str,
               size_t const size )
{
    if ( str == NULL || size == 0 ) {
        return;
    } else if ( size == 1 ) {
        str[ 0 ] = '\0';
        return;
    }

    size_t i = 0;
    if ( x < 0 ) {
        str[ 0 ] = '-';
        i++;
    }
    for ( ; ( i < size - 1 ) && ( x != 0 ); i++, x /= 10 ) {
        str[ i ] = '0' + ( x % 10 );
    }
    str[ i ] = '\0';
}


char *
int__to_str( int const x )
{
    size_t const size = int__str_length( x ) + 1;
    char * const s = malloc( size );
    int__into_str( x, s, size );
    return s;
}


void
int__print( int const x,
            FILE * const file )
{
    // TODO: abstract the buffer size.
    // TODO: any need to check str length of x here?

    char str[ 64 ];
    int__into_str( x, str, sizeof str );
    fputs( str, file );
}



/////////////////////////////
/// BITS TYPECLASS
/////////////////////////////


int const int__zero_bits = 0;
int const int__one_bits = ~int__zero_bits;


size_t
int__precision( void )
{
    size_t p = 0;
    for ( uint x = UINT_MAX; x != 0; x &= x - 1 ) {
        p++;
    }
    // one bit less than the precision of an unsigned int:
    return p - 1;
}


size_t
int__width( void )
{
    return int__precision() + 1;
}


size_t
int__padding( void )
{
    return ( sizeof ( int ) * 8 ) - int__width();
}


bool
int__can_lshift( int const x,
                 size_t const n )
{
    return ( x >= 0 )
        && ( n < int__width() )
        && ( x <= ( int__max_bound() >> n ) );
}


bool
int__can_rshift( int const x,
                 size_t const n )
{
    return ( x >= 0 )
        && ( n < int__width() );
}


int
int__lshift( int const x,
             size_t const n )
{
    REQUIRE( int__can_lshift( x, n ) );

    return x << n;
}


int
int__rshift( int const x,
             size_t const n )
{
    REQUIRE( n < int__width() );

    return x >> n;
}


int
int__shift( int const x,
            lssize_t const n )
{
    return ( n > 0 ) ? int__lshift( x, n ) : int__rshift( x, -n );
}


int
int__lrotate( int const x,
              size_t const n )
{
    REQUIRE( int__can_lshift( x, n ),
             int__can_rshift( x, int__precision() - n ) );

    return ( n == 0 ) ? x
                      : ( ( x << n ) | ( x >> ( int__precision() - n ) ) );
}


int
int__rrotate( int const x,
              size_t const n )
{
    REQUIRE( int__can_rshift( x, n ),
             int__can_lshift( x, int__precision() - n ) );

    return ( n == 0 ) ? x
                      : ( ( x >> n ) | ( x << ( int__precision() - n ) ) );
}


int
int__rotate( int const x,
             lssize_t const n )
{
    return ( n > 0 ) ? int__lrotate( x, n ) : int__rrotate( x, -n );
}


int int__bitwise_and( int const x, int const y ) { return x & y; }
int int__bitwise_or ( int const x, int const y ) { return x | y; }
int int__bitwise_xor( int const x, int const y ) { return x ^ y; }
int int__bitwise_not( int const x )              { return ~x; }


int
int__bit( size_t const n )
{
    REQUIRE( n < int__precision() );

    return 1 << n;
}


bool
int__get_bit( int const x,
              size_t const n )
{
    REQUIRE( n < int__precision() );

    return ( x & int__bit( n ) ) != 0;
}


int
int__set_bit( int const x,
              size_t const n )
{
    REQUIRE( n < int__precision() );

    return x | int__bit( n );
}


int
int__clear_bit( int const x,
                size_t const n )
{
    REQUIRE( n < int__precision() );

    return x & ~int__bit( n );
}


int
int__toggle_bit( int const x,
                 size_t const n )
{
    REQUIRE( n < int__precision() );

    return int__get_bit( x, n ) ? int__clear_bit( x, n )
                                : int__set_bit( x, n );
}


int
int__assign_bit( int const x,
                 size_t const n,
                 bool const b )
{
    REQUIRE( n < int__precision() );

    return b ? int__set_bit( x, n )
             : int__clear_bit( x, n );
}


int
int__clear_lowest_set_bit( int const x )
{
    if ( x == 0 ) {
        return x;
    } else {
        uint ux;
        mem_copy( &x, sizeof x, &ux );
        ux &= ux - 1;
        int r;
        mem_copy( &ux, sizeof ux, &r );
        return r;
    }
}


int
int__reverse_bits( int const x )
{
    uchar bits[ sizeof ( int ) ];
    memcpy( bits, &x, sizeof ( int ) );
    uchar revbits[ sizeof ( int ) ];
    for ( size_t i = 0; i < sizeof ( int ); i++ ) {
        revbits[ sizeof ( int ) - 1 - i ] =
            ( bits[ i ] * 0x0202020202ULL & 0x010884422010ULL ) % 1023;
        // from: <https://graphics.stanford.edu/~seander/
        //        bithacks.html#ReverseByteWith64BitsDiv>
    }
    int reverse;
    memcpy( &reverse, revbits, sizeof ( int ) );
    return reverse;
}


size_t
int__count_set_bits( int const x )
{
    uint ux;
    memcpy( &ux, &x, sizeof x );
    size_t count = 0;
    while ( ux != 0 ) {
        count++;
        ux &= ux - 1;
    }
    return count;
}


size_t
int__count_trailing_zeroes( int const x )
{
    if ( x == 0 ) {
        return int__width();
    } else {
        uint ux;
        memcpy( &ux, &x, sizeof x );
        size_t count = 0;
        // set ux's trailing 0s to 1s and zero rest:
        ux = ( ux ^ ( ux - 1 ) ) >> 1;
        while ( ux != 0 ) {
            count++;
            ux >>= 1;
        }
        return count;
    }
}


int int__lshift_1 ( int const x ) { return int__lshift( x, 1 ); }
int int__rshift_1 ( int const x ) { return int__rshift( x, 1 ); }
int int__lrotate_1( int const x ) { return int__lrotate( x, 1 ); }
int int__rrotate_1( int const x ) { return int__rrotate( x, 1 ); }


