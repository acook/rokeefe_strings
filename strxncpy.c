/* File : strxncpy.c
Author : Richard A. O'Keefe.
Updated: 25 may 1984
Defines: strxncpy()

strxncpy(dst, len, src1, ..., srcn, NullS)
moves the first len characters of the concatenation of src1,...,srcn
to dst. If there aren't that many characters, a NUL character will
be added to the end of dst to terminate it properly. This gives the
same effect as calling strxcpy(buff, src1, ..., srcn, NullS) with a
large enough buffer, and then calling strncpy(dst, buff, len).
It is just like strncpy except that it concatenates multiple sources.
Beware: the last argument should be the null character pointer.
Take VERY great care not to omit it! Also be careful to use NullS
and NOT to use 0, as on some machines 0 is not the same size as a
character pointer, or not the same bit pattern as NullS.

Note: strxncpy is like strncpy in that it always moves EXACTLY len
characters; dst will be padded on the right with NUL characters as
needed. strxnmov does the same. strxncat, like strncat, does NOT.
*/

#include "strings.h"
#include <varargs.h>

/*VARARGS*/
char *strxncpy(va_alist)
va_dcl
{
va_list pvar;
register char *dst, *src;
register int len;
char *bogus;

va_start(pvar);
dst = va_arg(pvar, char *);
bogus = dst;
len = va_arg(pvar, int);
src = va_arg(pvar, char *);
while (src != NullS) {
do if (--len < 0) return bogus;
while (*dst++ = *src++);
dst--;
src = va_arg(pvar, char *);
}
for (src = dst; --len >= 0; *dst++ = NUL) ;
return bogus;
}

