/* File : memcpy.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: memcpy()

memcpy(dst, src, len)
moves len bytes from src to dst. The result is dst. This is not
the same as strncpy or strnmov, while move a maximum of len bytes
and stop early if they hit a NUL character. This moves len bytes
exactly, no more, no less. See also bcopy() and bmove() which do
not return a value but otherwise do the same job.

Note: the VAX assembly code version can only handle 0 <= len < 2^16.
It is presented for your interest and amusement.
*/

#include "strings.h"

#if VaxAsm

char *memcpy(dst, src, len)
char *dst, *src;
int len;
{
asm("movc3 12(ap),*8(ap),*4(ap)");
return dst;
}

#else ~VaxAsm

char *memcpy(dst, src, len)
char *dst;
register char *src;
register int len;
{
register char *d;

for (d = dst; --len >= 0; *d++ = *src++) ;
return dst;
}

#endif VaxAsm

