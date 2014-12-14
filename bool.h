
#ifndef LIBBASE_BOOL_H
#define LIBBASE_BOOL_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


bool bool__id( bool x );    // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

bool bool__min_bound( void );   // Returns `false`.
bool bool__max_bound( void );   // Returns `true`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool bool__equal( bool x, bool y );         // Returns `x == y`.
bool bool__not_equal( bool x, bool y );     // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord bool__compare( bool x, bool y );   // Returns: `LT` if `x < y`,
                                       //          `EQ` if `x == y`, or
                                       //          `GT` if `x > y`.

bool bool__less_than( bool x, bool y );            // Returns `x < y`.
bool bool__less_than_or_eq( bool x, bool y );      // Returns `x <= y`.
bool bool__greater_than_or_eq( bool x, bool y );   // Returns `x >= y`.
bool bool__greater_than( bool x, bool y );         // Returns `x > y`.

bool bool__min2( bool x, bool y );   // Returns `x && y`.
bool bool__max2( bool x, bool y );   // Returns `x || y`.

bool bool__min_n( size_t n, bool const * xs );
// Returns `false` if any of the first `n` elements in the array `xs` are
// `false`. Returns `true` otherwise. Logically equivalent to `ALL()`.
// @requires n > 0, xs != NULL

bool bool__max_n( size_t n, bool const * xs );
// Returns `true` if any of the first `n` elements in the array `xs` are
// `true`. Returns `false` otherwise. Logically equivalent to `ANY()`.
// @requires n > 0, xs != NULL

#define bool__min( ... ) \
    bool__min_n( PP_COUNT( __VA_ARGS__ ), ( bool[] ){ __VA_ARGS__ } )

#define bool__max( ... ) \
    bool__max_n( PP_COUNT( __VA_ARGS__ ), ( bool[] ){ __VA_ARGS__ } )

bool bool__clamp( bool lower, bool upper, bool x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

bool bool__succ( bool x );  // Returns `true`.
                            // @requires x != true

bool bool__succ_b( bool x );    // Returns `true`.

bool bool__pred( bool x );      // Returns `false`.
                                // @requires x != false

bool bool__pred_b( bool x );    // Returns `false`.


#endif

