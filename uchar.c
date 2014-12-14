
#include "uchar.h"

#include <limits.h>                 // UCHAR_MAX, UCHAR_MIN

#include <libpp/call.h>             // PP_CALL
#include <libpp/separators.h>       // PP_SEP_NONE
#include <libtypes/types.h>         // UCHAR_TYPE

#include "eq/scalar.h"              // DERIVING_EQ_SCALAR
#include "ord/scalar.h"             // DERIVING_ORD_SCALAR
#include "enum/scalar.h"            // DERIVING_ENUM_SCALAR
#include "num/integral-unsigned.h"  // DERIVING_NUM_INTEGRAL_UNSIGNED


uchar uchar__id( uchar const x ) { return x; }


uchar uchar__min_bound( void ) { return 0; }
uchar uchar__max_bound( void ) { return UCHAR_MAX; }


PP_CALL( UCHAR_TYPE, PP_SEP_NONE, DERIVING_EQ_SCALAR,
                                  DERIVING_ORD_SCALAR,
                                  DERIVING_ENUM_SCALAR,
                                  DERIVING_NUM_INTEGRAL_UNSIGNED )


