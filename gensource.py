
# Copyright 2015  Malcolm Inglis <http://minglis.id.au>
#
# This file is part of Libbase.
#
# Libbase is free software: you can redistribute it and/or modify it under
# the terms of the GNU Affero General Public License as published by the
# Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# Libbase is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
# more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with Libbase. If not, see <https://gnu.org/licenses/>.


from __future__ import print_function
from argparse import ArgumentParser


# This is printed first:
PREFIX = '''
// This file is the result of executing `gensource.py`. You should make changes
// to this code by changing the template strings or the build process -- not
// editing this file.
'''


# This is printed after the `PREFIX` string:
LICENSE = '''
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
'''


# This is printed after the `PREFIX` and `LICENSE` strings:
TOP = '''
#include "{filename}.h"

#include <libtypes/types.h>


{type} {funcname}__id( {type} const x ) {{ return x; }}
'''


# What to prefix each typeclass section by:
TYPECLASS_HEADER = '''

///////////////////////////////////
/// TYPECLASS: {typeclass}
///////////////////////////////////
'''


def read_num(strtox, return_type):
    return '''
#include <errno.h>
#include <inttypes.h>
#include <stdlib.h>

{type}
{funcname}__from_str( char const * const str )
{{
    if ( str == NULL || str[ 0 ] == '\\0' ) {{
        errno = EINVAL;
        return 0;
    }}
    errno = 0;
    char * end_ptr;
    %s const x = %s( str, &end_ptr, 10 );
    if ( errno ) {{
        return 0;
    }} else if ( *end_ptr != '\\0' ) {{
        errno = EBADMSG;
        return 0;
    }} else if ( x < {funcname}__min_bound()
             || x > {funcname}__max_bound() ) {{
        errno = ERANGE;
        return 0;
    }} else {{
        return x;
    }}
}}
''' % (return_type, strtox)


# Mappings of typeclass names to the prototypes and macros they represent:
TYPECLASSES = {

    'BOUNDED': {
        'BOOL': '''
{type} {funcname}__min_bound( void ) {{ return false; }}
{type} {funcname}__max_bound( void ) {{ return true; }}
''',
        'SHORT': '''
#include <limits.h>

{type} {funcname}__min_bound( void ) {{ return SHRT_MIN; }}
{type} {funcname}__max_bound( void ) {{ return SHRT_MAX; }}
''',
        'USHORT': '''
#include <limits.h>

{type} {funcname}__min_bound( void ) {{ return 0; }}
{type} {funcname}__max_bound( void ) {{ return USHRT_MAX; }}
''',
        'SIGNED': '''
#include <limits.h>

{type} {funcname}__min_bound( void ) {{ return {macroname}_MIN; }}
{type} {funcname}__max_bound( void ) {{ return {macroname}_MAX; }}
''',
        'UNSIGNED': '''
#include <limits.h>

{type} {funcname}__min_bound( void ) {{ return 0; }}
{type} {funcname}__max_bound( void ) {{ return {macroname}_MAX; }}
'''
    },


    'EQ': {
        '*': '''
bool
{funcname}__equal(
        {type} const x,
        {type} const y )
{{
    return x == y;
}}


bool
{funcname}__not_equal(
        {type} const x,
        {type} const y )
{{
    return x != y;
}}
'''
    },


    'ORD': {
        '*': '''
#include <libmacro/assert.h>


ord
{funcname}__compare(
        {type} const x,
        {type} const y )
{{
    return ( x > y ) - ( x < y );
}}


bool
{funcname}__less_than(
        {type} const x,
        {type} const y )
{{
    return x < y;
}}


bool
{funcname}__less_than_or_eq(
        {type} const x,
        {type} const y )
{{
    return x <= y;
}}


bool
{funcname}__greater_than_or_eq(
        {type} const x,
        {type} const y )
{{
    return x >= y;
}}


bool
{funcname}__greater_than(
        {type} const x,
        {type} const y )
{{
    return x > y;
}}


{type}
{funcname}__min2(
        {type} const x,
        {type} const y )
{{
    return ( x < y ) ? x : y;
}}


{type}
{funcname}__max2(
        {type} const x,
        {type} const y )
{{
    return ( x > y ) ? x : y;
}}


{type}
{funcname}__min_n(
        size_t const n,
        {type} const * const xs )
{{
    ASSERT( n != 0, xs != NULL );

    {type} min = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {{
        min = {funcname}__min2( min, xs[ i ] );
    }}
    return min;
}}


{type}
{funcname}__max_n(
        size_t const n,
        {type} const * const xs )
{{
    ASSERT( n != 0, xs != NULL );

    {type} max = xs[ 0 ];
    for ( size_t i = 1; i < n; i++ ) {{
        max = {funcname}__max2( max, xs[ i ] );
    }}
    return max;
}}


{type}
{funcname}__clamp(
        {type} const lower,
        {type} const upper,
        {type} const x )
{{
    return ( lower >= x ) ? lower
         : ( upper <= x ) ? upper
                          : x;
}}
'''
    },


    'ENUM': {
        '*': '''
#include <libmacro/assert.h>


{type}
{funcname}__succ( {type} const x )
{{
    ASSERT( x != {funcname}__max_bound() );

    return x + 1;
}}


{type}
{funcname}__succ_b( {type} const x )
{{
    return ( x == {funcname}__max_bound() ) ? x : ( x + 1 );
}}


{type}
{funcname}__pred( {type} const x )
{{
    ASSERT( x != {funcname}__min_bound() );

    return x - 1;
}}


{type}
{funcname}__pred_b( {type} const x )
{{
    return ( x == {funcname}__min_bound() ) ? x : ( x - 1 );
}}
'''

    },


    'NUM': {

        'SIGNED': '''
bool {funcname}__is_signed( void ) {{ return true; }}


bool
{funcname}__add_would_underflow(
        {type} const x,
        {type} const y )
{{
    return y < 0 && x < ( {funcname}__min_bound() - y );
}}


bool
{funcname}__add_would_overflow(
        {type} const x,
        {type} const y )
{{
    return y > 0 && x > ( {funcname}__max_bound() - y );
}}


bool
{funcname}__can_add(
        {type} const x,
        {type} const y )
{{
    return !{funcname}__add_would_underflow( x, y )
        && !{funcname}__add_would_overflow( x, y );
}}


bool
{funcname}__sub_would_underflow(
        {type} const x,
        {type} const y )
{{
    return y > 0 && x < ( {funcname}__min_bound() + y );
}}


bool
{funcname}__sub_would_overflow(
        {type} const x,
        {type} const y )
{{
    return y < 0 && x > ( {funcname}__max_bound() + y );
}}


bool
{funcname}__can_sub(
        {type} const x,
        {type} const y )
{{
    return !{funcname}__sub_would_underflow( x, y )
        && !{funcname}__sub_would_overflow( x, y );
}}


bool
{funcname}__mul_would_underflow(
        {type} const x,
        {type} const y )
{{
    return ( x > 0 && y < 0 ) ? ( y < ( {funcname}__min_bound() / x ) )
         : ( x < 0 && y > 0 ) ? ( x < ( {funcname}__min_bound() / y ) )
                              : false;
}}


bool
{funcname}__mul_would_overflow(
        {type} const x,
        {type} const y )
{{
    return ( x > 0 && y > 0 ) ? ( x > ( {funcname}__max_bound() / y ) )
         : ( x < 0 && y < 0 ) ? ( y < ( {funcname}__max_bound() / x ) )
                              : false;
}}


bool
{funcname}__can_mul(
        {type} const x,
        {type} const y )
{{
    return !{funcname}__mul_would_underflow( x, y )
        && !{funcname}__mul_would_overflow( x, y );
}}


bool
{funcname}__div_would_underflow(
        {type} const x,
        {type} const y )
{{
    return false;
}}


bool
{funcname}__div_would_overflow(
        {type} const x,
        {type} const y )
{{
    return x == {funcname}__min_bound() && y == -1;
}}


bool
{funcname}__can_div(
        {type} const x,
        {type} const y )
{{
    return ( y != 0 && !{funcname}__div_would_overflow( x, y ) );
}}


{type}
{funcname}__add(
        {type} const x,
        {type} const y )
{{
    ASSERT( {funcname}__can_add( x, y ) );

    return x + y;
}}


{type}
{funcname}__sub(
        {type} const x,
        {type} const y )
{{
    ASSERT( {funcname}__can_sub( x, y ) );

    return x - y;
}}


{type}
{funcname}__mul(
        {type} const x,
        {type} const y )
{{
    ASSERT( {funcname}__can_mul( x, y ) );

    return x * y;
}}


{type}
{funcname}__div(
        {type} const x,
        {type} const y )
{{
    ASSERT( {funcname}__can_div( x, y ) );

    return x / y;
}}


{type}
{funcname}__mod(
        {type} const x,
        {type} const y )
{{
    ASSERT( {funcname}__can_div( x, y ) );

    return x % y;
}}


{type}
{funcname}__negate( {type} const x )
{{
    ASSERT( x != {funcname}__min_bound() );

    return -x;
}}


{type}
{funcname}__abs( {type} const x )
{{
    ASSERT( x != {funcname}__min_bound() );

    return ( x < 0 ) ? -x : x;
}}


{type}
{funcname}__add_b(
        {type} const x,
        {type} const y )
{{
    if ( {funcname}__add_would_underflow( x, y ) ) {{
        return {funcname}__min_bound();
    }} else if ( {funcname}__add_would_overflow( x, y ) ) {{
        return {funcname}__max_bound();
    }} else {{
        return x + y;
    }}
}}


{type}
{funcname}__sub_b(
        {type} const x,
        {type} const y )
{{
    if ( {funcname}__sub_would_underflow( x, y ) ) {{
        return {funcname}__min_bound();
    }} else if ( {funcname}__sub_would_overflow( x, y ) ) {{
        return {funcname}__max_bound();
    }} else {{
        return x - y;
    }}
}}


{type}
{funcname}__mul_b(
        {type} const x,
        {type} const y )
{{
    if ( {funcname}__mul_would_underflow( x, y ) ) {{
        return {funcname}__min_bound();
    }} else if ( {funcname}__mul_would_overflow( x, y ) ) {{
        return {funcname}__max_bound();
    }} else {{
        return x * y;
    }}
}}


{type}
{funcname}__div_b(
        {type} const x,
        {type} const y )
{{
    if ( y == 0 ) {{
        if ( x < 0 ) {{
            return {funcname}__min_bound();
        }} else if ( x == 0 ) {{
            return 0;
        }} else /* x > 0 */ {{
            return {funcname}__max_bound();
        }}
    }} else if ( {funcname}__div_would_underflow( x, y ) ) {{
        return {funcname}__min_bound();
    }} else if ( {funcname}__div_would_overflow( x, y ) ) {{
        return {funcname}__max_bound();
    }} else {{
        return x / y;
    }}
}}


{type}
{funcname}__mod_b(
        {type} const x,
        {type} const y )
{{
    if ( !{funcname}__can_div( x, y ) ) {{
        return 0;
    }} else {{
        return x % y;
    }}
}}


{type}
{funcname}__negate_b( {type} const x )
{{
    if ( x == {funcname}__min_bound() ) {{
        return {funcname}__max_bound();
    }} else {{
        return -x;
    }}
}}


{type}
{funcname}__abs_b( {type} const x )
{{
    if ( x == {funcname}__min_bound() ) {{
        return {funcname}__max_bound();
    }} else {{
        return {funcname}__abs( x );
    }}
}}


bool
{funcname}__same_sign(
        {type} const x,
        {type} const y )
{{
    return ( x < 0 ) == ( y < 0 );
}}


bool {funcname}__is_negative   ( {type} const x ) {{ return x < 0; }}
bool {funcname}__is_nonpositive( {type} const x ) {{ return x <= 0; }}
bool {funcname}__is_zero       ( {type} const x ) {{ return x == 0; }}
bool {funcname}__is_nonnegative( {type} const x ) {{ return x >= 0; }}
bool {funcname}__is_positive   ( {type} const x ) {{ return x > 0; }}


ord
{funcname}__compare_0( {type} const x )
{{
    return {funcname}__compare( x, 0 );
}}


bool {funcname}__is_even( {type} const x ) {{ return x % 2 == 0; }}
bool {funcname}__is_odd ( {type} const x ) {{ return x % 2 == 1; }}


{type} {funcname}__add_2( {type} const x )
        {{ return {funcname}__add( x, 2 ); }}
{type} {funcname}__sub_2( {type} const x )
        {{ return {funcname}__sub( x, 2 ); }}
{type} {funcname}__mul_2( {type} const x )
        {{ return {funcname}__mul( x, 2 ); }}
{type} {funcname}__div_2( {type} const x )
        {{ return {funcname}__div( x, 2 ); }}
{type} {funcname}__mod_2( {type} const x )
        {{ return {funcname}__mod( x, 2 ); }}


{type} {funcname}__mul_10( {type} const x )
        {{ return {funcname}__mul( x, 10 ); }}
{type} {funcname}__div_10( {type} const x )
        {{ return {funcname}__div( x, 10 ); }}


{type} {funcname}__add_b_2( {type} const x )
        {{ return {funcname}__add_b( x, 2 ); }}
{type} {funcname}__sub_b_2( {type} const x )
        {{ return {funcname}__sub_b( x, 2 ); }}
{type} {funcname}__mul_b_2( {type} const x )
        {{ return {funcname}__mul_b( x, 2 ); }}
{type} {funcname}__mul_b_10( {type} const x )
        {{ return {funcname}__mul_b( x, 10 ); }}
''',

        'UNSIGNED': '''
bool {funcname}__is_signed( void ) {{ return false; }}


bool
{funcname}__add_would_underflow(
        {type} const x,
        {type} const y )
{{
    return false;
}}


bool
{funcname}__add_would_overflow(
        {type} const x,
        {type} const y )
{{
    return ( x > ( {funcname}__max_bound() - y ) );
}}


bool
{funcname}__can_add(
        {type} const x,
        {type} const y )
{{
    return !{funcname}__add_would_overflow( x, y );
}}


bool
{funcname}__sub_would_underflow(
        {type} const x,
        {type} const y )
{{
    return ( x < y );
}}


bool
{funcname}__sub_would_overflow(
        {type} const x,
        {type} const y )
{{
    return false;
}}


bool
{funcname}__can_sub(
        {type} const x,
        {type} const y )
{{
    return !{funcname}__sub_would_underflow( x, y );
}}


bool
{funcname}__mul_would_underflow(
        {type} const x,
        {type} const y )
{{
    return false;
}}


bool
{funcname}__mul_would_overflow(
        {type} const x,
        {type} const y )
{{
    return ( x > ( {funcname}__max_bound() / y ) );
}}


bool
{funcname}__can_mul(
        {type} const x,
        {type} const y )
{{
    return !{funcname}__mul_would_overflow( x, y );
}}


bool
{funcname}__div_would_underflow(
        {type} const x,
        {type} const y )
{{
    return false;
}}


bool
{funcname}__div_would_overflow(
        {type} const x,
        {type} const y )
{{
    return false;
}}


bool
{funcname}__can_div(
        {type} const x,
        {type} const y )
{{
    return y != 0;
}}


{type}
{funcname}__add(
        {type} const x,
        {type} const y )
{{
    return x + y;
}}


{type}
{funcname}__sub(
        {type} const x,
        {type} const y )
{{
    return x - y;
}}


{type}
{funcname}__mul(
        {type} const x,
        {type} const y )
{{
    return x * y;
}}


{type}
{funcname}__div(
        {type} const x,
        {type} const y )
{{
    ASSERT( y != 0 );

    return x / y;
}}


{type}
{funcname}__mod(
        {type} const x,
        {type} const y )
{{
    ASSERT( y != 0 );

    return x % y;
}}


{type}
{funcname}__negate( {type} const x )
{{
    return -x;
}}


{type}
{funcname}__abs( {type} const x )
{{
    return x;
}}


{type}
{funcname}__add_b(
        {type} const x,
        {type} const y )
{{
    if ( {funcname}__add_would_overflow( x, y ) ) {{
        return {funcname}__max_bound();
    }} else {{
        return x + y;
    }}
}}


{type}
{funcname}__sub_b(
        {type} const x,
        {type} const y )
{{
    if ( {funcname}__sub_would_underflow( x, y ) ) {{
        return 0;
    }} else {{
        return x - y;
    }}
}}


{type}
{funcname}__mul_b(
        {type} const x,
        {type} const y )
{{
    if ( {funcname}__mul_would_overflow( x, y ) ) {{
        return {funcname}__max_bound();
    }} else {{
        return x * y;
    }}
}}


{type}
{funcname}__div_b(
        {type} const x,
        {type} const y )
{{
    if ( y == 0 ) {{
        if ( x == 0 ) {{
            return 0;
        }} else /* x > 0 */ {{
            return {funcname}__max_bound();
        }}
    }} else {{
        return x / y;
    }}
}}


{type}
{funcname}__mod_b(
        {type} const x,
        {type} const y )
{{
    if ( y == 0 ) {{
        return 0;
    }} else {{
        return x % y;
    }}
}}


{type}
{funcname}__negate_b( {type} const x )
{{
    return {funcname}__negate( x );
}}


{type}
{funcname}__abs_b( {type} const x )
{{
    return {funcname}__abs( x );
}}


bool
{funcname}__same_sign(
        {type} const x,
        {type} const y )
{{
    return true;
}}


bool {funcname}__is_negative   ( {type} const x ) {{ return false; }}
bool {funcname}__is_nonpositive( {type} const x ) {{ return x == 0; }}
bool {funcname}__is_zero       ( {type} const x ) {{ return x == 0; }}
bool {funcname}__is_nonnegative( {type} const x ) {{ return true; }}
bool {funcname}__is_positive   ( {type} const x ) {{ return x != 0; }}


ord
{funcname}__compare_0( {type} const x )
{{
    return {funcname}__compare( x, 0 );
}}


bool {funcname}__is_even( {type} const x ) {{ return x % 2 == 0; }}
bool {funcname}__is_odd ( {type} const x ) {{ return x % 2 == 1; }}


{type} {funcname}__add_2( {type} const x )
        {{ return {funcname}__add( x, 2 ); }}
{type} {funcname}__sub_2( {type} const x )
        {{ return {funcname}__sub( x, 2 ); }}
{type} {funcname}__mul_2( {type} const x )
        {{ return {funcname}__mul( x, 2 ); }}
{type} {funcname}__div_2( {type} const x )
        {{ return {funcname}__div( x, 2 ); }}
{type} {funcname}__mod_2( {type} const x )
        {{ return {funcname}__mod( x, 2 ); }}


{type} {funcname}__mul_10( {type} const x )
        {{ return {funcname}__mul( x, 10 ); }}
{type} {funcname}__div_10( {type} const x )
        {{ return {funcname}__div( x, 10 ); }}


{type} {funcname}__add_b_2( {type} const x )
        {{ return {funcname}__add_b( x, 2 ); }}
{type} {funcname}__sub_b_2( {type} const x )
        {{ return {funcname}__sub_b( x, 2 ); }}
{type} {funcname}__mul_b_2( {type} const x )
        {{ return {funcname}__mul_b( x, 2 ); }}
{type} {funcname}__mul_b_10( {type} const x )
        {{ return {funcname}__mul_b( x, 10 ); }}
'''
    },


    'READ': {
        'STRTOL':    read_num('strtol', 'long'),
        'STRTOLL':   read_num('strtoll', 'llong'),
        'STRTOIMAX': read_num('strtoimax', 'intmax_t'),
        'STRTOUL':   read_num('strtoul', 'ulong'),
        'STRTOULL':  read_num('strtoull', 'ullong'),
        'STRTOUMAX': read_num('strtoumax', 'uintmax_t'),
        'BOOL': '''
#include <ctype.h>
#include <errno.h>
#include <string.h>

{type}
{funcname}__from_str( char const * str )
{{
    if ( str == NULL || str[ 0 ] == '\\0' ) {{
        errno = EINVAL;
        return false;
    }}
    errno = 0;
    while ( isspace( *str ) ) {{
        str++;
    }}
    {type} r;
    static char const true_str[] = "true";
    static char const false_str[] = "false";
    if ( strncmp( str, true_str, sizeof true_str - 1 ) == 0 ) {{
        r = true;
        str += sizeof true_str - 1;
    }} else if ( strncmp( str, false_str, sizeof false_str - 1 ) == 0 ) {{
        r = false;
        str += sizeof false_str - 1;
    }} else {{
        errno = EBADMSG;
        return false;
    }}
    while ( isspace( *str ) ) {{
        str++;
    }}
    if ( *str != '\\0' ) {{
        errno = EBADMSG;
        return false;
    }}
    return r;
}}
'''
    },


    'TO_CONSTSTR': {
        'BOOL': '''
char const *
{funcname}__to_conststr( {type} const x )
{{
    return x ? "true" : "false";
}}
'''
    }

}


def render(file, type, macroname, typename, funcname, filename,
           typeclasses=None):
    typeclasses = typeclasses or []
    def fmt(s):
        return s.format(type=type, macroname=macroname, typename=typename,
                        funcname=funcname, filename=filename)
    print(fmt(PREFIX), file=file)
    print(fmt(LICENSE), file=file)
    print(fmt(TOP), file=file)
    for tc in typeclasses:
        sel = '*'
        if ':' in tc:
            tc, sel = tc.split(':', 2)
        print(TYPECLASS_HEADER.format(typeclass=tc), file=file)
        print(fmt(TYPECLASSES.get(tc)[sel]), file=file)


def parse_args(argv):
    p = ArgumentParser(description='Prints to stdout the text of a header '
                                   'file for Libbase with the given values.')
    p.add_argument('type',
                   help='the type, e.g. `int` or `uint32_t`')
    p.add_argument('macroname',
                   help='the name to use in macros, e.g. `INT` or `UINT32` '
                        'in macros like `LIBBASE_INT_H`')
    p.add_argument('typename',
                   help='the name to use in types, e.g. `int` or `uint32` '
                        'in types like `Maybe_int` or `ArrayM_uint32`')
    p.add_argument('funcname',
                   help='the name to use in functions, e.g. `int` or `uint32` '
                        'in functions like `int__equal` or `uint32__min2`')
    p.add_argument('filename',
                   help='the name to use in filepaths, e.g. `int` or `uint32` '
                        'in paths like `int.h` or `maybe-uint32.h`')
    p.add_argument('-t', '--typeclasses', nargs='+', metavar='TC',
                                          choices=typeclass_choices(),
                   help='the typeclasses that this type implements; must be '
                        'one of: ' + ', '.join(typeclass_choices()))
    p.add_argument('-o', '--output', type=str, default='/dev/stdout',
                   help='the filepath to write the rendered template to')
    a = p.parse_args(argv[1:])
    a.typeclasses = a.typeclasses or []
    return a


def typeclass_choices():
    choices = []
    for k, v in TYPECLASSES.items():
        for sel in v.keys():
            if sel != '*':
                choices.append(k + ':' + sel)
            else:
                choices.append(k)
    return choices


def main(stdout, argv):
    args = parse_args(argv)
    with open(args.output, 'w') as f:
        render(f, args.type, args.macroname, args.typename, args.funcname,
                  args.filename, typeclasses=args.typeclasses)
    return 0


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.stdout, sys.argv))


