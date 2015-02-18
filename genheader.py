
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
// This file is the result of executing `genheader.py`. You should make changes
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
#ifndef LIBBASE_{macroname}_H
#define LIBBASE_{macroname}_H


#include <libpp/count.h>        // PP_COUNT
#include <libtypes/types.h>     // bool, ord


typedef struct maybe_{typename} {{
    {type} value;
    bool nothing;
}} Maybe_{typename};


typedef struct result_{typename} {{
    {type} value;
    int error;
}} Result_{typename};


typedef struct arrayc_{typename} {{
    {type} const * e;
    size_t length;
}} ArrayC_{typename};


typedef struct arraym_{typename} {{
    {type} * e;
    size_t length;
}} ArrayM_{typename};


typedef struct vec_{typename} {{
    {type} * e;
    size_t length;
    size_t capacity;
}} Vec_{typename};


{type} {funcname}__id( {type} x );
// The identity function; returns `x`.
'''


# What to prefix each typeclass section by:
TYPECLASS_HEADER = '''

///////////////////////////////////
/// TYPECLASS: {typeclass}
///////////////////////////////////'''


# Mappings of typeclass names to the prototypes and macros they represent:
TYPECLASSES = {


    'BOUNDED': {
        '*': '''
{type} {funcname}__min_bound( void );
// Returns the minimum value representable by the `{type}` type.

{type} {funcname}__max_bound( void );
// Returns the maximum value representable by the `{type}` type.
''',
        'UNSIGNED': '''
{type} {funcname}__min_bound( void );
// Returns `0`, as that's the minimum value representable by `{type}`.

{type} {funcname}__max_bound( void );
// Returns the maximum value representable by the `{type}` type.
'''
    },


    'EQ': {
        '*': '''
bool {funcname}__equal( {type} x, {type} y );
// Returns `true` if `x == y`, or `false` if not.

bool {funcname}__not_equal( {type} x, {type} y );
// Returns `true` if `x != y`, or `false` if not.
'''
    },


    'ORD': {
        '*': '''
ord {funcname}__compare( {type} x, {type} y );
// Returns: `LT` if `x < y`,
//          `EQ` if `x == y`, or
//          `GT` if `x > y`.

bool {funcname}__less_than( {type} x, {type} y );
// Returns `true` if `x < y`, or `false` if not.

bool {funcname}__less_than_or_eq( {type} x, {type} y );
// Returns `true` if `x <= y`, or `false` if not.

bool {funcname}__greater_than_or_eq( {type} x, {type} y );
// Returns `true` if `x >= y`, or `false` if not.

bool {funcname}__greater_than( {type} x, {type} y );
// Returns `true` if `x > y`, or `false` if not.

{type} {funcname}__min2( {type} x, {type} y );
// Returns `x` if `x < y`, or `y` otherwise.

{type} {funcname}__max2( {type} x, {type} y );
// Returns `x` if `x > y`, or `y` otherwise.

{type} {funcname}__min_n( size_t n, {type} const * xs );
// Returns the minimum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

{type} {funcname}__max_n( size_t n, {type} const * xs );
// Returns the maximum value of the first `n` elements in the array `xs`.
// @requires n > 0, xs != NULL

// @public
#define {funcname}__min( ... ) \\
    {funcname}__min_n( PP_COUNT( __VA_ARGS__ ), ( {type}[] ){{ __VA_ARGS__ }} )

// @public
#define {funcname}__max( ... ) \\
    {funcname}__max_n( PP_COUNT( __VA_ARGS__ ), ( {type}[] ){{ __VA_ARGS__ }} )

{type} {funcname}__clamp( {type} lower, {type} upper, {type} x );
// Returns: - `lower` if `lower >= x`;
//          - `upper` if `upper <= x`;
//          - `x` otherwise, if `lower < x && x < upper`
'''
    },

    'ENUM': {
        '*': '''
{type} {funcname}__succ( {type} x );
// Returns `x + 1`.
// @requires x != {funcname}__max_bound()

{type} {funcname}__succ_b( {type} x );
// Returns `x + 1`, or `{funcname}__max_bound()` if
// `x == {funcname}__max_bound()`.

{type} {funcname}__pred( {type} x );
// Returns `x - 1`.
// @requires x != {funcname}__min_bound()

{type} {funcname}__pred_b( {type} x );
// Returns `x - 1`, or `{funcname}__min_bound()` if
// `x == {funcname}__min_bound()`.
'''
    },

    'NUM': {

        'SIGNED': '''
bool {funcname}__is_signed( void );
// Returns `true`, because `{type}` values can be negative.

bool {funcname}__add_would_underflow( {type}, {type} );
bool {funcname}__add_would_overflow( {type}, {type} );

bool {funcname}__can_add( {type} x, {type} y );
// Returns the boolean that the behavior of `x + y` is well-defined.

bool {funcname}__sub_would_underflow( {type}, {type} );
bool {funcname}__sub_would_overflow( {type}, {type} );

bool {funcname}__can_sub( {type} x, {type} y );
// Returns the boolean that the behavior of `x - y` is well-defined.

bool {funcname}__mul_would_underflow( {type}, {type} );
bool {funcname}__mul_would_overflow( {type}, {type} );

bool {funcname}__can_mul( {type} x, {type} y );
// Returns the boolean that the behavior of `x * y` is well-defined.

bool {funcname}__div_would_underflow( {type}, {type} );
bool {funcname}__div_would_overflow( {type}, {type} );

bool {funcname}__can_div( {type} x, {type} y );
// Returns the boolean that the behavior of `x / y` is well-defined.

{type} {funcname}__add( {type} x, {type} y );
// Returns `x + y`.
// @requires {funcname}__can_add( x, y )

{type} {funcname}__sub( {type} x, {type} y );
// Returns `x - y`.
// @requires {funcname}__can_sub( x, y )

{type} {funcname}__mul( {type} x, {type} y );
// Returns `x * y`.
// @requires {funcname}__can_mul( x, y )

{type} {funcname}__div( {type} x, {type} y );
// Returns `x / y`.
// @requires {funcname}__can_div( x, y )

{type} {funcname}__mod( {type} x, {type} y );
// Returns `x % y`.
// @requires {funcname}__can_div( x, y )

{type} {funcname}__negate( {type} x );
// Returns `-x`.
// @requires x != {funcname}__min_bound()

{type} {funcname}__abs( {type} x );
// Returns `( x < 0 ) ? -x : x`.
// @requires x != {funcname}__min_bound()

{type} {funcname}__add_b( {type} x, {type} y );
// Returns: - `{funcname}__min_bound()` if `x + y` would underflow;
//          - `{funcname}__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

{type} {funcname}__sub_b( {type} x, {type} y );
// Returns: - `{funcname}__min_bound()` if `x - y` would underflow;
//          - `{funcname}__max_bound()` if `x - y` would overflow;
//          - `x - y` otherwise.

{type} {funcname}__mul_b( {type} x, {type} y );
// Returns: - `{funcname}__min_bound()` if `x * y` would underflow;
//          - `{funcname}__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

{type} {funcname}__div_b( {type} x, {type} y );
// If `y == 0`, returns: - `{funcname}__min_bound()` if `x < 0`;
//                       - `0` if `x == 0`;
//                       - `{funcname}__max_bound()` if `x > 0`;
// Otherwise, returns: - `{funcname}__min_bound()` if
//                         `{funcname}__div_would_underflow( x, y )`;
//                     - `{funcname}__max_bound()` if
//                         `{funcname}__div_would_overflow( x, y )`;
//                     - `x / y` otherwise;

{type} {funcname}__mod_b( {type} x, {type} y );
// Returns: - `0` if `!{funcname}__can_div( x, y )`;
//          - `x % y` otherwise.

{type} {funcname}__negate_b( {type} x );
// Returns: - `{funcname}__max_bound()` if `x == {funcname}__min_bound()`;
//          - `-x` otherwise.

{type} {funcname}__abs_b( {type} x );
// Returns: - `{funcname}__max_bound()` if `x == {funcname}__min_bound()`;
//          - `{funcname}__abs( x )` otherwise.

bool {funcname}__same_sign( {type} x, {type} y );
// Returns `true` if `x` and `y` have the same sign, or `false` otherwise.

bool {funcname}__is_negative( {type} x );     // Returns `x < 0`.
bool {funcname}__is_nonpositive( {type} x );  // Returns `x <= 0`.
bool {funcname}__is_zero( {type} x );         // Returns `x == 0`.
bool {funcname}__is_nonnegative( {type} x );  // Returns `x >= 0`.
bool {funcname}__is_positive( {type} x );     // Returns `x > 0`.

ord {funcname}__compare_0( {type} x );
// Returns `{funcname}__compare( x, 0 )`.

bool {funcname}__is_even( {type} x );     // Returns `x % 2 == 0`.
bool {funcname}__is_odd( {type} x );      // Returns `x % 2 == 1`.

{type} {funcname}__add_2( {type} );
{type} {funcname}__sub_2( {type} );
{type} {funcname}__mul_2( {type} );
{type} {funcname}__div_2( {type} );
{type} {funcname}__mod_2( {type} );

{type} {funcname}__mul_10( {type} );
{type} {funcname}__div_10( {type} );

{type} {funcname}__add_b_2( {type} );
{type} {funcname}__sub_b_2( {type} );
{type} {funcname}__mul_b_2( {type} );
{type} {funcname}__mul_b_10( {type} );
''',

        'UNSIGNED': '''
bool {funcname}__is_signed( void );
// Returns `false`, because `{type}` values can't be negative.

bool {funcname}__add_would_underflow( {type}, {type} );
bool {funcname}__add_would_overflow( {type}, {type} );

bool {funcname}__can_add( {type} x, {type} y );
// Returns the boolean that the behavior of `x + y` will not overflow.

bool {funcname}__sub_would_underflow( {type}, {type} );
bool {funcname}__sub_would_overflow( {type}, {type} );

bool {funcname}__can_sub( {type} x, {type} y );
// Returns the boolean that the behavior of `x - y` will not underflow.

bool {funcname}__mul_would_underflow( {type}, {type} );
bool {funcname}__mul_would_overflow( {type}, {type} );

bool {funcname}__can_mul( {type} x, {type} y );
// Returns the boolean that the behavior of `x * y` will not overflow.

bool {funcname}__div_would_underflow( {type}, {type} );
bool {funcname}__div_would_overflow( {type}, {type} );

bool {funcname}__can_div( {type} x, {type} y );
// Returns the boolean that `y != 0`.

{type} {funcname}__add( {type} x, {type} y );
// Returns `x + y`, which may overflow.

{type} {funcname}__sub( {type} x, {type} y );
// Returns `x - y`, which may underflow.

{type} {funcname}__mul( {type} x, {type} y );
// Returns `x * y`, which may overflow.

{type} {funcname}__div( {type} x, {type} y );
// Returns `x / y`.
// @requires y != 0

{type} {funcname}__mod( {type} x, {type} y );
// Returns `x % y`.
// @requires y != 0

{type} {funcname}__negate( {type} x );
// Returns `-x`, which gives `{funcname}__max_bound() - x + 1`.

{type} {funcname}__abs( {type} x );
// Returns `x`, because it will never be negative.

{type} {funcname}__add_b( {type} x, {type} y );
// Returns: - `{funcname}__max_bound()` if `x + y` would overflow;
//          - `x + y` otherwise.

{type} {funcname}__sub_b( {type} x, {type} y );
// Returns: - `0` if `x - y` would underflow;
//          - `x - y` otherwise.

{type} {funcname}__mul_b( {type} x, {type} y );
// Returns: - `{funcname}__max_bound()` if `x * y` would overflow;
//          - `x * y` otherwise.

{type} {funcname}__div_b( {type} x, {type} y );
// Returns: - `0` if `y == 0 && x == 0`;
//          - `{funcname}__max_bound()` if `y == 0 && x > 0`;
//          - `x / y` otherwise.

{type} {funcname}__mod_b( {type} x, {type} y );
// Returns: - `0` if `y == 0`;
//          - `x % y` otherwise.

{type} {funcname}__negate_b( {type} x );
// Returns `{funcname}__negate( x )`.

{type} {funcname}__abs_b( {type} x );
// Returns `{funcname}__abs( x )`.

bool {funcname}__same_sign( {type}, {type} );
// Returns `true`, because `{type}` values will always have the same sign.

bool {funcname}__is_negative( {type} x );     // Returns `false`.
bool {funcname}__is_nonpositive( {type} x );  // Returns `x == 0`.
bool {funcname}__is_zero( {type} x );         // Returns `x == 0`.
bool {funcname}__is_nonnegative( {type} x );  // Returns `true`.
bool {funcname}__is_positive( {type} x );     // Returns `x != 0`.

ord {funcname}__compare_0( {type} x );
// Returns `{funcname}__compare( x, 0 )`.

bool {funcname}__is_even( {type} x );  // Returns `x % 2 == 0`.
bool {funcname}__is_odd( {type} x );   // Returns `x % 2 == 1`.

{type} {funcname}__add_2( {type} );
{type} {funcname}__sub_2( {type} );
{type} {funcname}__mul_2( {type} );
{type} {funcname}__div_2( {type} );
{type} {funcname}__mod_2( {type} );

{type} {funcname}__mul_10( {type} );
{type} {funcname}__div_10( {type} );

{type} {funcname}__add_b_2( {type} );
{type} {funcname}__sub_b_2( {type} );
{type} {funcname}__mul_b_2( {type} );
{type} {funcname}__mul_b_10( {type} );
'''
    },


    'READ': {
        '*': '''
{type} {funcname}__from_str( char const * str );
// Parses the given `str` to produce the contained `{type}` value.
// On error, returns `0` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if `str` contains a value but a non-whitespace suffix;
// - `ERANGE` if the resulting value can't be represented by an `{type}`.
''',

        'BOOL': '''
{type} {funcname}__from_str( char const * str );
// Returns `true` if the given `str` contains `"true"` surrounded only by
// whitespace, or `false` if it contains `"false"` surrounded only by
// whitespace. On error, returns `false` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if there was a parse error.
''',

        'ORD': '''
{type} {funcname}__from_str( char const * str );
// Returns `LT` if the given `str` contains `"LT"` surrounded only by
// whitespace, or `EQ` if it contains `"EQ"` surrounded only by whitespace, or
// `GT` if it contains `"GT"` surrounded only by whitespace. On error, returns
// `EQ` and sets `errno` to:
// - `EINVAL` if `str == NULL` or `str` is `""`;
// - `EBADMSG` if there was a parse error.
'''
    },


    'TO_CONSTSTR': {

        'BOOL': '''
char const *
{funcname}__to_conststr( {type} x );
// Returns `"true"` if `x == true`, or `"false"` otherwise.
''',

        'ORD': '''
char const *
{funcname}__to_conststr( {type} );
// Returns `"LT"` if `x == LT`, `"EQ"` if `x == EQ`, or `"GT"` if `x == GT`.
'''
    }

}


# This is printed after all the other template strings:
BOTTOM = '''
#endif // ifndef LIBBASE_{macroname}_H
'''


def render(file, type, macroname, typename, funcname, typeclasses):
    def fmt(s):
        return s.format(type=type, macroname=macroname,
                        typename=typename, funcname=funcname)
    print(fmt(PREFIX), file=file)
    print(fmt(LICENSE), file=file)
    print(fmt(TOP), file=file)
    for tc in typeclasses:
        sel = '*'
        if ':' in tc:
            tc, sel = tc.split(':', 2)
        print(TYPECLASS_HEADER.format(typeclass=tc), file=file)
        tpld = TYPECLASSES.get(tc)
        print(fmt(tpld[sel] if sel in tpld.keys() else tpld['*']), file=file)
    print(fmt(BOTTOM), file=file)


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
    p.add_argument('-t', '--typeclasses', nargs='+', metavar='TC',
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
                  args.typeclasses)
    return 0


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.stdout, sys.argv))


