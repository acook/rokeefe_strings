/* File : strrev.c
Author : Richard A. O'Keefe.
Updated: 1 June 1984
Defines: strrev()

strrev(dst, src)
copies all the characters of src to dst, in REVERSE order. Dst is
properly terminated with a NUL character. There is no result.
Example: strrev(x, "able was I er") moves "re I saw elba" to x.

Note: this function is perfectly happy to reverse a string into the
same place, strrev(x, x) will work. That is why it looks so hairy.
It will not work for partially overlapping source and destination.
*/

#include "strings.h"

void strrev(dsta, srca)
register char *dsta, *srca;
{
register char *dstz, *srcz;
register int t; /* should be char */

for (srcz = srca; *srcz++; ) ;
srcz--;
dstz = dsta+(srcz-srca);
/* Now srcz points to the NUL terminating src,
and dstz points to where the terminating NUL for dst belongs.
*/
*dstz = NUL;
while (srcz > srca) {
/* This is guaranteed safe by K&R, since srcz and srca
point "into the same array".
*/
t = *--srcz;
*--dstz = *srca++;
*dsta++ = t;
}
}

