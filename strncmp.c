/* File : strncmp.c
Author : Richard A. O'Keefe.
Updated: 10 April 1984
Defines: strncmp()

strncmp(s, t, n) compares the first n characters of s and t.
If they are the same in the first n characters it returns 0,
otherwise it returns the same value as strcmp(s, t) would.
*/

#include "strings.h"

int strncmp(s, t, n)
register char *s, *t;
register int n;
{
while (--n >= 0) {
if (*s != *t++) return s[0]-t[-1];
if (!*s++) return 0;
}
return 0;
}

