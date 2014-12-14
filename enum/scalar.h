
#ifndef LIBBASE_ENUM_SCALAR_H
#define LIBBASE_ENUM_SCALAR_H


#include <libmacro/require.h>  // REQUIRE


// @public
#define DERIVING_ENUM_SCALAR( T, TT, TF ) \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__succ( T const x )                                                   \
    {                                                                         \
        REQUIRE( x != TF##__max_bound() );                                    \
        return x + 1;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__succ_b( T const x )                                                 \
    {                                                                         \
        return ( x == TF##__max_bound() ) ? x : ( x + 1 );                    \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__pred( T const x )                                                   \
    {                                                                         \
        REQUIRE( x != TF##__min_bound() );                                    \
        return x - 1;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__pred_b( T const x )                                                 \
    {                                                                         \
        return ( x == TF##__min_bound() ) ? x : ( x - 1 );                    \
    }


#endif

