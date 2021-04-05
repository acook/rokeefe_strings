/* File : memccpy.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: memccpy()

memccpy(dst, src, chr, len)
copies bytes from src to dst until either len bytes have been moved
or a byte equal to chr has been moved. In the former case it gives
NullS as the value, in the latter a pointer to just after the place
where "chr" was moved to in dst. Note that copying stops after the
first instance of "chr", and that remaining characters in "dst" are
not changed in any way, no NUL being inserted or anything.

See the "Character Comparison" section in the READ-ME file.
*/

#include "strings.h"

char *memccpy(dst, src, chr, len)
register char *dst, *src;
register int chr; /* should be char */
register int len;
{
while (--len >= 0)
if ((*dst++ = *src++) == chr) return dst;
return NullS;
}

