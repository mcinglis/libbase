
#ifndef LIBBASE_INT_H
#define LIBBASE_INT_H


#include <libtypes/types.h>     // bool, ord


int int__id( int x );   // Returns `x`.


/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

int int__min_bound( void );     // Returns `INT_MIN`.
int int__max_bound( void );     // Returns `INT_MAX`.


/////////////////////////////
/// EQ TYPECLASS
/////////////////////////////

bool int__equal( int x, int y );        // Returns `x == y`.
bool int__not_equal( int x, int y );    // Returns `x != y`.


/////////////////////////////
/// ORD TYPECLASS
/////////////////////////////

ord int__compare( int x, int y );   // Returns: `LT` if `x < y`,
                                    //          `EQ` if `x == y`, or
                                    //          `GT` if `x > y`.

bool int__less_than( int x, int y );            // Returns `x < y`.
bool int__less_than_or_eq( int x, int y);       // Returns `x <= y`.
bool int__greater_than_or_eq( int x, int y );   // Returns `x >= y`.
bool int__greater_than( int x, int y );         // Returns `x > y`.

int int__min2( int x, int y ); // Returns `x` if `x < y`, or `y` otherwise.
int int__max2( int x, int y ); // Returns `x` if `x > y`, or `y` otherwise.

int int__min_n( size_t n, int const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

int int__max_n( size_t n, int const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

#define int__min( ... ) \
    int__min_n( PP_COUNT( __VA_ARGS__ ), ( int[] ){ __VA_ARGS__ } )

#define int__max( ... ) \
    int__max_n( PP_COUNT( __VA_ARGS__ ), ( int[] ){ __VA_ARGS__ } )

int int__clamp( int lower, int upper, int x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`



/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

int int__succ( int x );   // Returns `x + 1`.
                          // @requires x != int__max_bound()

int int__succ_b( int x ); // Returns `x + 1`,
                          // or `int__max_bound()` if `x == int__max_bound()`.

int int__pred( int x );   // Returns `x - 1`.
                          // @requires x != int__min_bound()

int int__pred_b( int x ); // Returns `x - 1`,
                          // or `int__min_bound()` if `x == int__min_bound()`.


/////////////////////////////
/// NUM TYPECLASS
/////////////////////////////

bool int__is_signed( void );
// Returns `true`, because `int` values can be negative.

bool int__can_add( int x, int y );
// Returns the boolean that the behavior of `x + y` is well-defined.
// Equivalent to:
//
//        implies( y > 0, x <= ( int__max_bound - y ) )
//     && implies( y < 0, x >= ( int__min_bound - y ) )

bool int__can_sub( int x, int y );
// Returns the boolean that the behavior of `x - y` is well-defined.
// Equivalent to:
//
//        implies( y > 0, x >= ( int__min_bound - y ) )
//     && implies( y < 0, x <= ( int__max_bound - y ) )

bool int__can_mul( int x, int y );
// Returns the boolean that the behavior of `x * y` is well-defined.
// Equivalent to:
//
//     ( x > 0 ) ? ( y > 0 ) ? ( x <= ( int__max_bound / y ) )
//                           : ( y >= ( int__min_bound / x ) )
//               : ( y > 0 ) ? ( x >= ( int__min_bound / y ) )
//                           : implies( x != 0, y >= ( int__max_bound / x ) )

bool int__can_div( int x, int y );
// Returns the boolean that the behavior of `x / y` is well-defined.
// Equivalent to:
//
//     ( y != 0 ) && !( ( x == int__min_bound ) && ( y == -1 ) )

int int__add( int x, int y );   // Returns `x + y`.
                                // @requires int__can_add( x, y )

int int__sub( int x, int y );   // Returns `x - y`.
                                // @requires int__can_sub( x, y )

int int__mul( int x, int y );   // Returns `x * y`.
                                // @requires int__can_mul( x, y )

int int__div( int x, int y );   // Returns `x / y`.
                                // @requires int__can_div( x, y )

int int__mod( int x, int y );   // Returns `x % y`.
                                // @requires int__can_div( x, y )

int int__negate( int x );       // Returns `-x`.
                                // @requires x != int__min_bound

int int__abs( int x );          // Returns `( x < 0 ) ? -x : x`.
                                // @requires x != int__min_bound

bool int__same_sign( int x, int y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool int__is_negative( int x );     // Returns `x < 0`.
bool int__is_nonpositive( int x );  // Returns `x <= 0`.
bool int__is_zero( int x );         // Returns `x == 0`.
bool int__is_nonnegative( int x );  // Returns `x >= 0`.
bool int__is_positive( int x );     // Returns `x > 0`.
ord  int__compare_0( int x );       // Returns `int__compare( x, 0 )`.

bool int__is_even( int x );     // Returns `x % 2 == 0`.
bool int__is_odd( int x );      // Returns `x % 2 == 1`.

int int__add_2( int x );    // Returns `int__add( x, 2 )`.
int int__sub_2( int x );    // Returns `int__sub( x, 2 )`.
int int__mul_2( int x );    // Returns `int__mul( x, 2 )`.
int int__div_2( int x );    // Returns `int__div( x, 2 )`.
int int__mod_2( int x );    // Returns `int__mod( x, 2 )`.


#endif

