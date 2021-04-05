/* File : strctrim.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strctrim()

strctrim(dst, src, set, ends)
copies src to dst, but will skip leading characters not in set if
ends <= 0 and will skip trailing characters not in set if ends >= 0.
Thus there are three cases:
ends < 0 : trim a prefix
ends = 0 : trim a prefix and a suffix both
ends > 0 : trim a suffix
This is to strtrim as strcspn is to strspn.
*/

#include "strings.h"
#include "_str2set.h"

char *strctrim(dst, src, set, ends)
register char *dst, *src;
char *set;
int ends;
{
_str2set(set);
if (ends <= 0) {
register int chr;
while ((chr = *src++) && _set_vec[chr] != _set_ctr) ;
--src;
}
if (ends >= 0) {
register int chr;
register char *save = dst;
while (chr = *src++) {
*dst++ = chr;
if (_set_vec[chr] == _set_ctr) save = dst;
}
dst = save, *dst = NUL;
} else {
while (*dst++ = *src++) ;
--dst;
}
return dst;
}

