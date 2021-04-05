/* File : strncpy.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strncpy()

strncpy(dst, src, n) copies up to n characters of src to dst. It
will pad dst on the right with NUL or truncate it as necessary to
ensure that n characters exactly are transferred. It returns the
old value of dst as strcpy does.
*/

#include "strings.h"

char *strncpy(dst, src, n)
register char *dst, *src;
register int n;
{
char *save;

for (save = dst; --n >= 0; ) {
if (!(*dst++ = *src++)) {
while (--n >= 0) *dst++ = NUL;
return save;
}
}
return save;
}

