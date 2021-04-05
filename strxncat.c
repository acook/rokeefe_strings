/* File : strxncat.c
Author : Richard A. O'Keefe.
Updated: 2 June 1984
Defines: strxncat()

strxncat(dst, len, src1, ..., srcn, NullS)
moves the first len bytes of the concatenation of dst,src1,...,srcn
to dst, terminating it with a NUL character unless len runs out, and
returns the original value of dst.
It is just like strcat except that it concatenates multiple sources.
Roughly, strxncat(d, L, s1, ..., sn) <=> strxncpy(d, L, d, s1, ..., sn).
Beware: the last argument should be the null character pointer.
Take VERY great care not to omit it! Also be careful to use NullS
and NOT to use 0, as on some machines 0 is not the same size as a
character pointer, or not the same bit pattern as NullS.

Note: strxncat is like strncat in that it will add at most one NUL,
and may in consequence move fewer than len characters. No so the
strxncpy and strxnmov routines, which resemble strncpy and strnmov.
*/

#include "strings.h"
#include <varargs.h>

/*VARARGS*/
char *strxncat(va_alist)
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
while (*dst)
if (--len < 0) return bogus;
else dst++;
src = va_arg(pvar, char *);
while (src != NullS) {
do if (--len < 0) return bogus;
while (*dst++ = *src++);
dst--;
src = va_arg(pvar, char *);
}
return bogus;
}

