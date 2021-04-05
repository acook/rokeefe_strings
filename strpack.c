/* File : strpack.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strpack()

strpack(dst, src, set, c)
copies characters from src to dst, stopping when it finds a NUL. If
c is NUL, characters in set are not copied to dst. If c is not NUL,
sequences of characters from set are copied as a single c.
strpack(d, s, " \t", ' ') can be used to compress white space,
strpack(d, s, " \t", NUL) to eliminate it. To translate characters
in set to c without compressing runs, see strtrans(). The result is
the address of the NUL byte now terminating dst. Note that dst may
safely be the same as src.
*/

#include "strings.h"
#include "_str2set.h"

char *strpack(dst, src, set, c)
register _char_ *dst, *src;
char *set;
register int c;
{
register int chr;

_str2set(set);
while (chr = *src++) {
if (_set_vec[chr] == _set_ctr) {
while ((chr = *src++) && _set_vec[chr] == _set_ctr) ;
if (c) *dst++ = c; /* 1. If you don't want trailing */
if (!chr) break; /* 2. things turned into "c", swap */
} /* lines 1 and 2. */
*dst++ = chr;
}
*dst = 0;
return dst;
}

