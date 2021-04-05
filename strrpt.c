/* File : strrpt.c
Author : Richard A. O'Keefe.
Updated: 20 April 1984
Defines: strrpt()

strrpt(dst, src, k) "RePeaTs" the string src into dst k times. E.g.
strrpt(dst, "hack ", 2) will move "hack hack" to dst. If k <= 0 it
does nothing. The result is the number of characters moved, except
for the closing NUL. src may be "" but may not of course be NullS.
*/

#include "strings.h"

int strrpt(dst, src, k)
register char *dst;
char *src;
int k;
{
char *save;

for (save = dst; --k >= 0; --dst) {
register char *p;
for (p = src; *dst++ = *p++; ) ;
}
return dst-save;
}

