
#include "bool.h"

#include <libpp/call.h>         // PP_CALL
#include <libpp/separators.h>   // PP_SEP_NONE
#include <libtypes/types.h>     // bool, BOOL_TYPE

#include "eq/scalar.h"          // DERIVING_EQ_SCALAR
#include "ord/scalar.h"         // DERIVING_ORD_SCALAR
#include "enum/scalar.h"        // DERIVING_ENUM_SCALAR


bool bool__id( bool const x ) { return x; }


bool bool__min_bound( void ) { return false; }
bool bool__max_bound( void ) { return true; }


PP_CALL( BOOL_TYPE, PP_SEP_NONE, DERIVING_EQ_SCALAR,
                                 DERIVING_ORD_SCALAR,
                                 DERIVING_ENUM_SCALAR )


