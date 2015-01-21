
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


#ifndef LIBBASE_READ_INTEGRAL_SIGNED_H
#define LIBBASE_READ_INTEGRAL_SIGNED_H


#include <stdlib.h>
#include <errno.h>

#include <libmacro/require.h>   // REQUIRE


// @public
#define DERIVING_READ_INTEGRAL_SIGNED( T, TT, TF ) \
                                                                              \
                                                                              \
    Result_##TT                                                               \
    TF##__from_str( char const * const str )                                  \
    {                                                                         \
        if ( str == NULL || str[ 0 ] == '\0' ) {                              \
            return ( Result_##TT ){ .error = EINVAL };                        \
        }                                                                     \
        char * end_ptr;                                                       \
        errno = 0;                                                            \
        llong const x = strtoll( str, &end_ptr, 10 );                         \
        return ( errno != 0 )           ? ( Result_##TT ){ .error = errno }   \
             : ( *end_ptr != '\0' )     ? ( Result_##TT ){ .error = EBADMSG } \
             : ( x < TF##__min_bound()                                        \
              || x > TF##__max_bound() )? ( Result_##TT ){ .error = ERANGE }  \
                                        : ( Result_##TT ){ .value = x };      \
    }                                                                         \
                                                                              \
                                                                              \
    T                                                                         \
    TF##__from_str_e( char const * const str,                                 \
                      int * const err )                                       \
    {                                                                         \
        Result_##TT const r = TF##__from_str( str );                          \
        if ( err != NULL ) {                                                  \
            *err = r.error;                                                   \
        }                                                                     \
        return r.value;                                                       \
    }                                                                         \


#endif

