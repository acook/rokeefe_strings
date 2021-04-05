/* File : memrchr.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: memrchr()

memrchr(src, chr, len)
searches the memory area pointed to by src extending for len bytes,
looking for an occurrence of the byte value chr. It returns NullS
if there is no such occurrence. Otherwise it returns a pointer to
the LAST such occurrence.

See the "Character Comparison" section in the READ-ME file.
*/

#include "strings.h"

char *memrchr(src, chr, len)
register char *src;
register int chr; /* should be char */
register int len;
{
register char *ans;
for (ans = NullS; --len >= 0; src++)
if (*src == chr) ans = src;
return ans;
}

