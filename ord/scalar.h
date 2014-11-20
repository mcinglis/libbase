
#ifndef LIBBASE_ORD_SCALAR_H
#define LIBBASE_ORD_SCALAR_H


#include <libtypes/types.h>     // bool, ord
#include <libmacro/require.h>  // REQUIRE


#define DERIVING_ORD_SCALAR( T, TT, TF ) \
                                                                              \
                                                                              \
    ord                                                                       \
    TF##__compare( T const x,                                                 \
                   T const y )                                                \
    {                                                                         \
        return ( x > y ) - ( x < y );                                         \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__less_than( T const x,                                               \
                     T const y )                                              \
    {                                                                         \
        return x < y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                     \
    TF##__less_than_or_eq( T const x,                                         \
                           T const y )                                        \
    {                                                                         \
        return x <= y;                                                        \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__greater_than_or_eq( T const x,                                      \
                              T const y )                                     \
    {                                                                         \
        return x >= y;                                                        \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__greater_than( T const x,                                            \
                        T const y )                                           \
    {                                                                         \
        return x > y;                                                         \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__min2( T const x,                                                    \
                T const y )                                                   \
    {                                                                         \
        return ( x < y ) ? x : y;                                             \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__max2( T const x,                                                    \
                T const y )                                                   \
    {                                                                         \
        return ( x > y ) ? x : y;                                             \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__min_n( size_t const n,                                              \
                 T const * const xs )                                         \
    {                                                                         \
        REQUIRE( n > 0, xs != NULL );                                         \
                                                                              \
        T min = xs[ 0 ];                                                      \
        for ( size_t i = 1; i < n; i++ ) {                                    \
            if ( xs[ i ] < min ) {                                            \
                min = xs[ i ];                                                \
            }                                                                 \
        }                                                                     \
        return min;                                                           \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__max_n( size_t const n,                                              \
                 T const * const xs )                                         \
    {                                                                         \
        REQUIRE( n > 0, xs != NULL );                                         \
                                                                              \
        T max = xs[ 0 ];                                                      \
        for ( size_t i = 1; i < n; i++ ) {                                    \
            if ( xs[ i ] > max ) {                                            \
                max = xs[ i ];                                                \
            }                                                                 \
        }                                                                     \
        return max;                                                           \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__clamp( int const lower,                                             \
                 int const upper,                                             \
                 int const x )                                                \
    {                                                                         \
        return ( lower >= x ) ? lower                                         \
             : ( upper <= x ) ? upper                                         \
                              : x;                                            \
    }


#endif

