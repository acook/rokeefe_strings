/* File : strnrpt.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strnrpt()

strnrpt(dst, n, src, k) "RePeaTs" the string src into dst k times,
but will truncate the result at n characters if necessary. E.g.
strnrpt(dst, 7, "hack ", 2) will move "hack ha" to dst WITHOUT the
closing NUL. The result is the number of characters moved, not
counting the closing NUL. Equivalent to strrpt-ing into an infinite
buffer and then strnmov-ing the result.
*/

#include "strings.h"

int strnrpt(dst, n, src, k)
register char *dst;
register int n;
char *src;
int k;
{
char *save;

for (save = dst; --k >= 0; dst--) {
register char *p;
for (p = src; ; ) {
if (--n < 0) return dst-save;
if (!(*dst++ = *p++)) break;
}
}
return dst-save;
}

