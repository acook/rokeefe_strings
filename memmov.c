/* File : memmov.c
Author : Richard A. O'Keefe.
Updated: 25 May 1984
Defines: memmov()

memmov(dst, src, len)
moves len bytes from src to dst. The result is dst+len.
This is to memcpy as str[n]mov is to str[n]cpy, that is, it moves
exactly the same bytes but returns a pointer to just after the
the last changed byte. You can concatenate blocks pa for la,
pb for lb, pc for lc into area pd by doing
memmov(memmov(memmov(pd, pa, la), pb, lb), pc, lc);
Unlike strnmov, memmov does not stop when it hits a NUL byte.

Note: the VAX assembly code version can only handle 0 <= len < 2^16.
It is presented for your interest and amusement.
*/

#include "strings.h"

#if VaxAsm

char *memmov(dst, src, len)
char *dst, *src;
int len;
{
asm("movc3 12(ap),*8(ap),*4(ap)");
return dst+len;
}

#else ~VaxAsm

char *memmov(dst, src, len)
register char *dst, *src;
register int len;
{
while (--len >= 0) *dst++ = *src++;
return dst;
}

#endif VaxAsm

