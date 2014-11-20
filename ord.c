
#include "ord.h"

#include <libpp/call.h>         // PP_CALL
#include <libpp/separators.h>   // PP_SEP_NONE
#include <libtypes/types.h>     // ord, ORD_TYPE

#include "eq/scalar.h"          // DERIVING_EQ_SCALAR
#include "ord/scalar.h"         // DERIVING_ORD_SCALAR
#include "enum/scalar.h"        // DERIVING_ENUM_SCALAR


ord ord__id( ord const x ) { return x; }


ord ord__min_bound( void ) { return LT; }
ord ord__max_bound( void ) { return GT; }


PP_CALL( ORD_TYPE, PP_SEP_NONE, DERIVING_EQ_SCALAR,
                                DERIVING_ORD_SCALAR,
                                DERIVING_ENUM_SCALAR )


