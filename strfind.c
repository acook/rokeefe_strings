/* File : strfind.c
Author : Richard A. O'Keefe.
Updated: 23 April 1984
Defines: strfind()

strfind(src, pat) looks for an instance of pat in src. pat is not a
regex(3) pattern, it is a literal string which must be matched exactly.
As a special hack to prevent infinite loops, the empty string will be
found just once, at the far end of src. This is hard to justify. The
result is a pointer to the first character AFTER the located instance,
or NullS if pat does not occur in src. The reason for returning the
place after the instance is so that you can count the number of instances
by writing
_str2pat(ToBeFound);
for (p = src, n = 0; p = strfind(p, NullS); n++) ;
If you want a pointer to the first character of the instance, it is up
to you to subtract strlen(pat).

If there were a strnfind it wouldn't have to look at all the characters
of src, this version does otherwise it could miss the closing NUL.
*/

#include "strings.h"
#include "_str2pat.h"

char *strfind(src, pat)
char *src, *pat;
{
register char *s, *p;
register int c, lastch;

pat = _str2pat(pat);
if (_pat_lim < 0) {
for (s = src; *s++; ) ;
return s-1;
}
/* The pattern is non-empty */
for (c = _pat_lim, lastch = pat[c]; ; c = _pat_vec[c]) {
for (s = src; --c >= 0; )
if (!*s++) return NullS;
c = *s, src = s;
if (c == lastch) {
for (s -= _pat_lim, p = pat; *p; )
if (*s++ != *p++) goto not_yet;
return s;
not_yet:; }
}
}

