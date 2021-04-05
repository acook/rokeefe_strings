/* File : strxcpy.c
Author : Richard A. O'Keefe.
Updated: 25 may 1984
Defines: strxcpy()

strxcpy(dst, src1, ..., srcn, NullS)
moves the concatenation of src1,...,srcn to dst, terminates it
with a NUL character, and returns the original value of dst.
It is just like strcpy except that it concatenates multiple sources.
Beware: the last argument should be the null character pointer.
Take VERY great care not to omit it! Also be careful to use NullS
and NOT to use 0, as on some machines 0 is not the same size as a
character pointer, or not the same bit pattern as NullS.
*/

#include "strings.h"
#include <varargs.h>

/*VARARGS*/
char *strxcpy(va_alist)
va_dcl
{
va_list pvar;
register char *dst, *src;
char *bogus;

va_start(pvar);
dst = va_arg(pvar, char *);
bogus = dst;
src = va_arg(pvar, char *);
while (src != NullS) {
while (*dst++ = *src++) ;
dst--;
src = va_arg(pvar, char *);
}
*dst = NUL; /* there might have been no sources! */
return bogus;
}

