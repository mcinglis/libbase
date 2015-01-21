
// Copyright 2015  Malcolm Inglis <http://minglis.id.au>
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


#include "ulong.h"

#include <limits.h>                 // ULONG_MAX

#include <libpp/call.h>             // PP_CALL
#include <libpp/separators.h>       // PP_SEP_NONE
#include <libtypes/types.h>         // ULONG_TYPE

#include "eq/scalar.h"              // DERIVING_EQ_SCALAR
#include "ord/scalar.h"             // DERIVING_ORD_SCALAR
#include "enum/scalar.h"            // DERIVING_ENUM_SCALAR
#include "num/integral-unsigned.h"  // DERIVING_NUM_INTEGRAL_UNSIGNED
#include "read/integral-unsigned.h" // DERIVING_READ_INTEGRAL_UNSIGNED


ulong ulong__id( ulong const x ) { return x; }


ulong ulong__min_bound( void ) { return 0; }
ulong ulong__max_bound( void ) { return ULONG_MAX; }


PP_CALL( ULONG_TYPE, PP_SEP_NONE, DERIVING_EQ_SCALAR,
                                  DERIVING_ORD_SCALAR,
                                  DERIVING_ENUM_SCALAR,
                                  DERIVING_NUM_INTEGRAL_UNSIGNED,
                                  DERIVING_READ_INTEGRAL_UNSIGNED )

