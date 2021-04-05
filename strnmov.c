/* File : strnmov.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strnmov()

strnmov(dst, src, n) moves up to n characters of src to dst. It
always moves exactly n characters to dst; if src is shorter than n
characters dst will be extended on the right with NULs, while if src
is longer than n characters dst will be a truncated version of src
and will not have a closing NUL. The result is a pointer to the
first NUL in dst, or is dst+n if dst was truncated.
*/

#include "strings.h"

char *strnmov(dst, src, n)
register char *dst, *src;
register int n;
{
while (--n >= 0) {
if (!(*dst++ = *src++)) {
src = dst-1;
while (--n >= 0) *dst++ = NUL;
return src;
}
}
return dst;
}

