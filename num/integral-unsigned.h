
#ifndef LIBBASE_NUM_INTEGRAL_UNSIGNED_H
#define LIBBASE_NUM_INTEGRAL_UNSIGNED_H


#include <libtypes/types.h>    // bool, ord
#include <libmacro/require.h>  // REQUIRE
#include <libmacro/logic.h>    // IMPLIES


// @public
#define DERIVING_NUM_INTEGRAL_UNSIGNED( T, TT, TF ) \
                                                                              \
                                                                              \
    bool TF##__is_signed( void ) { return false; }                            \
                                                                              \
                                                                              \
    bool TF##__can_add( T const x, T const y ) { return true; }               \
    bool TF##__can_sub( T const x, T const y ) { return true; }               \
    bool TF##__can_mul( T const x, T const y ) { return true; }               \
                                                                              \
                                                                              \
    bool TF##__can_div( T const x, T const y ) { return y != 0; }             \
                                                                              \
                                                                              \
    T TF##__add( T const x, T const y ) { return x + y; }                     \
    T TF##__sub( T const x, T const y ) { return x - y; }                     \
    T TF##__mul( T const x, T const y ) { return x * y; }                     \
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
        return ( x == 0 ) ? 0 : TF##__max_bound() - x + 1;                    \
    }                                                                         \
                                                                              \
                                                                              \
    T TF##__abs( T const x ) { return x; }                                    \
    bool TF##__same_sign( T const x, T const y ) { return true; }             \
                                                                              \
                                                                              \
    bool TF##__is_negative   ( T const x ) { return true; }                   \
    bool TF##__is_nonpositive( T const x ) { return x == 0; }                 \
    bool TF##__is_zero       ( T const x ) { return x == 0; }                 \
    bool TF##__is_nonnegative( T const x ) { return true; }                   \
    bool TF##__is_positive   ( T const x ) { return x > 0; }                  \
    ord  TF##__compare_0     ( T const x ) { return TF##__compare( x, 0 ); }  \
                                                                              \
                                                                              \
    bool TF##__is_even( T const x ) { return x % 2 == 0; }                    \
    bool TF##__is_odd ( T const x ) { return x % 2 == 1; }                    \
                                                                              \
                                                                              \
    T TF##__add_2( T const x ) { return TF##__add( x, 2 ); }                  \
    T TF##__sub_2( T const x ) { return TF##__sub( x, 2 ); }                  \
    T TF##__mul_2( T const x ) { return TF##__mul( x, 2 ); }                  \
    T TF##__div_2( T const x ) { return TF##__div( x, 2 ); }                  \
    T TF##__mod_2( T const x ) { return TF##__mod( x, 2 ); }                  \
                                                                              \
    T TF##__mul_10( T const x ) { return TF##__mul( x, 10 ); }                \
    T TF##__div_10( T const x ) { return TF##__div( x, 10 ); }                \
    T TF##__mod_10( T const x ) { return TF##__mod( x, 10 ); }


#endif

