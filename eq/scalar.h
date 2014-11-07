
#ifndef LIBBASE_EQ_SCALAR_H
#define LIBBASE_EQ_SCALAR_H


#define DERIVING_EQ_SCALAR( T, TF ) \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__equal( T const x,                                                   \
                 T const y )                                                  \
    {                                                                         \
        return x == y;                                                        \
    }                                                                         \
                                                                              \
                                                                              \
    bool                                                                      \
    TF##__not_equal( T const x,                                               \
                     T const y )                                              \
    {                                                                         \
        return x != y;                                                        \
    }


#endif

