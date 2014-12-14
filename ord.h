
#ifndef LIBBASE_BOOL_H
#define LIBBASE_BOOL_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


ord ord__id( ord x );    // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

ord ord__min_bound( void );   // Returns `LT`.
ord ord__max_bound( void );   // Returns `GT`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool ord__equal( ord x, ord y );         // Returns `x == y`.
bool ord__not_equal( ord x, ord y );     // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord ord__compare( ord x, ord y );   // Returns: `LT` if `x < y`,
                                    //          `EQ` if `x == y`, or
                                    //          `GT` if `x > y`.

bool ord__less_than( ord x, ord y );            // Returns `x < y`.
bool ord__less_than_or_eq( ord x, ord y );      // Returns `x <= y`.
bool ord__greater_than_or_eq( ord x, ord y );   // Returns `x >= y`.
bool ord__greater_than( ord x, ord y );         // Returns `x > y`.

ord ord__min2( ord x, ord y );  // Returns the minimum of `x` and `y`.
ord ord__max2( ord x, ord y );  // Returns the maximum of `x` and `y`.

ord ord__min_n( size_t n, ord const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

ord ord__max_n( size_t n, ord const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

#define ord__min( ... ) \
    ord__min_n( PP_COUNT( __VA_ARGS__ ), ( ord[] ){ __VA_ARGS__ } )

#define ord__max( ... ) \
    ord__max_n( PP_COUNT( __VA_ARGS__ ), ( ord[] ){ __VA_ARGS__ } )

ord ord__clamp( ord lower, ord upper, ord x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

ord ord__succ( ord x );         // Returns `x + 1`.
                                // @requires x != GT

ord ord__succ_b( ord x );       // Returns `x + 1`, or `GT` if `x == GT`.

ord ord__pred( ord x );         // Returns `x - 1`.
                                // @requires x != LT

ord ord__pred_b( ord x );       // Returns `x - 1`, or `LT` if `x == LT`.


#endif

