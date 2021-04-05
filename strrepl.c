/* File : strrepl.c
Author : Richard A. O'Keefe.
Updated: 23 April 1984
Defines: strrepl()

strrepl(dst, src, pat, rep, times) copies src to dst, replacing the
first "times" non-overlapping instances of pat by rep. pat is not a
regex(3) pattern, it is a literal string which must be matched
exactly. As a special hack, since strfind claims to find "" just
once at the end of the src string, strrepl does a strcat when pat is
an empty string "". If times <= 0, it is just strmov.

The result is a pointer to the NUL which now terminates dst.

BEWARE: even when rep is shorter than pat it is NOT necessarily safe
for dst to be the same as src. ALWAYS make sure dst and src do not/
will not overlap. You have been warned.

There really ought to be a strnrepl with a bound for the size of the
destination string, but there isn't.
*/

#include "strings.h"
#include "_str2pat.h"

char *strrepl(dst, src, pat, rep, times)
char *dst, *src, *pat, *rep;
int times;
{
register char *s, *p;
register int c, lastch;

pat = _str2pat(pat);
if (times <= 0) {
for (p = dst, s = src; *p++ = *s++; ) ;
return p-1;
}
if (_pat_lim < 0) {
for (p = dst, s = src; *p++ = *s++; ) ;
for (--p, s = rep; *p++ = *s++; ) ;
return p-1;
}
/* The pattern is non-empty and times is positive */
c = _pat_lim, lastch = pat[c];
for (;;) {
for (s = src, p = dst; --c >= 0; )
if (!(*p++ = *s++)) return p-1;
c = *s, src = s, dst = p;
if (c == lastch) {
for (s -= _pat_lim, p = pat; *p; )
if (*s++ != *p++) goto not_yet;
for (p = dst-_pat_lim, s = rep; *p++ = *s++; ) ;
--p;
if (--times == 0) {
for (s = src; *p++ = *++s; ) ;
return p-1;
}
dst = p, src++, c = _pat_lim;
} else {
not_yet: c = _pat_vec[c];
}
}
}
