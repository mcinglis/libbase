
#ifndef LIBBASE_INT_H
#define LIBBASE_INT_H


#include <libpp/call.h>

#include "types.h"



int int__id( int x );   // Returns `x`.



/////////////////////////////
/// BOUNDED TYPECLASS
/////////////////////////////

extern int const int__min_bound; // Equals `INT_MIN`.
extern int const int__max_bound; // Equals `INT_MAX`.



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

int int__min( int x, int y ); // Returns `x` if `x < y`, or `y` otherwise.
int int__max( int x, int y ); // Returns `x` if `x > y`, or `y` otherwise.



/////////////////////////////
/// ENUM TYPECLASS
/////////////////////////////

int int__succ( int x );     // Returns `x + 1`.
                            // @requires x != int__max_bound

int int__succ_b( int x );   // Returns `x + 1`,
                            // or `int__max_bound` if `x == int__max_bound`.

int int__pred( int x );     // Returns `x - 1`.
                            // @requires x != int__min_bound

int int__pred_b( int x );   // Returns `x - 1`,
                            // or `int__min_bound` if `x == int__min_bound`.



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


bool int__is_negative( int x );     // Returns `x < 0`.
bool int__is_nonpositive( int x );  // Returns `x <= 0`.
bool int__is_zero( int x );         // Returns `x == 0`.
bool int__is_nonnegative( int x );  // Returns `x >= 0`.
bool int__is_positive( int x );     // Returns `x > 0`.
ord  int__compare_0( int x );       // Returns `int__compare( x, 0 )`.


int int__add_2( int x );    // Returns `int__add( x, 2 )`.
int int__sub_2( int x );    // Returns `int__sub( x, 2 )`.
int int__mul_2( int x );    // Returns `int__mul( x, 2 )`.
int int__div_2( int x );    // Returns `int__div( x, 2 )`.
int int__mod_2( int x );    // Returns `int__mod( x, 2 )`.



/////////////////////////////
/// READ TYPECLASS
/////////////////////////////


size_t int__str_length( int x );
// Returns the number of `char`s required to represent `x`.


void int__into_str( int x, char * str, size_t size );
// Writes the decimal representation of `x` into `str`, up to a maximum of
// `size` characters including the null terminating byte.


char * int__to_str( int x );
// Allocates a `char` buffer of `int__str_length( x ) + 1` bytes, writes the
// decimal representation of `x` into it, and returns a pointer to that
// buffer. The buffer is dynamically allocated, so call `free()` when you're
// done with it.


void int__print( int x, FILE * file );
// Prints the decimal representation of `x` to the given `file`, minus the
// null terminating byte, and without any trailing newline.
//
// @require int__str_length( x ) < 64



/////////////////////////////
/// BITS TYPECLASS
/////////////////////////////


extern int const int__zero_bits;
// The `int` value with all bits unset, except any padding bits.

extern int const int__one_bits;
// The `int` value with all bits set, except any padding bits.


size_t int__precision( void );
// The number of bits used to represent an `int` value, excluding the sign
// bit and any padding bits.

size_t int__width( void );
// The number of bits used to represent an `int` value, including the sign
// bit, but excluding any padding bits. Equivalent to `int__precision() + 1`.

size_t int__padding( void );
// The number of padding bits in the object representation of an `int`.
// Equivalent to `( sizeof ( int ) * 8 ) - int__width()`.


bool int__can_lshift( int x, size_t n );
// Returns the boolean that the behavior of `x << n` is well-defined.
// Equivalent to:
//
//        ( x >= 0 )
//     && ( n < int__width() )
//     && ( x <= ( int__max_bound >> n ) )

bool int__can_rshift( int x, size_t n );
// Returns the boolean that the behavior of `x >> n` is well-defined.
// Equivalent to:
//
//        ( x >= 0 )
//     && ( n < int__width() )


int int__lshift( int x, size_t n );
// Shifts `x` left by `n` bits, i.e. `x << n`.
//
// @requires int__can_lshift( x, n )

int int__rshift( int x, size_t n );
// Shifts `x` right by `n` bits, i.e. `x >> n`.
//
// @requires int__can_rshift( x, n )

int int__shift( int x, lssize_t n );
// Returns `( n > 0 ) ? int__lshift( x, n ) : int__rshift( x, n )`.


int int__lrotate( int x, size_t n );
// Rotates `x` left by `n` bits. Equivalent to:
//
//     ( x << n ) | ( x >> ( int__precision() - n ) )
//
// @requires int__can_lshift( x, n )
//        && int__can_rshift( x, int__precision() - n )

int int__rrotate( int x, size_t n );
// Rotates `x` right by `n` bits. Equivalent to:
//
//     ( x >> n ) | ( x << ( int__precision() - n ) )
//
// @requires int__can_rshift( x, n )
//        && int__can_lshift( x, int__precision() - n )

int int__rotate( int x, lssize_t n );
// Returns `( n > 0 ) ? int__lrotate( x, n ) : int__rrotate( x, -n )`.


int int__bitwise_and( int x, int y );   // Returns `x & y`.
int int__bitwise_or( int x, int y );    // Returns `x | y`.
int int__bitwise_xor( int x, int y );   // Returns `x ^ y`.
int int__bitwise_not( int x, int y );   // Returns `~x`.


int int__bit( size_t n );
// Returns the `int` value with the `n`th bit set (0-indexed) and all other
// bits unset. Equivalent to `1 << n`.
//
// @requires n < int__precision()


bool int__get_bit( int x, size_t n );
// Returns `true` if the `n`th bit of `x` is set, or `false` otherwise.
// Equivalent to: `( x & int__bit( n ) ) != 0`.
//
// @requires n < int__precision()


int int__set_bit( int x, size_t n );
// Returns `x` with the `n`th bit (0-indexed) set.
//
// @requires n < int__precision()


int int__clear_bit( int x, size_t n );
// Returns `x` with the `n`th bit (0-indexed) unset.
//
// @requires n < int__precision()


int int__toggle_bit( int x, size_t n );
// Returns `x` with the `n`th bit (0-indexed) set if it was unset, or unset
// if it was set.
//
// @requires n < int__precision()


int int__assign_bit( int x, size_t n, bool b );
// Returns `x` with the `n`th bit (0-indexed) set if `b == true`, or unset if
// `b == false`.
//
// @requires n < int__precision()


int int__clear_lowest_set_bit( int x );
// Returns `x` with its least-significant set bit unset, or just `x` if
// `x == 0`, i.e. all bits were unset.


int int__reverse_bits( int x );
// Returns the `int` value whose object representation is the bitwise-reverse
// of the object representation of `x`.


size_t int__count_set_bits( int x );
// Returns the number of set bits among the sign and value bits of `x`. This
// operation is also known as the population count, or just "popcount".


size_t int__count_trailing_zeroes( int x );
// Returns the number of consecutive unset bits from the right of the binary
// representation of `x`. For example, binary 01011000 is decimal 88 and has
// three trailing zero bits.


int int__lshift_1( int x );     // Returns `int__lshift( x, 1 )`.
int int__rshift_1( int x );     // Returns `int__rshift( x, 1 )`.
int int__lrotate_1( int x );    // Returns `int__lrotate( x, 1 )`.
int int__rrotate_1( int x );    // Returns `int__rrotate( x, 1 )`.


#endif

