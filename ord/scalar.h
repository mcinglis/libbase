
#ifndef LIBBASE_ORD_SCALAR_H
#define LIBBASE_ORD_SCALAR_H


#define DERIVING_ORD_SCALAR( T, TF ) \
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
    bool                                                                      \
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
    TF##__min( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        return ( x < y ) ? x : y;                                             \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__max( T const x,                                                     \
               T const y )                                                    \
    {                                                                         \
        return ( x > y ) ? x : y;                                             \
    }


#endif

