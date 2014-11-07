
#ifndef LIBBASE_NUM_INTEGRAL_SIGNED_H
#define LIBBASE_NUM_INTEGRAL_SIGNED_H


#include "../types.h"


#define DERIVING_NUM_INTEGRAL_SIGNED( T, TF ) \
                                                                              \
                                                                              \
    bool is_signed( void ) { return true; }                                   \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__can_add( T const x,                                                 \
                   T const y )                                                \
    {                                                                         \
        return implies( y > 0, x <= ( TF##__max_bound() - y ) )               \
            && implies( y < 0, x >= ( TF##__min_bound() - y ) );              \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__can_sub( T const x,                                                 \
                   T const y )                                                \
    {                                                                         \
        return implies( y > 0, x >= ( TF##__min_bound() + y ) )               \
            && implies( y < 0, x <= ( TF##__max_bound() + y ) );              \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__can_mul( T const x,                                                 \
                   T const y )                                                \
    {                                                                         \
        return ( x > 0 ) ? ( ( y > 0 )                                        \
                               ? ( x <= ( TF##__max_bound() / y ) )           \
                               : ( y >= ( TF##__min_bound() / x ) ) )         \
                         : ( ( y > 0 )                                        \
                               ? ( x >= ( TF##__min_bound() / y ) )           \
                               : implies( x != 0,                             \
                                          y >= ( TF##__max_bound() / x ) ) ); \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__can_div( T const x,                                                 \
                   T const y )                                                \
    {                                                                         \
        return ( y != 0 )                                                     \
            && !( ( x == TF##__min_bound() ) && ( y == -1 ) );                \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__add( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        REQUIRE( TF##__can_add( x, y ) );                                     \
                                                                              \
        return x + y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__sub( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        REQUIRE( TF##__can_sub( x, y ) );                                     \
                                                                              \
        return x - y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__mul( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        REQUIRE( TF##__can_mul( x, y ) );                                     \
                                                                              \
        return x * y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__div( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        REQUIRE( TF##__can_div( x, y ) );                                     \
                                                                              \
        return x / y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__mod( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        REQUIRE( TF##__can_div( x, y ) );                                     \
                                                                              \
        return x % y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__negate( T const x )                                                 \
    {                                                                         \
        REQUIRE( x != TF##__min_bound() );                                    \
                                                                              \
        return -x;                                                            \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__abs( T const x )                                                    \
    {                                                                         \
        REQUIRE( x != TF##__min_bound() );                                    \
                                                                              \
        return ( x < 0 ) ? -x : x;                                            \
    }                                                                         \
                                                                              \
                                                                              \
    ord  TF##__compare_0     ( T const x ) { return TF##__compare( x, 0 ); }  \
    bool TF##__is_negative   ( T const x ) { return x < 0; }                  \
    bool TF##__is_nonpositive( T const x ) { return x <= 0; }                 \
    bool TF##__is_zero       ( T const x ) { return x == 0; }                 \
    bool TF##__is_nonnegative( T const x ) { return x >= 0; }                 \
    bool TF##__is_positive   ( T const x ) { return x > 0; }                  \
                                                                              \
                                                                              \
    T TF##__add_2( T const x ) { return TF##__add( x, 2 ); }                  \
    T TF##__sub_2( T const x ) { return TF##__sub( x, 2 ); }                  \
    T TF##__mul_2( T const x ) { return TF##__mul( x, 2 ); }                  \
    T TF##__div_2( T const x ) { return TF##__div( x, 2 ); }                  \
    T TF##__mod_2( T const x ) { return TF##__mod( x, 2 ); }


#endif

