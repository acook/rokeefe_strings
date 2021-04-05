/* File : bcopy.c
Author : Richard A. O'Keefe.
Updated: 23 April 1984
Defines: bcopy()

bcopy(src, dst, len) moves exactly "len" bytes from the source "src"
to the destination "dst". It does not check for NUL characters as
strncpy() and strnmov() do. Thus if your C compiler doesn't support
structure assignment, you can simulate it with
bcopy(&from, &to, sizeof from);
BEWARE: the first two arguments are the other way around from almost
everything else. I'm sorry about that, but that's the way it is in
the 4.2bsd manual, though they list it as a bug. For a version with
the arguments the right way around, use bmove().
No value is returned.

Note: the "b" routines are there to exploit certain VAX order codes,
but the MOVC3 instruction will only move 65535 characters. The asm
code is presented for your interest and amusement.
*/

#include "strings.h"

#if VaxAsm

void bcopy(src, dst, len)
char *src, *dst;
int len;
{
asm("movc3 12(ap),*4(ap),*8(ap)");
}

#else ~VaxAsm

void bcopy(src, dst, len)
register char *src, *dst;
register int len;
{
while (--len >= 0) *dst++ = *src++;
}

#endif VaxAsm

