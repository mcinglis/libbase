
// Copyright 2014  Malcolm Inglis <http://minglis.id.au>
//
// This file is part of Libbase.
//
// Libbase is free software: you can redistribute it and/or modify it under
// the terms of the GNU Affero General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
//
// Libbase is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
// more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with Libbase. If not, see <https://gnu.org/licenses/>.


#include "uchar.h"

#include <stdlib.h>                 // strtoul
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


Maybe_uchar
uchar__from_str( char const * const str )
{
    if ( str == NULL || str[ 0 ] == '\0' ) {
        return ( Maybe_uchar ){ .nothing = true };
    }
    char * end_ptr;
    ulong const x = strtoul( str, &end_ptr, 10 );
    if ( end_ptr[ 0 ] != '\0'
      || x > uchar__max_bound() ) {
        return ( Maybe_uchar ){ .nothing = true };
    }
    return ( Maybe_uchar ){ .value = x };
}


