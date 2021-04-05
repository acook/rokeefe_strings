/* File : strncat.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strncat()

strncat(dst, src, n) copies up to n characters of src to the end of
dst. As with strcat, it has to search for the end of dst. Even if
it abandons src early because n runs out it will still close dst
with a NUL. See also strnmov.
*/

#include "strings.h"

char *strncat(dst, src, n)
register char *dst, *src;
register int n;
{
char *save;

for (save = dst; *dst++; ) ;
for (--dst; --n >= 0; )
if (!(*dst++ = *src++)) return save;
*dst = NUL;
return save;
}

