/* File : strtrim.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strtrim()

strtrim(dst, src, set, ends)
copies src to dst, but will skip leading characters in set if "ends"
is <= 0, and will skip trailing characters in set if ends is >= 0.
Thus there are three cases:
ends < 0 : trim a prefix
ends = 0 : trim a prefix and a suffix both
ends > 0 : trim a suffix
To compress internal runs, see strpack. The normal use of this is
strtrim(buffer, buffer, " \t", 0); The result is the address of the
NUL which now terminates dst.
*/

#include "strings.h"
#include "_str2set.h"

char *strtrim(dst, src, set, ends)
register char *dst, *src;
char *set;
int ends;
{
_str2set(set);
if (ends <= 0) {
while (_set_vec[*src] == _set_ctr) src++;
}
if (ends >= 0) {
register int chr;
register char *save = dst;
while (chr = *src++) {
*dst++ = chr;
if (_set_vec[chr] != _set_ctr) save = dst;
}
dst = save, *dst = NUL;
} else {
while (*dst++ = *src++) ;
--dst;
}
return dst;
}

