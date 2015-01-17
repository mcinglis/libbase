
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


