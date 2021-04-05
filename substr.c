/* File : substr.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: substr()

substr(destination, source, offset, length)
copies length bytes from source+offset to destination, stopping
early if a NUL is encountered. The difference between this and
strncpy(destination, source+offset, length)
is that if the offset is negative, it has the same effect as 0,
and if it exceeds strlen(source), it has the same effect as
strlen(source). If either of these boundaries is hit, or if
a NUL is encountered before length bytes have been moved, the
value of errno will be EDOM, otherwise it is guaranteed to be 0.
That is:
errno == 0 <=> (0 <= offset <= strlen(source)
&& 0 <= length && <= strlen(source)-offset)
You may accept the sensible result produced when these boundary
conditions are violated, or you may treat it as an error, as you
will. There is an algebra of sequences in which this treatment
of boundary conditions makes sense.

After the substring of source is moved to destination, a NUL byte
is moved to terminate the string, and the result is a pointer to
this NUL byte, ready to have new stuff stuck on the end.

I suppose this should be called strsub, but I can't stick it.
*/

#include "strings.h"
#include <errno.h>

extern int errno; /* why isn't this in errno.h?? */


char *substr(dst, src, off, len)
register char *dst, *src;
register int off, len;
{
errno = off < 0 || len < 0 ? EDOM : 0;

while (--off >= 0)
if (!*src++) { /* We've hit the end */
errno = EDOM; /* report boundary violation */
*dst = NUL; /* return empty string */
return dst;
}
while (--len >= 0)
if (!(*dst++ = *src++)) { /* We've hit the end */
errno = EDOM;
return dst-1; /* dst is already terminated */
}
*dst = NUL; /* terminate dst with NUL */
return dst;
}

