/* File : memrev.c
Author : Richard A. O'Keefe.
Updated: 1 June 1984
Defines: memrev()

memrev(dst, src, len)
moves len bytes from src to dst, in REVERSE order. NUL characters
receive no special treatment, they are moved like the rest. It is
to strrev as memcpy is to strcpy.

Note: this function is perfectly happy to reverse a block into the
same place, memrev(x, x, L) will work.
It will not work for partially overlapping source and destination.
*/

#include "strings.h"

void memrev(dsta, srca, len)
register char *dsta, *srca;
int len;
{
register char *dstz, *srcz;
register int t;

if (len <= 0) return;
srcz = srca+len;
dstz = dsta+len;
while (srcz > srca) {
t = *--srcz;
*--dstz = *srca++;
*dsta++ = t;
}
}

