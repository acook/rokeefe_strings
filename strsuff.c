/* File : strsuff.c
Author : Richard A. O'Keefe.
Updated: 11 April 1984
Defines: strsuff()

strsuff(src, suffix)
checks whether suffix is a suffix of src. If it is not, the result
is NullS. If it is, the result is a pointer to the character of src
where suffix starts (which is the same as src+strlen(src)-strlen(prefix) ).
See strpref.c for a comment about using if (strsuff(...)) in C.
*/

#include "strings.h"

char *strsuff(src, suffix)
register char *src, *suffix;
{
register int L; /* length of suffix */

for (L = 0; *suffix++; L++)
if (!*src++) return NullS;
while (*src++) ;
for (--src, --suffix; --L >= 0; )
if (*--src != *--suffix) return NullS;
return src;
}

