
#include "int.h"

#include <limits.h>                 // INT_MAX, INT_MIN

#include <libpp/call.h>             // PP_CALL
#include <libpp/separators.h>       // PP_SEP_NONE
#include <libtypes/types.h>         // INT_TYPE

#include "eq/scalar.h"              // DERIVING_EQ_SCALAR
#include "ord/scalar.h"             // DERIVING_ORD_SCALAR
#include "enum/scalar.h"            // DERIVING_ENUM_SCALAR
#include "num/integral-signed.h"    // DERIVING_NUM_INTEGRAL_SIGNED


int int__id( int const x ) { return x; }


int int__min_bound( void ) { return INT_MIN; }
int int__max_bound( void ) { return INT_MAX; }


PP_CALL( INT_TYPE, PP_SEP_NONE, DERIVING_EQ_SCALAR,
                                DERIVING_ORD_SCALAR,
                                DERIVING_ENUM_SCALAR,
                                DERIVING_NUM_INTEGRAL_SIGNED )


