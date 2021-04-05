/* File : strnrev.c
Author : Richard A. O'Keefe.
Updated: 1 June 1984
Defines: strnrev()

strnrev(dst, src, len)
copies all the characters of src to dst, in REVERSE order. If src
was terminated by a NUL character, so will dst be, otherwise dst &
src are both exactly len non-NUL characters long. This returns no
result. It is to strrev as strncpy is to strcpy.

Note: this function is perfectly happy to reverse a string into the
same place, strnrev(x, x, L) will work.
It will not work for partially overlapping source and destination.
*/

#include "strings.h"

void strnrev(dsta, srca, len)
register char *dsta, *srca;
register int len;
{
register char *dstz, *srcz;
register int t;
/* On a machine which doesn't supply 6 register variables,
you could #define t len, as the two variables don't overlap.
*/

for (srcz = srca; --len >= 0 && *srcz; srcz++) ;
dstz = dsta+(srcz-srca);
/* If srcz was stopped by len running out, it points just after
the last character of the source string, and it and dstz are
just right. Otherwise, it was stopped by hitting NUL, and is
in the right place, but dstz should get a NUL as well.
*/
if (len >= 0) *dstz = NUL;
/* That was the very last use of len */
while (srcz > srca) {
t = *--srcz;
*--dstz = *srca++;
*dsta++ = t;
}
}

